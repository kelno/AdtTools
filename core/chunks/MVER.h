#ifndef MVER_H
#define MVER_H

#include "chunkHeader.h"
#include "logger.h"

#define MVER_SIZE sizeof(int)

class MVER 
{
public:
	unsigned int version;

    //can throw
	MVER(std::fstream& adtFile)
	{ 
		adtFile.seekg(std::ios::beg);
		chunkHeader MVER_CHeader(adtFile);
		if (std::strncmp(MVER_CHeader.title,"REVM",4) != 0)
            throw("Invalid Header");

		adtFile.read(reinterpret_cast<char *>(&version), MVER_SIZE);
	}

	MVER(unsigned int version) :
		version(version)
	{}

	friend std::ostream& operator<< (std::ostream &stream, MVER& me){
		chunkHeader CHeader("MVER",4);
		stream << CHeader;
		stream.write(reinterpret_cast<char *>(&me.version), MVER_SIZE);

		return stream;
	}
};

#endif