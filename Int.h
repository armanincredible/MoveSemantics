#ifndef INT_HEADER
#define INT_HEADER

#include "iostream"
#include "log.h"

class Int
{
public:
    Int(int num, const std::string& name = "")
    {
        number_ = num;
        SetName(name);
        history_ = " = " + std::to_string(num);
        LOG_VARIABLE_(*this);
    }

    Int(const Int& other, const std::string& name = "")
    {
        number_ = other.get_number();
        SetName(name);
        history_.clear();
        history_ = " = " + other.get_name() + other.get_history();
        LOG_VARIABLE_(*this);
    }

    ~Int(){}

    int get_number() const {return number_;}
    std::string get_name() const {return name_;}
    std::string get_history() const {return history_;}

private:
    bool real_var_ = false;
    std::string name_ = "";
    std::string history_ = "";
    static int number_of_temp_var;
    int number_ = 0;

    void SetName(const std::string& name)
    {
        if (name != "") 
        {
            real_var_ = true;
            name_ = name;
        } 
        else 
        {
            real_var_ = false;
            name_ = "tmp_" + std::to_string(number_of_temp_var);
        }
    }
};

#define MAKE_INT_BY_VALUE_(name, var) Int name{var, #name}
#define MAKE_INT_BY_VARIABLE_(new_var, other_var) Int new_var(other_var, #new_var)

#endif