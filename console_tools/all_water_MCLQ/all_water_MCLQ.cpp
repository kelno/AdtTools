#include "all_water_MCLQ.h"
#include "adt.h"
#include "logger.h"

#include <sstream>

int AllWaterMCLQ::Work(int argc, char* argv[])
{
    //Init
    std::string targetADTFilename = argv[2];
    float height = (float)atof(argv[3]);

    std::fstream* targetFile = nullptr;
    adt* targetADT = nullptr;

    auto cleanAll = [&]()
    {
        if (targetFile)
        {
            if (targetFile->is_open())
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

    //Set water
    targetADT->AllWaterMCLQ(height);
    sLogger->Out(Logger::LogLevel::LOG_LEVEL_NORMAL, "Water set to %f", height);

    //Cleaning up
    targetADT->WriteToDisk(*targetFile);
    cleanAll();

    return 0;
}