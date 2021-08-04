#include "all_water_MCLQ.h"
#include "adt.h"
#include "logger.h"

#include <sstream>

int AllWaterMCLQ::Work(int argc, char* argv[])
{
    //Init
    std::string targetADTFilename = argv[2];
    float height = (float)atof(argv[3]);
    MCNKFlags type = MCNKFlags(atoi(argv[4]));

    std::unique_ptr<std::fstream> targetFile;
    std::unique_ptr<adt> targetADT;
    std::tie(targetFile, targetADT) = OpenAdtFile(targetADTFilename);

    if (!targetFile)
        return 1;

    //Set water
    targetADT->AllWaterMCLQ(height, type);
    sLogger->Out(Logger::LogLevel::LOG_LEVEL_NORMAL, "Water set to %f", height);

    //Cleaning up
    targetADT->WriteToDisk(*targetFile);

    return 0;
}