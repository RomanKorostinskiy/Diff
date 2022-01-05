#include "../include/Diff.h"

int ScanFormula(char* str)
{
    printf("Enter the formula you want to differentiate:\n");
    ScanString(str);

    return 0;
}

int ScanString(char* array)
{
    int i = 0;

    while (true) {
        int c = getchar();

        if (i > MAX_FORMULA_LEN) {
            printf("In function ScanPhrase: too much letters\n");
            break;
        }

        if (c == '\n') {
            array[i] = '\0';
            break;
        } else {
            array[i] = (char) c;
            i++;
        }
    }

    return 0;
}