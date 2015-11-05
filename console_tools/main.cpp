#include <iostream>
#include <vector>
#include <list>

#include "template/console_tool_template.h"
#include "all_water_MCLQ\AllWaterMCLQ.h"
#include "version.h"

std::list<ConsoleTool*> tools;

/* Create all tools into tools list */
void InitTools()
{
    tools.push_back((ConsoleTool*)new AllWaterMCLQ());
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
    std::cout << "Commands list:" << std::endl;
    for(auto itr : tools)
        std::cout << "  " << itr->GetCommandName() << " - " << itr->GetShortDescription() << std::endl;
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
    std::cout << "Usage: " << commandName;
    for(auto arg : arguments)
        std::cout << " <" << arg.name << ">"; 

    std::cout << std::endl;
}

void ShowExtendedDescription(std::string const& executableName, std::string const& commandName, ConsoleTool const* tool)
{
    std::cout << "Description: " << std::endl;
    std::cout << "  " << tool->GetFullDescription() << std::endl << std::endl;
    PrintUsage(executableName, commandName, tool);    
    std::cout << std::endl << "Version: " << tool->GetVersion() << std::endl;
}

void main(int argc, char* argv[])
{
    InitTools();

    //if no command given, list commands
	if(argc == 1)
	{
        std::cout << "AdtTools v" << ADTTOOLS_VERSION << std::endl;
        ListCommands();

		exit(0);
	} 
    
    //else if command given
    std::string executableName = argv[0];
    std::string commandName = argv[1];

    //check if command exists
    ConsoleTool* tool = GetToolWithName(commandName);
    if(!tool)
    {
        std::cout << "No command found with this name." << std::endl;
        ListCommands();
		exit(1);
    }

    if(argc == 2) //if only the command name was given, show extended description
    {
        ShowExtendedDescription(executableName, commandName, tool);
        exit(0);
    } else { //if command argument(s) is/are given
        unsigned int argCount = argc - 2;
        if(argCount < tool->GetMinArgumentCount())
        {
            std::cout << "Too few arguments." << std::endl;
            PrintUsage(executableName, commandName, tool);
            exit(0);
        } else if (argCount > tool->GetMaxArgumentCount())
        {
            std::cout << "Too much arguments." << std::endl;
            PrintUsage(executableName, commandName, tool);
            exit(0);
        }
    }

    //all okay let's get to work
    int error = tool->Work(argc, argv);

    //erase all tools
    DeleteTools();

    exit(error);
}