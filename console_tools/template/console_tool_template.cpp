#include "console_tool_template.h"

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