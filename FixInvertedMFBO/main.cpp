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
		std::cout << "AdtTools FixCamera v" << VERSION << std::endl;
        std::cout << std::endl;
        std::cout << "Description : This tool fixes the 'MFBO bug' sometimes induced by noggit which causes the camera to stay far up the player." << std::endl;
        std::cout << "Tool by " << AUTHOR << std::endl;
        std::cout << std::endl;
        std::cout << "Usage : FixCamera <adt file(s)>" << std::endl;
        std::cout << "        You can drag & drop files into this exe as well." << std::endl;
		pauseAndExit();
	}

    for(int i = 1; i < argc; i++) {
	    std::fstream adtFile(argv[i], std::ios::in | std::ios::out | std::ios::binary);

	    if (!adtFile.is_open()) {
            std::cerr << "Could not open file : " << argv[1];
            continue;
        }

	    adt ADT(adtFile);

        if(ADT.mfbo->hasInvertedMinMax())
        {
            std::cout <<  argv[1] << " has inverted coordinates, fixing it." << std::endl;
            ADT.mfbo->invertMinMax();
	        ADT.writeToDisk(adtFile);
        } else {
            std::cout << argv[1] << " seems already correct, nothing to do." << std::endl;
        }

	    adtFile.close();
    }
    std::cout << "Finished!";
}