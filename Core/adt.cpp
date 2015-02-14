#include "adt.h"

#define MHDR_OFFSET (2*sizeof(chunkHeader) + MVER_SIZE)
using namespace std;

adt::adt(fstream& adtFile, DebugLog* debuglog) :
	debug_log(debuglog)
{
	if(!debug_log)
		debug_log = new DebugLog();

	debug_log->log("Extracting adt data :\n");
	adtFile.seekg(0, std::ios_base::beg); 
	try {
		debug_log->log("Extracting mver...\n");
		mver = new MVER(adtFile, debug_log);
	} catch (char* e) {
		debug_log->log(e);
		debug_log->log("Is this an adt file? Aborting...\n");
		exit(1);
	}
	try {
		debug_log->log("Extracting mhdr...\n");
		mhdr = new MHDR(adtFile, MHDR_OFFSET - sizeof(chunkHeader));
	} catch (char* e) {
		debug_log->log(e);
		debug_log->log("Cannot continue, aborting... %xh\n", (int)adtFile.tellg());

		exit(1);
	}
	//lesquels peuvent etre vides? Check des chunks perdus dans le vide
	if (mhdr->offsMCIN) {
		try {
			debug_log->log("Extracting mcin...\n");
			if (mhdr->offsMCIN) mcin = new MCIN(adtFile, MHDR_OFFSET + mhdr->offsMCIN);
		} catch (char* e) {
			debug_log->log(e);
		}
	}
	if (mhdr->offsMTEX) {
		try {
			debug_log->log("Extracting mtex...\n");
			mtex = new MTEX(adtFile, MHDR_OFFSET + mhdr->offsMTEX, debug_log);
			//std::cout << mtex->debug_log << endl;
		} catch (char* e) {
			debug_log->log(e);
		}
	}  else
		mtex = nullptr;

	debug_log->log("Extracting mmdx...\n");
	if (mhdr->offsMMDX) mmdx = new MMDX(adtFile, MHDR_OFFSET + mhdr->offsMMDX, debug_log); else mmdx = nullptr;
	debug_log->log("Extracting mmid...\n");
	if (mhdr->offsMMID) mmid = new MMID(adtFile, MHDR_OFFSET + mhdr->offsMMID);	else mmid = nullptr;
	debug_log->log("Extracting mwmo...\n");
	if (mhdr->offsMWMO) mwmo = new MWMO(adtFile, MHDR_OFFSET + mhdr->offsMWMO, debug_log); else mwmo = nullptr;
	debug_log->log("Extracting mwid...\n");
	if (mhdr->offsMWID) mwid = new MWID(adtFile, MHDR_OFFSET + mhdr->offsMWID); else mwid = nullptr;
	debug_log->log("Extracting mddf...\n");
	if (mhdr->offsMDDF) mddf = new MDDF(adtFile, MHDR_OFFSET + mhdr->offsMDDF); else mddf = nullptr;
	debug_log->log("Extracting modf...\n");
	if (mhdr->offsMODF) modf = new MODF(adtFile, MHDR_OFFSET + mhdr->offsMODF); else modf = nullptr;

	debug_log->log("Extracting mcnk...\n");
	mcnk = new MCNK(adtFile, mcin);

	debug_log->log("Extracting mfbo...\n");
	if (mhdr->offsMFBO)	mfbo = new MFBO(adtFile, MHDR_OFFSET + mhdr->offsMFBO); else mfbo = nullptr;
	debug_log->log("Extracting mh2o...\n");
	if (mhdr->offsMH2O)	mh2o = new MH2O(adtFile, MHDR_OFFSET + mhdr->offsMH2O); else mh2o = nullptr;
	debug_log->log("Extracting mtxf...\n");
	if (mhdr->offsMTXF)	mtxf = new MTXF(adtFile, MHDR_OFFSET + mhdr->offsMTXF); else mtxf = nullptr;
	debug_log->log("Extracting done\n");

	//ValidityCheck
}

