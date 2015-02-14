#ifndef MCRF_H
#define MCRF_H

#include "chunkHeader.h"

class MCRF {
public:
	char* fill;
	unsigned int size;

	MCRF(std::fstream& adtFile, unsigned int startByte){
		//std::cout << "startbyte " << std::hex << startByte << std::endl;
		adtFile.seekg(startByte);
		chunkHeader CHeader(adtFile);
		size = CHeader.chunkSize;
		//std::cout << "size " << std::hex << size << std::endl;
		fill = new char[size];
		adtFile.read(fill, size);
	}
	friend std::ostream& operator<< (std::ostream &stream, MCRF& me) {
		chunkHeader CHeader("MCRF", me.size);
		stream << CHeader;

		stream.write(me.fill, me.size);		

		return stream;
	}
};

#endif