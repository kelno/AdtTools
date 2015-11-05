#include "console_tool.h"
#include "adt.h"
#include "logger.h"

std::string const& ConsoleTool::GetCommandName() const
{
    return commandName;
}

std::string const& ConsoleTool::GetVersion() const
{
    return version;
}

std::string const& ConsoleTool::GetShortDescription() const
{
    return shortDescription;
}

std::string const& ConsoleTool::GetFullDescription() const
{
    return fullDescription;
}

std::vector<ToolArgument> const& ConsoleTool::GetArguments() const
{
    return arguments;
}

ConsoleTool::ConsoleTool(std::string const& commandName, std::string const& version, std::string const& shortDescription, std::string const& fullDescription, std::vector<ToolArgument> const& arguments) :
    commandName(commandName),
    version(version),
    shortDescription(shortDescription),
    fullDescription(fullDescription),
    arguments(arguments)
{
}

unsigned int ConsoleTool::GetMinArgumentCount() const
{
    unsigned int count = 0;
    for(auto arg : arguments)
        if(arg.required)
            count++;

    return count;
}

unsigned int ConsoleTool::GetMaxArgumentCount() const
{
    return unsigned int(arguments.size());
}

std::fstream* ConsoleTool::OpenAdtFile(std::string fileName, adt* ADT)
{
    std::fstream* file = new std::fstream(fileName, std::ios::in | std::ios::out | std::ios::binary);
    if (!file->is_open())
    {
        sLogger->Out(Logger::LogLevel::LOG_LEVEL_ERROR, "Could not open file: %s", fileName);
        return nullptr;
    }

    ADT = new adt(*file);

    return file;
}