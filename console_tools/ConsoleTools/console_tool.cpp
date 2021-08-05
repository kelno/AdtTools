#include "console_tool.h"
#include "adt.h"
#include "logger.h"

#include <iostream>
#include <vector>
#include <list>
#include <sstream>

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

std::list<ToolArgument> const& ConsoleTool::GetArguments() const
{
    return arguments;
}

ConsoleTool::ConsoleTool(std::string const& commandName, std::string const& version, std::string const& shortDescription, std::string const& fullDescription, std::list<ToolArgument> const& arguments) :
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

std::pair<std::unique_ptr<std::fstream>, std::unique_ptr<adt>> ConsoleTool::OpenAdtFile(std::string fileName)
{
    std::unique_ptr<std::fstream> file = std::make_unique<std::fstream>(fileName, std::ios::in | std::ios::out | std::ios::binary);
    if (!file->is_open())
    {
        sLogger->Out(Logger::LogLevel::LOG_LEVEL_ERROR, "Could not open file: %s", fileName);
        return { nullptr, nullptr };
    }

    std::unique_ptr<adt> ADT = std::make_unique<adt>(*file);

    return { std::move(file), std::move(ADT) };
}

/* Print the arguments of a command */
void ConsoleTool::PrintUsage(std::string const& executableName)
{
    auto arguments = GetArguments();

    std::stringstream usage;
    usage << "Usage: " << executableName;
    for (auto arg : arguments)
        if (arg.required)
            usage << " <" << arg.name << ">";
        else
            usage << " [" << arg.name << "]";

    usage << std::endl;

    for (auto arg : arguments)
        usage << "  " << arg.name << ": " << arg.description << std::endl;

    sLogger->Out(Logger::LogLevel::LOG_LEVEL_NORMAL, "%s", usage.str().c_str());
}

void ConsoleTool::ShowExtendedDescription(std::string const& executableName)
{
    sLogger->Out(Logger::LogLevel::LOG_LEVEL_NORMAL, "Description:");
    sLogger->Out(Logger::LogLevel::LOG_LEVEL_NORMAL, "  %s\n", GetFullDescription().c_str());
    PrintUsage(executableName);
    sLogger->Out(Logger::LogLevel::LOG_LEVEL_NORMAL, "Tool version: %s", GetVersion().c_str());
}

int ConsoleTool::Main(int argc, char* argv[])
{
    auto DoExit = [&](int code)
    {
        sLogger->WaitUntilEmpty();
        return code;
    };

    std::string executableName = argv[0];

    //if no command given, list commands
    if (argc == 1)
    {
        ShowExtendedDescription(executableName);
        return DoExit(0);
    }

    //else if command given
    std::string commandName = argv[1];

    //if command argument(s) is/are given
    assert(argc >= 1);
    unsigned int argCount = argc - 1;
    if (argCount < GetMinArgumentCount())
    {
        sLogger->Out(Logger::LogLevel::LOG_LEVEL_ERROR, "%s", "Too few arguments.");
        PrintUsage(executableName);
        return DoExit(0);
    }
    else if (argCount > GetMaxArgumentCount())
    {
        sLogger->Out(Logger::LogLevel::LOG_LEVEL_ERROR, "%s", "Too much arguments.");
        PrintUsage(executableName);
        return DoExit(0);
    }

    //all okay let's get to work
    int error = Work(argc, argv);

    return DoExit(error);
}