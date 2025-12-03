#pragma once
#include <fstream>
#include <string>

namespace zh
{
#define LOG_DEBUG(format, ...) zh::Logger::instance().log(zh::Logger::DEBUG, __FILE__, __LINE__, format, ##__VA_ARGS__);

#define LOG_INFO(format, ...) zh::Logger::instance().log(zh::Logger::INFO, __FILE__, __LINE__, format, ##__VA_ARGS__);

#define LOG_WARN(format, ...) zh::Logger::instance().log(zh::Logger::WARN, __FILE__, __LINE__, format, ##__VA_ARGS__);

#define LOG_ERROR(format, ...) zh::Logger::instance().log(zh::Logger::ERROR, __FILE__, __LINE__, format, ##__VA_ARGS__);

#define LOG_FATAL(format, ...) zh::Logger::instance().log(zh::Logger::FATAL, __FILE__, __LINE__, format, ##__VA_ARGS__);

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

        void           log(Level level, const char* file, int line, const char* format, ...);
        void           open(const std::string& fileName);
        void           close();
        static Logger& instance();

        void setMinLevel(Level level);
        void setMaxLength(int bytes);
        void rotate();

    private:
        std::string        m_fileName;
        std::ofstream      m_fout;
        static const char* s_level[LEVEL_COUNT];
        Level              m_level;
        int                m_maxLength;
        int                m_nowLenght;

    private:
        Logger();
        ~Logger();
    };
} // namespace zh
