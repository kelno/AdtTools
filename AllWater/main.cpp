#include <iostream>
#include "adt.h"

#define VERSION "0.1"

void pauseAndExit()
{
    std::cout << "Press any key to exit...";
    std::getchar();
	exit(0);
}

void main(int argc, char* argv[])
{
	if(argc < 3)
	{
		std::cout << "AdtTools AllWaterPreWotLK v" << VERSION << std::endl;
        std::cout << std::endl;
        std::cout << "Description : This tool adds 'MCLQ' water that can be parsed by clients of all versions. "
                     "You should still prefer using the usual AllWater for >= LK clients, which put 'MH20' water, "
                     "and most tools only supports this one." << std::endl;
        std::cout << "Tool by " << AUTHOR << std::endl;
        std::cout << std::endl;
        std::cout << "Usage : adtools <adt file> <height>" << std::endl;
		pauseAndExit();
	}

	std::fstream adtFile(argv[1], std::ios::in | std::ios::out |std::ios::binary);
	float height = (float)atof(argv[2]);

	if (!adtFile.is_open()) {
        std::cerr << "Could not open file : " << argv[1];
        exit(0);
    }

	std::cout << "Setting water to " << height << std::endl;
	adt ADT(adtFile);

	ADT.allWaterMCLQ(height);

	ADT.writeToDisk(adtFile);
	adtFile.close();
}