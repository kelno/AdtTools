#ifndef MTXF_H
#define MTXF_H

#include "chunkHeader.h"

class MTXF {
public:
   unsigned int size;
   unsigned int* mode; //nMTXF

   MTXF(std::fstream& adtFile, unsigned int startByte) { 
	adtFile.seekg(startByte);
	chunkHeader MTXFHeader(adtFile);
	size = MTXFHeader.chunkSize;
	mode = (unsigned int*)new char[size];
	adtFile.read(reinterpret_cast<char *>(mode), size);
  }
   friend std::ostream& operator<< (std::ostream &stream, MTXF& me){
		chunkHeader CHeader("MTXF",me.size);
		stream << CHeader;
		stream.write(reinterpret_cast<char *>(me.mode),me.size);

		return stream;
	}
};

#endif