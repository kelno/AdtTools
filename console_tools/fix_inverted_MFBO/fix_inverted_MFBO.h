#ifndef H_FIX_INVERTED_MFBO
#define H_FIX_INVERTED_MFBO

#include "console_tool.h"

/** This tool will fix the noggit out of bound camera.
The bug is caused by Noggit somehow saving MFBO coordinates with min and max reversed.
This tool will check if the given adt has the problem, fix it if needed, else do nothing (no file rewrite).
*/
class FixInvertedMFBO : public ConsoleTool
{
public:
    FixInvertedMFBO() :
    ConsoleTool(
        //command name
        "fixcamera",
        //version
        "0.1",
        //short description
        "Fix out of bounds camera bug induced by Noggit",
        //full description
        "Fix out of bounds camera bug induced by Noggit (corrupted MFBO data). This tool will have no effect if the given adt has not this bug.",
        //arguments
        { 
            ToolArgument("target adt", "Fix this adt"), 
        }
    )
    { }

	int Work(int argc, char* argv[]) override;
};

#endif //H_FIX_INVERTED_MFBO