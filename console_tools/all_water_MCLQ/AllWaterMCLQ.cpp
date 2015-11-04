#include "console_tool_template.h"
#include "AllWaterMCLQ.h"
#include <sstream>
#include "adt.h"

int AllWaterMCLQ::Work(int argc, char* argv[])
{
    std::fstream adtFile(argv[2], std::ios::in | std::ios::out |std::ios::binary);
    //Todo : check if argument is a number
	float height = (float)atof(argv[3]);

	if (!adtFile.is_open()) {
        std::cerr << "Could not open file : " << argv[2];
        return 1;
    }

	std::cout << "Setting water to " << height << std::endl;
	adt ADT(adtFile);

	ADT.AllWaterMCLQ(height);

	ADT.WriteToDisk(adtFile);
	adtFile.close();

    return 0;
}