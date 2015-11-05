#ifndef H_COPY_MCLQ
#define H_COPY_MCLQ

#include "console_tool.h"

class CopyMCLQ : public ConsoleTool
{
public:
    CopyMCLQ() :
    ConsoleTool(
        //command name
        "copywater",
        //version
        "0.1",
        //short description
        "Copy 'MCLQ' water (pre-LK water) from an adt to another",
        //full description
        "Copy 'MCLQ' water (pre-LK water) from an adt to another.",
        //arguments
        { 
            ToolArgument("source adt", "Copy water from this adt"), 
            ToolArgument("target adt", "Copy water to this adt") 
        }
    )
    { }

	int Work(int argc, char* argv[]) override;
};

#endif //H_COPY_MCLQ