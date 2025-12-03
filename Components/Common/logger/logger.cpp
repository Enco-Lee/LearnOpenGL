#include "logger.h"
#include <cstdarg>
#include <ctime>
#include <memory>
#include <stdexcept>

namespace zh
{
    const char* Logger::s_level[LEVEL_COUNT] = {
        "DEBUG",
        "INFO ",
        "WARN ",
        "ERROR",
        "FATAL",
    };

    static std::string getNowTimeInfo(const char* format)
    {
        time_t     ticks = time(nullptr);
        struct tm* ptm   = localtime(&ticks);
        char       timestamp[32];
        memset(timestamp, 0, sizeof(timestamp));
        std::strftime(timestamp, sizeof(timestamp), format, ptm);
        return std::string(timestamp);
    }

    void Logger::log(Level level, const char* file, int line, const char* format, ...)
    {
        if (level < m_level)
            return;
        if (!m_fout.is_open())
        {
            throw std::logic_error("open file error: " + std::string(file));
        }
        const char* timeFormat  = "%Y-%m-%d %H:%M:%S";
        std::string nowTimeInfo = getNowTimeInfo(timeFormat);
        const char* fmt         = "%s %s %s:%d ";
        int         size        = snprintf(nullptr, 0, fmt, nowTimeInfo.data(), s_level[level], file, line);
        if (size > 0)
        {
            long capacity = size + 1;
            auto buffer   = std::unique_ptr<char[]>(new char[capacity]);
            snprintf(buffer.get(), capacity, fmt, nowTimeInfo.data(), s_level[level], file, line);
            buffer[size] = '\0';
            m_nowLenght += size;
            m_fout << buffer;
        }
        va_list arg_ptr;
        va_start(arg_ptr, format);
        size = vsnprintf(nullptr, 0, format, arg_ptr);
        va_end(arg_ptr);
        if (size > 0)
        {
            long capacity = size + 1;
            auto content  = std::unique_ptr<char[]>(new char[capacity]);
            va_start(arg_ptr, format);
            vsnprintf(content.get(), capacity, format, arg_ptr);
            va_end(arg_ptr);
            content[size] = '\0';
            m_nowLenght += size;
            m_fout << content << "\n";
        }
        m_fout.flush();
        if (m_nowLenght >= m_maxLength && m_maxLength > 0)
        {
            rotate();
        }
    }

    void Logger::open(const std::string& fileName)
    {
        m_fout.open(fileName, std::ios::app);
        if (m_fout.fail())
        {
            throw std::logic_error("open file error: " + fileName);
        }
        m_fileName = fileName;
        m_fout.seekp(0, std::ios::end);
        m_nowLenght = m_fout.tellp();
    }

    void Logger::close()
    {
        m_fout.close();
    }

    Logger& Logger::instance()
    {
        static Logger s_instance;
        return s_instance;
    }

    void Logger::setMinLevel(Level level)
    {
        m_level = level;
    }

    void Logger::setMaxLength(int bytes)
    {
        m_maxLength = bytes;
    }

    void Logger::rotate()
    {
        close();
        const char* timeFormat  = "%Y-%m-%d_%H%M%S";
        std::string nowTimeInfo = getNowTimeInfo(timeFormat);
        std::string fileName    = "log_" + nowTimeInfo + ".txt";
        // if (rename(m_fileName.c_str(), fileName.c_str()) != 0)
        {
            // throw std::logic_error("rename log file failed");
        } // else
        {
            m_fileName  = fileName;
            m_nowLenght = 0;
            open(m_fileName);
        }
    }

    Logger::Logger() : m_fileName(""), m_level(DEBUG), m_nowLenght(0), m_maxLength(0) {}

    Logger::~Logger()
    {
        close();
    }

}; // namespace zh
