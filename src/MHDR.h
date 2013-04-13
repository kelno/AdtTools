#ifndef MHDR_H
#define MHDR_H

#include "chunkHeader.h"

//offsets relative to &MHDR.flags
class MHDR {
public:
	 /*000h*/  unsigned int flags;
	 /*004h*/  unsigned int offsMCIN;
	 /*008h*/  unsigned int offsMTEX;
	 /*00Ch*/  unsigned int offsMMDX;
	 /*010h*/  unsigned int offsMMID;
	 /*014h*/  unsigned int offsMWMO;
	 /*018h*/  unsigned int offsMWID;
	 /*01Ch*/  unsigned int offsMDDF;
	 /*020h*/  unsigned int offsMODF;
	 /*024h*/  unsigned int offsMFBO;
	 /*028h*/  unsigned int offsMH2O;
	 /*02Ch*/  unsigned int offsMTXF;
	 /*030h*/  unsigned int unused1;
	 /*034h*/  unsigned int unused2;
	 /*038h*/  unsigned int unused3;
	 /*03Ch*/  unsigned int unused4;
	 /*040h*/

	 MHDR(std::fstream& adtFile, unsigned int startByte) { 
		adtFile.seekg(startByte);
		chunkHeader MHDR_CHeader(adtFile);
		if (std::strncmp(MHDR_CHeader.title,"RDHM",4) != 0)
		{
			throw("MHDR constructor : Invalid Header\n");
		}

		adtFile.read(reinterpret_cast<char *>(&flags), sizeof(MHDR));
	 }

	 friend std::ostream& operator<< (std::ostream &stream, MHDR& me){
		chunkHeader CHeader("MHDR",sizeof(MHDR));
		stream << CHeader;
		stream.write((char*)&me.flags,sizeof(MHDR));

		return stream;
	}
};

#endif