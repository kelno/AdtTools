#include <iostream>
#include <vector>
#include <list>
#include <sstream>

#include "template/console_tool.h"
#include "all_water_MCLQ/all_water_MCLQ.h"
#include "copy_MCLQ/copy_MCLQ.h"
#include "fix_inverted_MFBO/fix_inverted_MFBO.h"

#include "version.h"
#include "logger.h"

#define TOOLS_DESCRIPTION "Various tools to alter WoW map files, for Vanilla to Lich King expansions."

std::list<ConsoleTool*> tools;

/* Create all tools into tools list */
void InitTools()
{
    tools.push_back(static_cast<ConsoleTool*>(new AllWaterMCLQ()));
    tools.push_back(static_cast<ConsoleTool*>(new CopyMCLQ()));
    tools.push_back(static_cast<ConsoleTool*>(new FixInvertedMFBO()));
};

/* Delete all tools and empty tools list */
void DeleteTools()
{
    while (!tools.empty())
    {
        ConsoleTool* tool = tools.back();
        delete tool;
        tool = nullptr;
        tools.pop_back();
    }
}

void ListCommands()
{
    std::stringstream list;
    list << "Commands list:" << std::endl;
    for(auto itr : tools)
        list << "  " << itr->GetCommandName() << " - " << itr->GetShortDescription() << std::endl;

    sLogger->Out(Logger::LogLevel::LOG_LEVEL_NORMAL, "%s", list.str().c_str());
}

ConsoleTool* GetToolWithName(std::string name)
{
    for (auto itr : tools)
        if (itr->GetCommandName() == name)
            return itr;

    //no tool found
    return nullptr;
}

/* Print the arguments of a command */
void PrintUsage(std::string const& executableName, std::string const& commandName, ConsoleTool const* tool)
{
    auto arguments = tool->GetArguments();

    std::stringstream usage;
    usage << "Usage: " << commandName;
    for(auto arg : arguments)
        if(arg.required)
            usage << " <" << arg.name << ">";
        else
            usage << " [" << arg.name << "]";

    usage << std::endl;

    for (auto arg : arguments)
        usage << "  " << arg.name << ": " << arg.description << std::endl;

    sLogger->Out(Logger::LogLevel::LOG_LEVEL_NORMAL, "%s", usage.str().c_str());
}

void ShowExtendedDescription(std::string const& executableName, std::string const& commandName, ConsoleTool const* tool)
{
    sLogger->Out(Logger::LogLevel::LOG_LEVEL_NORMAL, "Description:");
    sLogger->Out(Logger::LogLevel::LOG_LEVEL_NORMAL, "  %s\n", tool->GetFullDescription().c_str());
    PrintUsage(executableName, commandName, tool);    
    sLogger->Out(Logger::LogLevel::LOG_LEVEL_NORMAL, "Tool version: %s", tool->GetVersion().c_str());
}

void main(int argc, char* argv[])
{
#ifdef DEBUG_MODE
    std::cout << "Press any key to continue..." << std::endl;
    std::getchar();
#endif

    auto DoExit = [&](int code)
    {
        //erase all tools
        DeleteTools();
        sLogger->WaitUntilEmpty();
        exit(code);
    };

    InitTools();

    //if no command given, list commands
	if(argc == 1)
	{
        sLogger->Out(Logger::LogLevel::LOG_LEVEL_NORMAL, "AdtTools v%s", ADTTOOLS_VERSION);
        sLogger->Out(Logger::LogLevel::LOG_LEVEL_NORMAL, "%s", TOOLS_DESCRIPTION);
        ListCommands();

        DoExit(0);
	} 
    
    //else if command given
    std::string executableName = argv[0];
    std::string commandName = argv[1];

    //check if command exists
    ConsoleTool* tool = GetToolWithName(commandName);
    if(!tool)
    {
        sLogger->Out(Logger::LogLevel::LOG_LEVEL_ERROR, "%s", "No command found with this name.");
        ListCommands();
        DoExit(1);
    }

    if(argc == 2) //if only the command name was given, show extended description
    {
        ShowExtendedDescription(executableName, commandName, tool);
        DoExit(0);
    } else { //if command argument(s) is/are given
        unsigned int argCount = argc - 2;
        if(argCount < tool->GetMinArgumentCount())
        {
            sLogger->Out(Logger::LogLevel::LOG_LEVEL_ERROR, "%s", "Too few arguments.");
            PrintUsage(executableName, commandName, tool);
            DoExit(0);
        } else if (argCount > tool->GetMaxArgumentCount())
        {
            sLogger->Out(Logger::LogLevel::LOG_LEVEL_ERROR, "%s", "Too much arguments.");
            PrintUsage(executableName, commandName, tool);
            DoExit(0);
        }
    }

    //all okay let's get to work
    int error = tool->Work(argc, argv);

    DoExit(error);
}