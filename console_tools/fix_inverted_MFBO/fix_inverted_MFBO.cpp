#include "fix_inverted_MFBO.h"
#include "adt.h"
#include "logger.h"

#include <sstream>

int FixInvertedMFBO::Work(int argc, char* argv[])
{
    //Init
    std::fstream* targetFile = nullptr;
    adt* targetADT = nullptr;
    std::string targetADTFilename = argv[2];

    auto cleanAll = [&]()
    {
        if (targetFile)
        {
            if(targetFile->is_open())
                targetFile->close();

            delete targetFile;
            targetFile = nullptr;
        }
        if (targetADT)
        {
            delete targetADT;
            targetADT = nullptr;
        }
    };

    if (!(targetFile = OpenAdtFile(targetADTFilename, targetADT)))
    {
        cleanAll();
        return 1;
    }

    //Fix the bug if needed
    if (targetADT->mfbo->hasInvertedMinMax())
    {
        std::cout << targetADTFilename << " has inverted coordinates, fixing it." << std::endl;
        targetADT->mfbo->invertMinMax();

        targetADT->WriteToDisk(*targetFile);
    } else {
        std::cout << targetADTFilename << " seems already correct, nothing to do." << std::endl;
    }

    //Done, cleaning up
    cleanAll();

    return 0;
}