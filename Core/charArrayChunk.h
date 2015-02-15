#ifndef CHARARRAYCHUNK_H
#define CHARARRAYCHUNK_H

#include "chunkHeader.h"

class CharArrayChunk {
public:
  unsigned int size;
  char* fileNames;
  char* chunkName;

  CharArrayChunk() {};
  CharArrayChunk(char* name, std::fstream& adtFile, unsigned int startByte);

  friend std::ostream& operator<< (std::ostream& stream, const CharArrayChunk& me);
};


#endif