#include "../include/Diff.h"

const char* s = nullptr;

int main()
{
    char* string = (char*) calloc(MAX_FORMULA_LEN, sizeof(char));
    ScanString(string);

//    tnode* tokens_array = (tnode*) calloc(MAX_FORMULA_LEN, sizeof(tnode));
//    LexicalAnalysis(string, tokens_array);
    Node* root = GetG(string);
    if (root == nullptr) {
        free(string);
        return 0;
    }

    TreeDump(root, __FUNCTION__ );

    TreeDtor(root);
    free(string);
}