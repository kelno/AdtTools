#include "copy_MCLQ.h"
#include "adt.h"
#include "logger.h"

#include <sstream>

int CopyMCLQ::Work(int argc, char* argv[])
{
    //Init
    std::fstream* sourceFile = nullptr;
    std::fstream* targetFile = nullptr;
    adt* sourceADT = nullptr;
    adt* targetADT = nullptr;
    std::string sourceADTFilename = argv[2];
    std::string targetADTFilename = argv[3];

    auto cleanAll = [&]()
    {
        if (sourceFile)
        {
            if(sourceFile->is_open())
                sourceFile->close();

            delete sourceFile;
            sourceFile = nullptr;
        }
        if (targetFile)
        {
            if(targetFile->is_open())
                targetFile->close();

            delete targetFile;
            targetFile = nullptr;
        }
        if (sourceADT)
        {
            delete sourceADT;
            sourceADT = nullptr;

        }
        if (targetADT)
        {
            delete targetADT;
            targetADT = nullptr;
        }
    };

    if (!(sourceFile = OpenAdtFile(sourceADTFilename, sourceADT)))
    {
        cleanAll();
        return 1;
    }

    if (!(targetFile = OpenAdtFile(targetADTFilename, targetADT)))
    {
        cleanAll();
        return 1;
    }

    //Copy all water chunks
    for (unsigned int i = 0; i < MCNK::ENTRY_COUNT; i++)
        targetADT->mcnk->entries[i].mclq = sourceADT->mcnk->entries[i].mclq;

    sLogger->Out(Logger::LogLevel::LOG_LEVEL_NORMAL, "Water copied from %s to %s", sourceADTFilename, targetADTFilename);

    //Done, cleaning up
    targetADT->WriteToDisk(*targetFile);
    cleanAll();

    return 0;
}