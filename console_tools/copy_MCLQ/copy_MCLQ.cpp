#include "copy_MCLQ.h"
#include "adt.h"
#include "logger.h"

#include <sstream>

int CopyMCLQ::Work(int argc, char* argv[])
{
    std::string sourceADTFilename = argv[1];
    std::string targetADTFilename = argv[2];

    std::unique_ptr<std::fstream> sourceFile;
    std::unique_ptr<adt> sourceADT;
    std::tie(sourceFile, sourceADT) = OpenAdtFile(sourceADTFilename);

    std::unique_ptr<std::fstream> targetFile;
    std::unique_ptr<adt> targetADT;
    std::tie(targetFile, targetADT) = OpenAdtFile(targetADTFilename);

    if (!sourceFile)
        return 1;

    if (!targetFile)
        return 1;

    // Copy all water chunks
    for (unsigned int i = 0; i < CHUNKS_PER_ADT; i++)
    {
        targetADT->mcnk->entries[i].header.flags = sourceADT->mcnk->entries[i].header.flags;
        targetADT->mcnk->entries[i].mclq = std::move(sourceADT->mcnk->entries[i].mclq);
    }

    sLogger->Out(Logger::LogLevel::LOG_LEVEL_NORMAL, "Water copied from %s to %s", sourceADTFilename.c_str(), targetADTFilename.c_str());

    // Done, cleaning up
    targetADT->WriteToDisk(*targetFile);

    return 0;
}

int main(int argc, char* argv[])
{
    CopyMCLQ tool;

    return tool.Main(argc, argv);
}
