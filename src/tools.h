#include "adt.h"
#include <iostream>
#include <string>

void copyMCLQ(int argc, char* argv[])
{
	if(argc < 3)
	{
		std::cout << "AdtTools copyMCLQ \nUsage : adtools <to> <from>\n";
		exit(0);
	} 
	
	std::fstream adtFile(argv[1], std::ios::in | std::ios::out | std::ios::binary);
	std::fstream adtFile2(argv[2], std::ios::in | std::ios::binary);
	
	if (adtFile.is_open() && adtFile2.is_open())
	{
		adt ADT_TARGET(adtFile, new DebugLog());
		adt ADT_FROM(adtFile2, new DebugLog());
		
		for (int i = 0; i < 256; i++)
		{
			ADT_TARGET.mcnk->entries[i].mclq = ADT_FROM.mcnk->entries[i].mclq;
		}

		ADT_TARGET.writeToDisk(adtFile);
		adtFile.close();
		adtFile2.close();
	} else {
		std::cout << "Erreur fichier." << std::endl;
		std::cout << "to : " << argv[1] << std::endl;
		std::cout << "from : " << argv[2] << std::endl;
	}
}

void allWater(int argc, char* argv[])
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

void justOpen(int argc, char* argv[])
{
	if(argc < 2)
	{
		std::cout << "AdtTools justOpen \nUsage : adtools <adt file>\n";
		exit(0);
	}

	std::fstream adtFile(argv[1], std::ios::in | std::ios::out | std::ios::binary);
	
	if (adtFile.is_open())
	{
		adt ADT_TARGET(adtFile, new DebugLog("log.txt", true));
		
		adtFile.close();
	} else {
		std::cout << "Erreur fichier.";
	}
}

void Rewrite(int argc, char* argv[])
{
	if(argc < 3)
	{
		std::cout << "AdtTools Rewrite \nUsage : adtools <in adt file> <out adt file>\n";
		exit(0);
	}

	std::fstream adtFile(argv[1], std::ios::in | std::ios::binary);
	std::fstream adtFile2(argv[2], std::ios::out | std::ios::binary);
	
	if (adtFile.is_open() && adtFile2.is_open())
	{
		adt ADT(adtFile, new DebugLog());

		ADT.writeToDisk(adtFile2);
		adtFile.close();
		adtFile2.close();
	} else {
		std::cout << "Erreur fichier.";
	}
}