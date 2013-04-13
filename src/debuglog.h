#ifndef DEBUGLOG_H
#define DEBUGLOG_H
#include <fstream>
#include <iostream>

class DebugLog
{
public:
	DebugLog();
	DebugLog(const char* str, bool doprint = false);
	~DebugLog();

	void log(_In_z_ _Printf_format_string_ const char* str, ...);
	
	std::ofstream* logFile;
	bool print;
};
#endif