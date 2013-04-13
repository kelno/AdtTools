#include "debuglog.h"
#include <stdarg.h>

DebugLog::DebugLog() : 
	logFile(NULL),
	print(true)
{}

DebugLog::DebugLog(const char* str, bool doprint) : 
	logFile(new std::ofstream(str, std::ios::out)),
	print(doprint)
{}

DebugLog::~DebugLog() {
	if (logFile) (*logFile).close();
}
void DebugLog::log(const char* str, ...) {

	
		if( !str || (!print && !logFile))
			return;

		char buf[256];
		va_list ap;
		va_start(ap, str);
		vsnprintf(buf,256, str, ap);
		va_end(ap);
		if (print)
			std::cout << buf;
		if (logFile) 
			(*logFile) << str;
}