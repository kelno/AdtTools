#ifndef MCCV_H
#define MCCV_H

#include "chunkHeader.h"

class MCCV {
public:
	char* fill;
	unsigned int size;

	MCCV(std::fstream& adtFile, unsigned int startByte){
		adtFile.seekg(startByte);
		chunkHeader CHeader(adtFile);
		size = CHeader.chunkSize;
		fill = new char[size];
		adtFile.read(fill, size);
	}
	friend std::ostream& operator<< (std::ostream &stream, MCCV& me) {
		chunkHeader CHeader("MCCV", me.size);
		stream << CHeader;

		stream.write(me.fill, me.size);		

		return stream;
	}
};

#endif