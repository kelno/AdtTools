#include "CharArrayChunk.h"
#include "logger.h"

CharArrayChunk::CharArrayChunk(char* name, std::fstream& adtFile, unsigned int startByte)
  {  
	adtFile.seekg(startByte);
	chunkHeader CHeader(adtFile);
	size = CHeader.chunkSize;
	//std::cout << "read size = " << size << std::endl;
	fileNames = new char[size];
	adtFile.read(fileNames, size);
	chunkName = name;

	if(size == 0)
        sLogger->OutMessage(Logger::LOG_LEVEL_DEBUG, "Warning - charArrayChunk(%s) : size = 0", chunkName);
  };

std::ostream& operator<< (std::ostream& stream, const CharArrayChunk& me){
	//std::cout << me.debug_log; //ca a pas la bonne valeur, why?
	//me.debug_log->log("\nlol\n");
	chunkHeader CHeader(me.chunkName,me.size);
	stream << CHeader;
	stream.write(me.fileNames,me.size);
	//std::cout << "writing size = " << me.size << std::endl;
	return stream;
};