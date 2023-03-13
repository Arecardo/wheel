#ifndef _C_LOGGER_H__
#define _C_LOGGER_H__

#include <string>
#include <fstream>
#include <chrono>
#include <stdexcept>
#include <iostream>

namespace wheel{

class Logger
{
public:
    enum Level
    {
        DEBUG = 0,
        INFO,
        WARN,
        ERROR,
        FATAL,
        LEVEL_COUNT
    };
    void Log(Level level, const char * file, int line, const char* format, ...);
    void open(const std::string& filename);
    void close();

private:
    Logger();
    ~Logger();

public:
    // singleton
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    Logger(Logger&&) = delete;
    Logger& operator=(Logger&&) = delete;

public:
    // singleton
    static Logger& GetInstance()
    {
        static Logger _ins;
        return _ins;
    }
private:
    std::string m_filename;
    std::ofstream m_fout;
    static const char* s_level[LEVEL_COUNT];
};

} // namespace wheel
#endif // _C_LOGGER_H__  