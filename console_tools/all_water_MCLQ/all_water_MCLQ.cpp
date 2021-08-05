#include "all_water_MCLQ.h"
#include "adt.h"
#include "logger.h"

#include <sstream>

int AllWaterMCLQ::Work(int argc, char* argv[])
{
    //Init
    std::string targetADTFilename = argv[1];
    float height = (float)atof(argv[2]);
    MCNKFlags type = FLAG_LQ_RIVER;
    if (argc >= 4)
        type = MCNKFlags(atoi(argv[3]));

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

int main(int argc, char* argv[])
{
    AllWaterMCLQ tool;

    return tool.Main(argc, argv);
}