#ifndef INT_HEADER
#define INT_HEADER

#include "iostream"
#include "log.h"

class Int
{
public:

    int assign_number = 0;

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

        LOG_ARROW_(other, *this, "move");
    }

    Int(Int&& other, const std::string& name = "")
    {
        int tmp = other.get_number();
        other.set_number(number_);
        number_ = tmp;

        std::string tmp1 = other.get_history();
        other.set_history(history_);
        history_ = " = " + other.get_name() + tmp1;

        SetName(name);

        LOG_VARIABLE_(*this);
        LOG_ARROW_(other, *this, "move");
    }

/*constuctors for operators from operator.gen*/
// from here
    Int(const Int& first, const Int& second, const int num, const std::string& op)
    {
        number_ = num;
        SetName();
        history_ = " = " + first.get_name() + " " + op + " " + second.get_name();
        LOG_VARIABLE_(*this);

        LOG_ARROWS_(first, second, *this, op);
    }

    Int(const Int& var, const int num, const std::string& op)
    {
        number_ = num;
        SetName();
        history_ = " = " + op + " " + var.get_name();
        LOG_VARIABLE_(*this);

        LOG_ARROW_(var, *this, "unary " + op);
    }
// to here

    Int& operator=(const Int& other);
    Int& operator=(Int&& other);

    ~Int(){}

#define BIN_OPR_(op)                    \
    Int operator op(const Int&) const;

#define UNARY_OPR_(op)                  \
    Int operator op() const;

#define ASS_OPR_(op)                    \
    Int& operator op(const Int&);

    #include "operator.gen"

#undef BIN_OPR_
#undef UNARY_OPR_
#undef ASS_OPR_

    int get_number() const {return number_;}
    void set_number(int num){number_ = num;}

    std::string get_name() const {return name_;}
    std::string get_history() const {return history_;}
    void set_history(std::string str){history_ = str;}

    bool is_real_var() const {return real_var_;}

private:
    bool real_var_ = false;
    std::string name_ = "";
    std::string history_ = "";
    static int number_of_temp_var;
    int number_ = 0;

    void SetName(const std::string& name = "")
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
            number_of_temp_var++;
        }
    }
};

#define MAKE_INT_BY_VALUE_(name, var) Int name(var, #name)
#define MAKE_INT_BY_VARIABLE_(new_var, other_var) Int new_var(other_var, #new_var)

#endif