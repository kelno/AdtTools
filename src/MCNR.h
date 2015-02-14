#ifndef MCNR_H
#define MCNR_H

#include "chunkHeader.h"

class MCNR {
public:
	char data[435];
	char unknown[13];

	MCNR(std::fstream& adtFile, unsigned int startByte) {
		adtFile.seekg(sizeof(chunkHeader), std::ios_base::cur);
		adtFile.read(reinterpret_cast<char *>(data), sizeof(MCNR));
	}
	friend std::ostream& operator<< (std::ostream &stream, MCNR& me) {
		chunkHeader CHeader("MCNR",sizeof(char)*435);
		//chunkHeader CHeader("MCNR",sizeof(data));
		stream << CHeader;
		stream.write(reinterpret_cast<char *>(me.data),sizeof(MCNR));

		return stream;
	}
};

#endif