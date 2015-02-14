#include "MCNK.h"

MCNK::MCNK(std::fstream& adtFile, MCIN* mcin_) {
	mcin = mcin_;
	//totalSize = mcin->getMCNKSize();
	for (int i = 0; i < (16*16); i++) 
	{
		//std::cout << i;
		unsigned int MCNKChunk_Start = (unsigned int)adtFile.tellg();
		adtFile.seekg(mcin->entries[i].mcnkOffs);
		chunkHeader CHeader(adtFile);
		mcin->entries[i].size = CHeader.chunkSize;
		adtFile.read(reinterpret_cast<char *>(&(entries[i].header.flags)), sizeof(MCNKHeader));
		if (entries[i].header.ofsMCVT) entries[i].mcvt = new MCVT(adtFile, MCNKChunk_Start + entries[i].header.ofsMCVT); else entries[i].mcvt = nullptr;
		if (entries[i].header.ofsMCNR) entries[i].mcnr = new MCNR(adtFile, MCNKChunk_Start + entries[i].header.ofsMCNR); else entries[i].mcnr = nullptr;
		if (entries[i].header.ofsMCLY) entries[i].mcly = new MCLY(adtFile, MCNKChunk_Start + entries[i].header.ofsMCLY); else entries[i].mcly = nullptr;
		//std::cout << std::hex << MCNKChunk_Start << std::endl;
		//std::cout << std::hex << entries[i].header.ofsMCRF << std::endl;
		//std::cout << std::hex << MCNKChunk_Start + entries[i].header.ofsMCRF << std::endl;
		if (entries[i].header.ofsMCRF) entries[i].mcrf = new MCRF(adtFile, MCNKChunk_Start + entries[i].header.ofsMCRF); else entries[i].mcrf = nullptr;
		//if (i == 57) std::cout << "reading mcrf. Size = " << std::hex << entries[i].mcrf->size << std::endl;
		if (entries[i].header.ofsMCSH) entries[i].mcsh = new MCSH(adtFile, MCNKChunk_Start + entries[i].header.ofsMCSH); else entries[i].mcsh = nullptr;
		if (entries[i].header.ofsMCAL) entries[i].mcal = new MCAL(adtFile, MCNKChunk_Start + entries[i].header.ofsMCAL); else entries[i].mcal = nullptr;
		if (entries[i].header.ofsMCLQ) entries[i].mclq = new MCLQ(adtFile, MCNKChunk_Start + entries[i].header.ofsMCLQ, entries[i].header.sizeLiquid); else entries[i].mclq = nullptr;
		//if (entries[i].header.sizeLiquid > 8) std::cout << i << " " << entries[i].header.sizeLiquid << std::endl; 
		if (entries[i].header.ofsMCSE) entries[i].mcse = new MCSE(adtFile, MCNKChunk_Start + entries[i].header.ofsMCSE); else entries[i].mcse = nullptr;
		if (entries[i].header.ofsMCCV) entries[i].mccv = new MCCV(adtFile, MCNKChunk_Start + entries[i].header.ofsMCCV); else entries[i].mccv = nullptr;
		adtFile.seekg(MCNKChunk_Start + sizeof(chunkHeader) + mcin->entries[i].size); //ready for next

		/*entries[i].fill = new char[entries[i].size - sizeof(MCNKHeader)];
			
		adtFile.read(entries[i].fill, entries[i].size - sizeof(MCNKHeader));
		if (i == 255)
			std::cout << "im at " << std::hex << adtFile.tellg() << std::endl;*/
	}
}

std::ostream& operator<< (std::ostream &stream, MCNK& me) {
	for (int i = 0; i < (16*16); i++)
	//int i = 1;
	{
		me.mcin->entries[i].mcnkOffs = (unsigned int)stream.tellp();
		//std::cout << "start " << std::hex << me.mcin->entries[i].mcnkOffs << std::endl;

		 //reserving, written at the end
		stream.seekp(sizeof(chunkHeader), std::ios_base::cur); ////std::cout << "after cheader " << std::hex << stream.tellp() << std::endl;
		stream.seekp(sizeof(MCNKHeader), std::ios_base::cur);

		if(me.entries[i].mcvt) {
			me.entries[i].header.ofsMCVT = (unsigned int)stream.tellp() - me.mcin->entries[i].mcnkOffs;
			stream << (*me.entries[i].mcvt);
		} else { me.entries[i].header.ofsMCVT = NULL; }

		if(me.entries[i].mcnr) {
			me.entries[i].header.ofsMCNR = (unsigned int)stream.tellp() - me.mcin->entries[i].mcnkOffs;
			stream << (*me.entries[i].mcnr);
		} else { me.entries[i].header.ofsMCNR = NULL; }

		if(me.entries[i].mcly) {
			me.entries[i].header.ofsMCLY = (unsigned int)stream.tellp() - me.mcin->entries[i].mcnkOffs;
			stream << (*me.entries[i].mcly);
		} else { me.entries[i].header.ofsMCLY = NULL; }

		if(me.entries[i].mcrf) {
			me.entries[i].header.ofsMCRF = (unsigned int)stream.tellp() - me.mcin->entries[i].mcnkOffs;
			stream << (*me.entries[i].mcrf);
		} else { me.entries[i].header.ofsMCRF = NULL; }
		//if (i== 57) std::cout << "writing mcrf. Size = " << std::hex << (*me.entries[i].mcrf).size << std::endl;

		if(me.entries[i].mcsh) {
			me.entries[i].header.ofsMCSH = (unsigned int)stream.tellp() - me.mcin->entries[i].mcnkOffs;
			stream << (*me.entries[i].mcsh);
		} else { me.entries[i].header.ofsMCSH = NULL; }

		if(me.entries[i].mcal) {
			me.entries[i].header.ofsMCAL = (unsigned int)stream.tellp() - me.mcin->entries[i].mcnkOffs;
			stream << (*me.entries[i].mcal);
		} else { me.entries[i].header.ofsMCAL = NULL; }

		if(me.entries[i].mclq) {
			me.entries[i].header.ofsMCLQ = (unsigned int)stream.tellp() - me.mcin->entries[i].mcnkOffs;
			me.entries[i].header.sizeLiquid = me.entries[i].mclq->sizeLiquid;
			stream << (*me.entries[i].mclq);
		} else { me.entries[i].header.ofsMCLQ = NULL; }

		if(me.entries[i].mcse) {
			me.entries[i].header.ofsMCSE = (unsigned int)stream.tellp() - me.mcin->entries[i].mcnkOffs;
			stream << (*me.entries[i].mcse);
		} else { me.entries[i].header.ofsMCSE = NULL; }

		if(me.entries[i].mccv) {
			me.entries[i].header.ofsMCCV = (unsigned int)stream.tellp() - me.mcin->entries[i].mcnkOffs;
			stream << (*me.entries[i].mccv);
		} else { me.entries[i].header.ofsMCCV = NULL; }

		//std::cout << "end " << std::hex << stream.tellp() << std::endl;
		me.mcin->entries[i].size = (unsigned int)stream.tellp() - (me.mcin->entries[i].mcnkOffs);
		//std::cout << "size =  " << me.mcin->entries[i].size << std::endl;
		stream.seekp(me.mcin->entries[i].mcnkOffs);
		chunkHeader CHeader("MCNK",me.mcin->entries[i].size - sizeof(chunkHeader));
		stream << CHeader;
		stream.write(reinterpret_cast<char *>(&(me.entries[i].header)),sizeof(MCNKHeader));
		stream.seekp(me.mcin->entries[i].mcnkOffs + me.mcin->entries[i].size); //ready for next
	}
	return stream;
}