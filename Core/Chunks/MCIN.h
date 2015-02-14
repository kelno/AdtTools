#ifndef MCIN_H
#define MCIN_H

#include "chunkHeader.h"
//#include <vector>

struct MCINEntry 
{
	unsigned int mcnkOffs;                   // absolute offset.
	unsigned int size;                // the size of the MCNK chunk, this is refering to. (including cheader)
	unsigned int flags;               // these two are always 0. only set in the client.
	unsigned int asyncId;	
};

class MCIN {
public:
   MCINEntry entries[16*16];

  MCIN(std::fstream& adtFile, unsigned int startByte) {  
	adtFile.seekg(startByte);
	chunkHeader CHeader(adtFile);
	//if (std::strncmp(CHeader.title,"NICM",4) != 0)
	//	throw("MCIN constructor : Invalid Header\n");

	adtFile.read(reinterpret_cast<char *>(entries), sizeof(MCINEntry)*16*16);
  }

  unsigned int getMCNKSize(){
	  unsigned int sum = 0;
	  for (int i = 0; i < (16*16); i++) {
		  sum += entries[i].size;
	  }
	  return sum;
  }
  friend std::ostream& operator<< (std::ostream &stream, MCIN& me){
	chunkHeader CHeader("MCIN", sizeof(MCINEntry)*256);
	stream << CHeader;
	stream.write(reinterpret_cast<char *>(&me.entries),sizeof(MCINEntry)*16*16);

	return stream;
  }
};

#endif