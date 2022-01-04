#include "../include/Diff.h"

int Require(const char sign)
{
    if (*s == sign) {
        s++;
    }
    else {
        SyntaxError(__FUNCTION__);
        printf("Required sign %c\n", sign);
        return SYNTAX_ERROR;
    }

    return 0;
}

int SyntaxError(const char* function)
{
    printf("SyntaxError: in function %s\n", function);
    return SYNTAX_ERROR;
}