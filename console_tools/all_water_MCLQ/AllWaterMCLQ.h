#ifndef H_ALL_WATER_MCLQ
#define H_ALL_WATER_MCLQ

#include "console_tool_template.h"

class AllWaterMCLQ : ConsoleTool
{
public:
    AllWaterMCLQ() :
    ConsoleTool(
        //version
        "0.1",
        //quick description
        "WATER EVERYWHERE",
        //full description
        "Adds 'MCLQ' water that can be parsed by clients of all versions. You should still prefer using the usual AllWater for >= LK clients, which put 'MH20' water, and most tools only supports this one.",
        //arguments
        { 
            ToolArgument("adt file"), 
            ToolArgument("height") 
        }
    )
    { }

	int Work(int argc, char* argv[]) override;
};

#endif