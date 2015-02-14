#ifndef MCAL_H
#define MCAL_H

#include "chunkHeader.h"

class MCAL {
public:
	char* fill;
	unsigned int size;

	MCAL(std::fstream& adtFile, unsigned int startByte){
		adtFile.seekg(startByte);
		chunkHeader CHeader(adtFile);
		size = CHeader.chunkSize;
		fill = new char[size];
		adtFile.read(fill, size);
	}
	friend std::ostream& operator<< (std::ostream &stream, MCAL& me) {
		chunkHeader CHeader("MCAL", me.size);
		stream << CHeader;

		stream.write(me.fill, me.size);		

		return stream;
	}
};

#endif