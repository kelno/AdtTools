#include <iostream>
#include "adt.h"

void main(int argc, char* argv[])
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
		std::cerr << "Erreur fichier." << std::endl;
		std::cerr << "to : " << argv[1] << std::endl;
		std::cerr << "from : " << argv[2] << std::endl;
	}
}