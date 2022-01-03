#include "../include/Diff.h"

int ScanString(char* str)
{
    printf("Enter the formula you want to differentiate:\n");
    scanf("%s", str);

    return 0;
}



tnode* GetE()
{
    tnode* val = GetN();

    while (*string == '+' || *string == '-') {
        char op = *string;
        string++;

        tnode* val2 = GetN();
        val = CreateNode(OP, &op, val, val2);
    }

    return val;
}

tnode* GetN()
{
    double val , power;

    for (val = 0.0; isdigit(*string); string++)
        val = 10.0 * val + *string - '0';

    if (*string == '.')
        string++;

    for (power = 1.0; isdigit(*string); string++) {
        val = 10.0 * val + *string - '0';
        power *= 10.0;
    }

    val = val / power;

    return CreateNode(NUM, &val, nullptr, nullptr);
}

tnode* CreateNode(int type, void* data, tnode* left, tnode* right)
{
    tnode* new_node = (tnode*)calloc(1, sizeof(tnode));
    new_node->type = type;

    if (type == NUM) {
        new_node->data = (double*) calloc(1, sizeof(double));
        *(double*) new_node->data = *(double*) data;
    } else if (type == OP) {
        new_node->data = (char*) calloc(1, sizeof(char));
        *(char*) new_node->data = *(char*) data;
    }

    new_node->left = left;
    new_node->right = right;

    return new_node;
}

//int LexicalAnalysis(char* string, tnode* tokens_array)
//{
//    int i = 0;
//    int j = 0;
//
//    while(j < MAX_FORMULA_LEN) {
//        while(string[i] >= '0' && string[i] <= '9') {
//            int value = 0;
//
//            do
//        }
//
//    }
//
//    return 0;
//}