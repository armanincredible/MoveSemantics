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

#define PRINT_FILE_WITHOUT_SPACES_(f_, ...) fprintf (log_file_, (f_), ##__VA_ARGS__)

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

void Logger::LogUnicNodeName(const Int& var)
{
    INITED_CHECK_();
    PRINT_FILE_WITHOUT_SPACES_("INFO%s%p%d ", var.get_name().c_str(), (void*)&var, var.assign_number);
}

void Logger::LogVariable(const Int& var)
{
    INITED_CHECK_();
    PRINT_FILE_(" ");
    LogUnicNodeName(var);
    PRINT_FILE_WITHOUT_SPACES_("[shape = record, ");

    if (!var.is_real_var())
    {
        PRINT_FILE_WITHOUT_SPACES_("color = red, style=\"rounded,filled\", ");
    }

    PRINT_FILE_WITHOUT_SPACES_("label = \"<name> %s %s\"];\n", var.get_name().c_str(), var.get_history().c_str());

}

void Logger::LogArrow(const Int& from, const Int& to, const std::string& name)
{
    INITED_CHECK_();
    PRINT_FILE_(" ");
    LogUnicNodeName(from);
    PRINT_FILE_WITHOUT_SPACES_(": <name> -> ");
    LogUnicNodeName(to);
    PRINT_FILE_WITHOUT_SPACES_(": <name> [label = \" %s \", ]\n", name.c_str());
}

void Logger::LogArrows(const Int& from1, const Int& from2, const Int& into, const std::string& name)
{
    INITED_CHECK_();
    LogArrow(from1, into, name);
    LogArrow(from2, into, name);
}

void Logger::LogAssignArrow(Int& from, Int& to, const std::string& name)
{
    INITED_CHECK_();
    PRINT_FILE_(" ");
    to.assign_number -= 1;
    LogUnicNodeName(from);
    PRINT_FILE_WITHOUT_SPACES_(": <name> -> ");
    to.assign_number += 1;
    LogUnicNodeName(to);
    PRINT_FILE_WITHOUT_SPACES_(": <name> [label = \" %s \", ]\n", name.c_str());
}

void Logger::LogAssignArrows(Int& from1, const Int& from2,const std::string& name)
{
    INITED_CHECK_();
    LogAssignArrow(from1, from1, name);
    LogArrow(from2, from1, name);
}
