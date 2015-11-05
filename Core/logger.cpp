#include "logger.h"
#include <sstream>
#include <chrono>
#include <iostream>
#include <cstdarg>

Logger::Logger(LogLevel level) :
    logLevel(level)
{
    //init logger
    sLogger->Start();
#ifdef DEBUG_MODE
    sLogger->SetLogLevel(Logger::LOG_LEVEL_DEBUG);
#endif
}

Logger::~Logger() {

}

Logger::LogLevel Logger::GetLogLevel() const {
    return logLevel;
}

void Logger::SetLogLevel(LogLevel level) {
    logLevel = level;
}

void Logger::Out(LogLevel level, const char* msg, ...) {
    va_list ap;
    va_start(ap, msg);
    char text[1024] = {};
    vsnprintf(text, 1024, msg, ap);
    va_end(ap); 
    
    std::lock_guard<std::mutex> lock(queueMutex);
    outputQueue.push(std::make_pair(level, text));
}

void Logger::Run() {
    std::pair<LogLevel, std::string> pair;
    while(!m_stop)
    {
        queueMutex.lock();
        if(!outputQueue.empty())
        {
            pair = outputQueue.front();
            if(pair.first <= logLevel)
                if(logLevel == LOG_LEVEL_ERROR)
                    std::cerr << pair.second << std::endl;
                else
                    std::cout << pair.second << std::endl;
            outputQueue.pop();
        }
        queueMutex.unlock();
        //some sleep to avoid much much unecessary loops
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
}