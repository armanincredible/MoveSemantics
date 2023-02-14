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

    void LogUnicNodeName(const Int&);
    void LogArrow(const Int&, const Int&, const std::string&);
    void LogArrows(const Int&, const Int&, const Int&, const std::string&);
    void LogAssignArrow(Int& from, Int& to, const std::string& name);
    void LogAssignArrows(Int& from1, const Int& from2, const std::string& name);

    void LogVariable(const Int&);

    void LogFunctionEnd();
    Logger();
    ~Logger();
};

extern Logger PROGRAM_LOGGER;

#define START_FUNC_ PROGRAM_LOGGER.LogFunctionStart(__PRETTY_FUNCTION__)
#define END_FUNC_ PROGRAM_LOGGER.LogFunctionEnd()
#define LOG_VARIABLE_(var) PROGRAM_LOGGER.LogVariable(var)
#define LOG_ARROW_(from, to, name) PROGRAM_LOGGER.LogArrow(from, to, name)
#define LOG_ARROWS_(first, second, into, name) PROGRAM_LOGGER.LogArrows(first, second, into, name)

#define LOG_ASSIGN_(first, second, name)                                \
        do{                                                             \
            (first).assign_number += 1;                                 \
            LOG_VARIABLE_(first);                                       \
            PROGRAM_LOGGER.LogAssignArrows(first, second, name);        \
        }while(0)

#endif
