#ifndef MCSE_H
#define MCSE_H

#include "chunkHeader.h"

class MCSE {
public:
	char* fill;
	unsigned int size;

	MCSE(std::fstream& adtFile, unsigned int startByte){
		adtFile.seekg(startByte);
		chunkHeader CHeader(adtFile);
		size = CHeader.chunkSize;
		fill = new char[size];
		adtFile.read(fill, size);
	}
	friend std::ostream& operator<< (std::ostream &stream, MCSE& me) {
		chunkHeader CHeader("MCSE", me.size);
		stream << CHeader;

		stream.write(me.fill, me.size);		

		return stream;
	}
};

#endif