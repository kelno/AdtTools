#ifndef MCVT_H
#define MCVT_H

#include "chunkHeader.h"

class MCVT {
public:
	float heightMap[145];

	MCVT(std::fstream& adtFile, unsigned int startByte) {
		adtFile.seekg(sizeof(chunkHeader), std::ios_base::cur);
		adtFile.read(reinterpret_cast<char *>(heightMap), sizeof(MCVT));
	};
	friend std::ostream& operator<< (std::ostream &stream, MCVT& me) {
		chunkHeader CHeader("MCVT",sizeof(MCVT));
		stream << CHeader;
		stream.write(reinterpret_cast<char *>(me.heightMap),sizeof(MCVT));

		return stream;
	};
};

#endif