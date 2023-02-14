#include "Int.h"
#include "log.h"

int Int::number_of_temp_var = 0;

#define BIN_OPR_(op)                                                                        \
            Int Int::operator op(const Int& other) const{                                   \
                return Int(*this, other, this->get_number() op other.get_number(), #op);    \
            }

#define UNARY_OPR_(op)                                                                      \
            Int Int::operator op() const{                                                   \
                return Int(*this, op this->get_number(), #op);                              \
            }

#define ASS_OPR_(op)                                                                        \
            Int& Int::operator op(const Int& other){                                        \
                number_ op other.get_number();                                              \
                history_ = " = " + this->get_name() + " " + #op + " " + other.get_name();   \
                LOG_ASSIGN_(*this, other, #op);                                             \
                return *this;                                                               \
            }

#include "operator.gen"

#undef BIN_OPR_
#undef UNARY_OPR_

Int& Int::operator=(const Int& other)
{
    set_number(other.get_number());
    set_history(other.get_history());
    history_ = other.history_;
    LOG_ASSIGN_(*this, other, "=");
    return *this;
}

Int& Int::operator=(Int&& other)
{
    set_number(other.get_number());
    set_history(other.get_history());
    history_ = other.history_;
    LOG_ASSIGN_(*this, other, "=");
    return *this;
}