void adt::writeToDisk(fstream& adtFile)
{
	debug_log->log("Writing adt data : \n");
	adtFile.seekp(0, std::ios_base::beg); 
	adtFile << (*mver);
	adtFile.seekp(sizeof(MHDR) + sizeof(chunkHeader), std::ios_base::cur); //reserving, mhdr written at the end

	mhdr->offsMCIN = (unsigned int)adtFile.tellp() - MHDR_OFFSET;
	adtFile.seekp(sizeof(MCIN) + sizeof(chunkHeader), std::ios_base::cur); //reserving, mcin written at the end
	
	if(mtex) {
		debug_log->log("Writing mtex...\n");
		mhdr->offsMTEX = (unsigned int)adtFile.tellp() - MHDR_OFFSET;
		//std::cout << mtex->debug_log << endl;
		adtFile << (*mtex);
		//debug_log->log("ha\n");
	} else { mhdr->offsMCIN = NULL; }
	if(mmdx) {
		debug_log->log("Writing mmdx...\n");
		mhdr->offsMMDX = (unsigned int)adtFile.tellp() - MHDR_OFFSET;
		adtFile << (*mmdx);
	} else { mhdr->offsMMDX = NULL; }
	if(mmid) {
		debug_log->log("Writing mmid...\n");
		mhdr->offsMMID = (unsigned int)adtFile.tellp() - MHDR_OFFSET;
		adtFile << (*mmid);
	} else { mhdr->offsMMID = NULL; }
	if(mwmo) {
		debug_log->log("Writing mwmo...\n");
		mhdr->offsMWMO = (unsigned int)adtFile.tellp() - MHDR_OFFSET;
		adtFile << (*mwmo);
	} else { mhdr->offsMWMO = NULL; }
	if(mwid) {
		debug_log->log("Writing mwmo...\n");
		mhdr->offsMWID = (unsigned int)adtFile.tellp() - MHDR_OFFSET;
		adtFile << (*mwid);
	} else { mhdr->offsMWID = NULL; }
	if(mddf) {
		debug_log->log("Writing mddf...\n");
		mhdr->offsMDDF = (unsigned int)adtFile.tellp() - MHDR_OFFSET;
		adtFile << (*mddf);
	} else { mhdr->offsMDDF = NULL; }
	if(modf) {
		debug_log->log("Writing modf...\n");
		mhdr->offsMODF = (unsigned int)adtFile.tellp() - MHDR_OFFSET;
		adtFile << (*modf);
	} else { mhdr->offsMODF = NULL; }

	debug_log->log("Writing mcnk...\n");
	mcnk->mcin = mcin; //update link
	adtFile << (*mcnk); 
	if(mfbo) {
		debug_log->log("Writing mfbo...\n");
		mhdr->offsMFBO = (unsigned int)adtFile.tellp() - MHDR_OFFSET;
		adtFile << (*mfbo);
	} else { mhdr->offsMFBO = NULL; }

	adtFile.seekp(32768, std::ios_base::cur);

	if(mh2o) {
		debug_log->log("Writing mh2o...\n");
		mhdr->offsMH2O = (unsigned int)adtFile.tellp() - MHDR_OFFSET;
		adtFile << (*mh2o);
	} else { mhdr->offsMH2O = NULL; }
	if(mtxf) {
		debug_log->log("Writing mtxf...\n");
		mhdr->offsMTXF = (unsigned int)adtFile.tellp() - MHDR_OFFSET;
		adtFile << (*mtxf);
	} else { mhdr->offsMTXF = NULL; }

	debug_log->log("Writing mhdr...\n");
	adtFile.seekp(MHDR_OFFSET - sizeof(chunkHeader)); //reserving, mhdr written at the end
	adtFile << (*mhdr);
	debug_log->log("Writing mcin...\n");
	adtFile << (*mcin);
}
