#include "../include/Diff.h"

const char* s = nullptr;

int main()
{
    char* string = (char*) calloc(MAX_FORMULA_LEN, sizeof(char));
    ScanFormula(string);

    Node* root = GetG(string);
    CHECK_ROOT(root, string);
    TreeDump(root, "GetG");

    LoopSimplify(root);

    Node* diff_root = Diff(root);
    TreeDump(diff_root, "Diff");

    LoopSimplify(diff_root);

    TreeDtor(root);
    TreeDtor(diff_root);
    free(string);

    //    printf("Node = %ld, Node* = %ld, void* = %ld, char = %ld", sizeof(Node), sizeof(Node*), sizeof(void*), sizeof(char));
    return 0;
}