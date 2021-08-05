#include "chunkHeader.h"

ChunkHeader::ChunkHeader(std::string_view str, unsigned int size) :
        chunkSize(size) 
{
    if (str.size() != CHUNK_NAME_SIZE)
        throw ("Invalid chunk name size");

    title[0] = str[3];
    title[1] = str[2];
    title[2] = str[1];
    title[3] = str[0];
}

ChunkHeader::ChunkHeader(ChunkName _title, unsigned int size) :
    chunkSize(size),
    title(_title)
{
}

ChunkHeader::ChunkHeader(std::fstream& adtFile)
{
    adtFile.read(reinterpret_cast<char *>(this), sizeof(ChunkHeader));
}

std::ostream& operator<< (std::ostream &stream, ChunkHeader& me) 
{
    stream.write(reinterpret_cast<char*>(&me), sizeof(ChunkHeader));
    return stream;
}

void ChunkHeader::CheckTitle(std::string_view checkTitle) const
{
    if (checkTitle.size() != CHUNK_NAME_SIZE)
        throw ("Invalid chunk name size");

    for (unsigned int i = 0; i < CHUNK_NAME_SIZE; ++i)
        if (title[i] != checkTitle[CHUNK_NAME_SIZE - 1 - i])
            throw ("Invalid chunk name");
}