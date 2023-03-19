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

#define LOG_DEBUG(msg) wheel::Logger::GetInstance().Log(wheel::Level::DEBUG, __FILE__, __LINE__, msg)
#define LOG_INFO(msg) wheel::Logger::GetInstance().Log(wheel::Level::INFO, __FILE__, __LINE__, msg)
#define LOG_WARN(msg) wheel::Logger::GetInstance().Log(wheel::Level::WARN, __FILE__, __LINE__, msg)
#define LOG_ERROR(msg) wheel::Logger::GetInstance().Log(wheel::Level::ERROR, __FILE__, __LINE__, msg)
#define LOG_FATAL(msg) wheel::Logger::GetInstance().Log(wheel::Level::FATAL, __FILE__, __LINE__, msg)

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

// singleton
public:
    static Logger& GetInstance()
    {
        static Logger _ins("log.txt", 1000000);
        return _ins;
    }
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    Logger(Logger&&) = delete;
    Logger& operator=(Logger&&) = delete;
private:
    Logger(const std::string& filename, size_t max_size);
    ~Logger();

private:
    std::string m_filename;
    std::ofstream m_fout;
    size_t m_max_size;
};

} // namespace wheel
#endif // _C_LOGGER_H__  