#ifndef LOGGER_HEADER
#define LOGGER_HEADER

#include <cstdlib>
#include <stdio.h>
#include <iostream>

class Int;

class Logger
{
private:
    FILE* log_file_ = nullptr;
    int inited_ = 0;
    int func_num_ = 0;
    int node_ = 0;
    int tabs_ = 0;

public:

    void LogFunctionStart(const std::string&);

    void LogVaribaleValue(const Int&);
    void LogVaribaleName(const Int&);
    void LogVaribalePointer(const Int&);

    void LogVariable(const Int&);

    void LogFunctionEnd();
    Logger();
    ~Logger();
};

extern Logger PROGRAM_LOGGER;

#define START_FUNC_ PROGRAM_LOGGER.LogFunctionStart(__PRETTY_FUNCTION__)
#define END_FUNC_ PROGRAM_LOGGER.LogFunctionEnd()
#define LOG_VARIABLE_(var) PROGRAM_LOGGER.LogVariable(var)

#endif
