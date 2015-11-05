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
    if (targetADT->mfbo)
    {
        if (targetADT->mfbo->hasInvertedMinMax())
        {
            sLogger->Out(Logger::LogLevel::LOG_LEVEL_NORMAL, "%s has inverted coordinates, fixing it.", targetADTFilename);
            targetADT->mfbo->invertMinMax();

            targetADT->WriteToDisk(*targetFile);
        }
        else {
            sLogger->Out(Logger::LogLevel::LOG_LEVEL_NORMAL, "%s seems already correct, nothing to do.", targetADTFilename);
        }
    }
    else {
        sLogger->Out(Logger::LogLevel::LOG_LEVEL_NORMAL, "%s has no MFBO data, nothing to do.", targetADTFilename);
    }

    //Done, cleaning up
    cleanAll();

    return 0;
}