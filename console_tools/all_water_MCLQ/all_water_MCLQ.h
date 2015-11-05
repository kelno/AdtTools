#ifndef H_ALL_WATER_MCLQ
#define H_ALL_WATER_MCLQ

#include "console_tool.h"

class AllWaterMCLQ : public ConsoleTool
{
public:
    AllWaterMCLQ() :
    ConsoleTool(
        //command name
        "allwater",
        //version
        "0.2",
        //short description
        "Fill adt with (pre-LK) water with given level",
        //full description
        "Adds 'MCLQ' water that can be parsed by clients of all versions. You should still prefer using the usual AllWater for >= LK clients, which put 'MH20' water, and most tools only supports this one.",
        //arguments
        { 
            ToolArgument("target adt", "Set water to this adt"), 
            ToolArgument("height", "Water height") 
        }
    )
    { }

	int Work(int argc, char* argv[]) override;
};

#endif //H_ALL_WATER_MCLQ