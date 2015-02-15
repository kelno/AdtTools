#include <iostream>
#include <cstdio>
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
		std::cout << "AdtTools CopyPreWotLKWater v" << VERSION << std::endl;
        std::cout << std::endl;
        std::cout << "Description : This tool copy 'MCLQ' water from one adt to another. This tool will NOT copy 'MH20' water, "
                     "no water from LK maps or later will be copied." << std::endl;
        std::cout << "Tool by " << AUTHOR << std::endl;
        std::cout << std::endl;
        std::cout << "Usage : CopyPreWotLKWater <target> <source>" << std::endl;
        pauseAndExit();
	} 
	
	std::fstream adtFileTarget(argv[1], std::ios::in | std::ios::out | std::ios::binary);
	std::fstream adtFileSource(argv[2], std::ios::in | std::ios::binary);
	
    if(!adtFileTarget.is_open())
    {
        if(adtFileSource.is_open())
            adtFileSource.close();

        std::cerr << "Could not open target file : " << argv[1] << std::endl;
        exit(0);
    }

    if(!adtFileSource.is_open())
    { 
        if(adtFileTarget.is_open())
            adtFileTarget.close();

        std::cerr << "Could not open source file : " << argv[2] << std::endl;
        pauseAndExit();
    }

	adt AdtTarget(adtFileTarget);
	adt AdtFrom(adtFileSource);
		
	for (int i = 0; i < MCNK::ENTRY_COUNT; i++)
		AdtTarget.mcnk->entries[i].mclq = AdtFrom.mcnk->entries[i].mclq;

	AdtTarget.writeToDisk(adtFileTarget);
	adtFileTarget.close();
	adtFileSource.close();

    pauseAndExit();
}