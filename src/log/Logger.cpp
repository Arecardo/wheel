#include "Logger.h"
using namespace wheel;

const char * Logger::s_level[LEVEL_COUNT] = {
    "DEBUG",
    "INFO",
    "WARN",
    "ERROR",
    "FATAL"
};

Logger::Logger()
{

}

Logger::~Logger()
{

}

void Logger::open(const std::string& filename)
{
    m_filename = filename;
    m_fout.open(filename, std::ios::app);
    if (m_fout.fail())
    {
        throw std::logic_error("open file failed " + filename);
    }
}

void Logger::close()
{
    m_fout.close();
}

void Logger::Log(Level level, const char* file, int line, const char* format, ...)
{
    if (m_fout.fail())
    {
        throw std::logic_error("open file failed " + m_filename);
    }

    auto curr_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    char* it = ctime(&curr_time);
    std::cout << it;
}