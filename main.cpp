#include "Int.h"
#include "log.h"

Int test()
{
    START_FUNC_;

    MAKE_INT_BY_VALUE_(a, 5);

    END_FUNC_;
    return a;
}

int main()
{
    START_FUNC_;

    MAKE_INT_BY_VALUE_(a, 5);
    MAKE_INT_BY_VARIABLE_(b, 4);
    MAKE_INT_BY_VARIABLE_(d, 5);
    d += 4;
    d = b;
    MAKE_INT_BY_VARIABLE_(z, -d);
    MAKE_INT_BY_VARIABLE_(c, a + b + z);
    //MAKE_INT_BY_VALUE_

    MAKE_INT_BY_VALUE_(ret, test());

    END_FUNC_;

    return 0;
}