#ifndef INTARRAYCHUNK_H
#define INTARRAYCHUNK_H

#include "chunkHeader.h"

class IntArrayChunk {
public:
  unsigned int size;
  unsigned int* offsets;

  IntArrayChunk() {};
  IntArrayChunk(std::fstream& adtFile, unsigned int startByte) {  
	adtFile.seekg(startByte);
	chunkHeader CHeader(adtFile);
	size = CHeader.chunkSize;
	offsets = (unsigned int*)new char[size];
	adtFile.read(reinterpret_cast<char *>(offsets), size);
  };
  /*unsigned int getSize() {
	  return size;
  };*/
};

#endif