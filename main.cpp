#include "Int.h"
#include "log.h"

int main()
{
    START_FUNC_;

    MAKE_INT_BY_VALUE_(a, 5);
    MAKE_INT_BY_VARIABLE_(b, a);

    END_FUNC_;
    return 0;
}