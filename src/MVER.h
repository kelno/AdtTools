#ifndef MVER_H
#define MVER_H

#include "chunkHeader.h"
#include "debuglog.h"

#define MVER_SIZE sizeof(int)

class MVER {
public:
	unsigned int version;

	MVER(std::fstream& adtFile, DebugLog* debug_log) :
		debug_log(debug_log)
	{ 
		adtFile.seekg(std::ios::beg);
		chunkHeader MVER_CHeader(adtFile);
		if (std::strncmp(MVER_CHeader.title,"REVM",4) != 0)
			debug_log->log("MVER constructor : Invalid Header\n");

		adtFile.read(reinterpret_cast<char *>(&version), MVER_SIZE);
	}

	MVER(unsigned int version, DebugLog* debug_log = NULL) :
		version(version),
		debug_log(debug_log)
	{}

	friend std::ostream& operator<< (std::ostream &stream, MVER& me){
		chunkHeader CHeader("MVER",4);
		stream << CHeader;
		stream.write(reinterpret_cast<char *>(&me.version), MVER_SIZE);

		return stream;
	}
private:
	DebugLog* debug_log;
};

#endif