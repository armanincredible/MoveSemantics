#include "log.h"
#include "Int.h"

#define PRINT_FILE_(f_, ...)                            \
        do{                                             \
            for (int i = 0; i < tabs_; i++)             \
            {                                           \
                fprintf (log_file_, "\t");              \
            }                                           \
            fprintf (log_file_, (f_), ##__VA_ARGS__);   \
        }while(0)

#define INITED_CHECK_(ret)              \
        do{                             \
            if (inited_ != 1)           \
            {                           \
                return ret;             \
            }                           \
        }while(0)

Logger PROGRAM_LOGGER;


struct log_elem
{
    void* pointer;
};

Logger::Logger()
{
    log_file_ = fopen("graph.dot", "w");
    if (log_file_ == NULL)
    {
        inited_ = 0;
    }
    else
    {
        PRINT_FILE_("digraph{\n");
        tabs_++;
        inited_ = 1;
    }
}

Logger::~Logger()
{
    if ((log_file_ != NULL) && (inited_ == 1))
    {
        tabs_--;
        PRINT_FILE_("}\n");
        fclose(log_file_);
    }
}

void Logger::LogFunctionStart(const std::string& func_name)
{
    INITED_CHECK_();
    PRINT_FILE_("subgraph cluster_%d {\n", func_num_);
    tabs_++;
    PRINT_FILE_("label = \"%s\"\n", func_name.c_str());
    func_num_++;
}

void Logger::LogFunctionEnd()
{
    INITED_CHECK_();
    tabs_--;
    PRINT_FILE_("}\n");
}

void Logger::LogVaribaleValue(const Int& var)
{
    INITED_CHECK_();
    
}
void Logger::LogVaribaleName(const Int& var)
{
    INITED_CHECK_();
}
void Logger::LogVaribalePointer(const Int& var)
{
    INITED_CHECK_();
}

void Logger::LogVariable(const Int& var)
{
    INITED_CHECK_();
    PRINT_FILE_("INFO%p [shape = record, label = \"<name> %s %s\"];\n", (void*)&var, var.get_name().c_str(),var.get_history().c_str());
}
