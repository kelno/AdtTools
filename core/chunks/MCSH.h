#ifndef MCSH_H
#define MCSH_H

#include "chunkHeader.h"

class MCSH {
public:
	char* fill;
	unsigned int size;

	MCSH(std::fstream& adtFile, unsigned int startByte){
		adtFile.seekg(startByte);
		chunkHeader CHeader(adtFile);
		size = CHeader.chunkSize;
		fill = new char[size];
		adtFile.read(fill, size);
	}
	friend std::ostream& operator<< (std::ostream &stream, MCSH& me) {
		chunkHeader CHeader("MCSH", me.size);
		stream << CHeader;

		stream.write(me.fill, me.size);		

		return stream;
	}
};

#endif