#include "CharArrayChunk.h"
#include "logger.h"

CharArrayChunk::CharArrayChunk(std::string_view name, std::fstream& adtFile, unsigned int startByte)
{  
    adtFile.seekg(startByte);
    ChunkHeader CHeader(adtFile);
    size = CHeader.chunkSize;
    //std::cout << "read size = " << size << std::endl;
    fileNames.resize(size);
    adtFile.read(&fileNames[0], size);

    if (name.size() != CHUNK_NAME_SIZE)
        throw ("Invalid chunk name");

    for (unsigned int i = 0; i < CHUNK_NAME_SIZE; ++i)
        chunkName[i] = name[i];

    if (size == 0)
        sLogger->Out(Logger::LOG_LEVEL_DEBUG, "Warning - charArrayChunk(%s) : size = 0", chunkName);
};

std::ostream& operator<< (std::ostream& stream, const CharArrayChunk& me) 
{
    ChunkHeader CHeader(me.chunkName, me.size);
    stream << CHeader;
    stream.write(me.fileNames.c_str(), me.size);
    //std::cout << "writing size = " << me.size << std::endl;
    return stream;
};