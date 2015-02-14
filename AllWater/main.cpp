#include <iostream>
#include "adt.h"

void main(int argc, char* argv[])
{
	if(argc < 3)
	{
		std::cout << "AdtTools allWater \nUsage : adtools <adt file> <height>\n";
		exit(0);
	}

	
	std::fstream adtFile(argv[1], std::ios::in | std::ios::out |std::ios::binary);
	float height = (float)atof(argv[2]);
	std::cout << "Setting water to " << height << std::endl;

	if (adtFile.is_open()) {
		adt ADT(adtFile, new DebugLog());
		for (int i = 0; i < 256; i++) {
			ADT.mcnk->entries[i].mclq = MCLQ::AllWater(height);
			ADT.mcnk->entries[i].header.flags |= MCNK_FLAG_LQ_RIVER;
		}
		
		ADT.writeToDisk(adtFile);
		adtFile.close();
	} else {
		std::cout << "Erreur fichier.";
	}
	
}