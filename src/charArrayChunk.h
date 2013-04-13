#ifndef CHARARRAYCHUNK_H
#define CHARARRAYCHUNK_H

#include "chunkHeader.h"
#include "debuglog.h"

class CharArrayChunk {
public:
  unsigned int size;
  char* fileNames;
  char* chunkName;

  CharArrayChunk() {};
  CharArrayChunk(char* name, std::fstream& adtFile, unsigned int startByte, DebugLog* debuglog);
/*  unsigned int getSize() {
	  return size;
  };*/
	friend std::ostream& operator<< (std::ostream& stream, const CharArrayChunk& me);

	DebugLog* debug_log;
};


#endif