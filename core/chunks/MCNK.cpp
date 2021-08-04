#include "MCNK.h"

MCNK::MCNK(std::fstream& adtFile, MCIN* mcin_) :
    mcin(mcin_)
{
    for (unsigned int i = 0; i < CHUNKS_PER_ADT; ++i)
    {
        //std::cout << i;
        unsigned int MCNKChunk_Start = (unsigned int)adtFile.tellg();
        adtFile.seekg(mcin->entries[i].mcnkOffs);
        chunkHeader CHeader(adtFile);
        mcin->entries[i].size = CHeader.chunkSize;
        adtFile.read(reinterpret_cast<char *>(&(entries[i].header.flags)), sizeof(MCNKHeader));
        if (entries[i].header.ofsMCVT) 
            entries[i].mcvt = std::make_unique<MCVT>(adtFile, MCNKChunk_Start + entries[i].header.ofsMCVT);
        if (entries[i].header.ofsMCNR) 
            entries[i].mcnr = std::make_unique<MCNR>(adtFile, MCNKChunk_Start + entries[i].header.ofsMCNR);
        if (entries[i].header.ofsMCLY) 
            entries[i].mcly = std::make_unique<MCLY>(adtFile, MCNKChunk_Start + entries[i].header.ofsMCLY);
        //std::cout << std::hex << MCNKChunk_Start << std::endl;
        //std::cout << std::hex << entries[i].header.ofsMCRF << std::endl;
        //std::cout << std::hex << MCNKChunk_Start + entries[i].header.ofsMCRF << std::endl;
        if (entries[i].header.ofsMCRF) 
            entries[i].mcrf = std::make_unique<MCRF>(adtFile, MCNKChunk_Start + entries[i].header.ofsMCRF);
        //if (i == 57) std::cout << "reading mcrf. Size = " << std::hex << entries[i].mcrf->size << std::endl;
        if (entries[i].header.ofsMCSH) 
            entries[i].mcsh = std::make_unique<MCSH>(adtFile, MCNKChunk_Start + entries[i].header.ofsMCSH);
        if (entries[i].header.ofsMCAL) 
            entries[i].mcal = std::make_unique<MCAL>(adtFile, MCNKChunk_Start + entries[i].header.ofsMCAL);
        if (entries[i].header.ofsMCLQ) 
            entries[i].mclq = std::make_unique<MCLQ>(adtFile, entries[i], MCNKChunk_Start + entries[i].header.ofsMCLQ, entries[i].header.sizeLiquid);
        //if (entries[i].header.sizeLiquid > 8) std::cout << i << " " << entries[i].header.sizeLiquid << std::endl; 
        if (entries[i].header.ofsMCSE) 
            entries[i].mcse = std::make_unique<MCSE>(adtFile, MCNKChunk_Start + entries[i].header.ofsMCSE);
        if (entries[i].header.ofsMCCV) 
            entries[i].mccv = std::make_unique<MCCV>(adtFile, MCNKChunk_Start + entries[i].header.ofsMCCV);

        adtFile.seekg(MCNKChunk_Start + sizeof(chunkHeader) + mcin->entries[i].size); //get ready for next entry

        /*entries[i].fill = new char[entries[i].size - sizeof(MCNKHeader)];
            
        adtFile.read(entries[i].fill, entries[i].size - sizeof(MCNKHeader));
        if (i == 255)
            std::cout << "im at " << std::hex << adtFile.tellg() << std::endl;*/
    }
}

std::ostream& operator<< (std::ostream& stream, MCNK& me) {
    for (unsigned int i = 0; i < CHUNKS_PER_ADT; ++i)
    {
        me.mcin->entries[i].mcnkOffs = (unsigned int)stream.tellp();
        //std::cout << "start " << std::hex << me.mcin->entries[i].mcnkOffs << std::endl;

        //reserving, written at the end
        stream.seekp(sizeof(chunkHeader), std::ios_base::cur); ////std::cout << "after cheader " << std::hex << stream.tellp() << std::endl;
        stream.seekp(sizeof(MCNKHeader), std::ios_base::cur);

        if (me.entries[i].mcvt) {
            me.entries[i].header.ofsMCVT = (unsigned int)stream.tellp() - me.mcin->entries[i].mcnkOffs;
            stream << (*me.entries[i].mcvt);
        }
        else { me.entries[i].header.ofsMCVT = NULL; }

        if (me.entries[i].mcnr) {
            me.entries[i].header.ofsMCNR = (unsigned int)stream.tellp() - me.mcin->entries[i].mcnkOffs;
            stream << (*me.entries[i].mcnr);
        }
        else { me.entries[i].header.ofsMCNR = NULL; }

        if (me.entries[i].mcly) {
            me.entries[i].header.ofsMCLY = (unsigned int)stream.tellp() - me.mcin->entries[i].mcnkOffs;
            stream << (*me.entries[i].mcly);
        }
        else { me.entries[i].header.ofsMCLY = NULL; }

        if (me.entries[i].mcrf) {
            me.entries[i].header.ofsMCRF = (unsigned int)stream.tellp() - me.mcin->entries[i].mcnkOffs;
            stream << (*me.entries[i].mcrf);
        }
        else { me.entries[i].header.ofsMCRF = NULL; }
        //if (i== 57) std::cout << "writing mcrf. Size = " << std::hex << (*me.entries[i].mcrf).size << std::endl;

        if (me.entries[i].mcsh) {
            me.entries[i].header.ofsMCSH = (unsigned int)stream.tellp() - me.mcin->entries[i].mcnkOffs;
            stream << (*me.entries[i].mcsh);
        }
        else { me.entries[i].header.ofsMCSH = NULL; }

        if (me.entries[i].mcal) {
            me.entries[i].header.ofsMCAL = (unsigned int)stream.tellp() - me.mcin->entries[i].mcnkOffs;
            stream << (*me.entries[i].mcal);
        }
        else { me.entries[i].header.ofsMCAL = NULL; }

        if (me.entries[i].mclq) {
            me.entries[i].header.ofsMCLQ = (unsigned int)stream.tellp() - me.mcin->entries[i].mcnkOffs;
            me.entries[i].header.sizeLiquid = me.entries[i].mclq->sizeLiquid;
            stream << (*me.entries[i].mclq);
        }
        else { me.entries[i].header.ofsMCLQ = NULL; }

        if (me.entries[i].mcse) {
            me.entries[i].header.ofsMCSE = (unsigned int)stream.tellp() - me.mcin->entries[i].mcnkOffs;
            stream << (*me.entries[i].mcse);
        }
        else { me.entries[i].header.ofsMCSE = NULL; }

        if (me.entries[i].mccv) {
            me.entries[i].header.ofsMCCV = (unsigned int)stream.tellp() - me.mcin->entries[i].mcnkOffs;
            stream << (*me.entries[i].mccv);
        }
        else { me.entries[i].header.ofsMCCV = NULL; }

        //std::cout << "end " << std::hex << stream.tellp() << std::endl;
        me.mcin->entries[i].size = (unsigned int)stream.tellp() - (me.mcin->entries[i].mcnkOffs);
        //std::cout << "size =  " << me.mcin->entries[i].size << std::endl;
        stream.seekp(me.mcin->entries[i].mcnkOffs);
        chunkHeader CHeader("MCNK", me.mcin->entries[i].size - sizeof(chunkHeader));
        stream << CHeader;
        stream.write(reinterpret_cast<char*>(&(me.entries[i].header)), sizeof(MCNKHeader));
        stream.seekp(me.mcin->entries[i].mcnkOffs + me.mcin->entries[i].size); //ready for next
    }
    return stream;
}