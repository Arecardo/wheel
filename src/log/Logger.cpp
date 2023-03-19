#include "Logger.h"
using namespace wheel;
using namespace std::chrono;

Logger::Logger(const std::string& filename, size_t max_size):
    m_filename(filename), m_max_size(max_size)
{

}

Logger::~Logger()
{
    CloseFile();
}

void Logger::OpenFile()
{
    m_fout.open(m_filename, std::ios::out | std::ios::app);
    if (!m_fout.is_open())
    {
        throw std::runtime_error("open file failed: " + m_filename);
    }
}

void Logger::ReopenFile()
{
    m_fout.close();
    std::ostringstream oss;
    oss << m_filename << "." << std::time(nullptr) << ".log";
    std::string newFilename = oss.str();
    std::rename(m_filename.c_str(), newFilename.c_str());
    OpenFile();
}

void Logger::CloseFile()
{
    if (m_fout.is_open())
    {
        m_fout.close();
    }
}

std::string Logger::LevelToStr(Level level)
{
    switch(level)
    {
        case Level::DEBUG:
            return "DEBUG";
        case Level::INFO:
            return "INFO";
        case Level::WARN:
            return "WARN";
        case Level::ERROR:
            return "ERROR";
        case Level::FATAL:
            return "FATAL";
        default:
            return "UNKNOWN";
    }
}

std::string Logger::Now()
{
    auto now = system_clock::now();
    auto m = now.time_since_epoch();
    auto diff = duration_cast<microseconds>(m).count();
    auto const ms = diff % 1000000;

    std::stringstream ss;
    time_t t = system_clock::to_time_t(now);
    ss << std::put_time(localtime(&t), "%Y-%m-%d %H:%M:%S") << "." << ms;
    return ss.str();
}

void Logger::Log(Level level, const std::string& file, int line, const std::string& message)
{
    if (m_fout.is_open() && m_fout.tellp() >= m_max_size)
    {
        ReopenFile();
    }

    if (!m_fout.is_open())
    {
        OpenFile();
    }

    std::string curr_time = Now();

    std::ostringstream oss;
    oss << "[" << curr_time.c_str() << "]" << "[" << LevelToStr(level) << "]" << "[" << file << ":" << line << "]" << message << std::endl;
    m_fout << oss.str();
    m_fout.flush();
}