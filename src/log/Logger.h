#ifndef _C_LOGGER_H__
#define _C_LOGGER_H__

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <ctime>
#include <iomanip>

namespace wheel{

enum class Level
{
    DEBUG = 0,
    INFO,
    WARN,
    ERROR,
    FATAL
};

class Logger
{
public:
    
    void Log(Level level, const std::string& file, int line, const std::string& message);

private:
    void OpenFile();
    void ReopenFile();
    void CloseFile();
    std::string Now();
    std::string LevelToStr(Level level);

public:
    Logger(Level level, const std::string& filename, size_t max_size);
    ~Logger();

private:
    std::string m_filename;
    std::ofstream m_fout;
    Level m_level;
    size_t m_max_size;
};

} // namespace wheel
#endif // _C_LOGGER_H__  