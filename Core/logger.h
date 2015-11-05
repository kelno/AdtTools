#ifndef H_LOGGER
#define H_LOGGER

#include "runnable.h"
#include <mutex>
#include <queue>

/*
Logger should be used for all console outputs to avoid concurrency issues. Logger use a queue of log messages and output those within it's own thread.
Logger should only be accessed via sLogger, which creates the object the first time it is called.
*/
class Logger : public Runnable
{
public:
    enum LogLevel
    {
        LOG_LEVEL_ERROR    = 0,
        LOG_LEVEL_NORMAL   = 1,
        LOG_LEVEL_DEBUG    = 2
    };

    //initialise the Logger with given log level. A message with a higher log level than the logger log level will not be printed to console.
    Logger(LogLevel level = LOG_LEVEL_NORMAL);
    ~Logger();

    //create a Logger object if none exists, else returns the already existing one
    static Logger* instance()
    {
        static Logger instance;
        return &instance;
    }

    /* Get the log level. */
    LogLevel GetLogLevel() const;
    /* Set the log level */
    void SetLogLevel(LogLevel level);

    /* Print a message with a given log level. A message with a higher log level than the logger log level will not be printed.
    This is a thread safe function (it may be called at any time by any thread without conflicts) */
    void Out(LogLevel level, const char* msg, ...);

private:
    void Run();
    std::queue<std::pair<LogLevel, std::string>> outputQueue; //level + message
    std::mutex queueMutex;

    LogLevel logLevel;
};

#define sLogger Logger::instance()

#endif //H_LOGGER
