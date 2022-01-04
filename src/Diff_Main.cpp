#include "../include/Diff.h"

const char* s = nullptr;

int main()
{
    char* string = (char*) calloc(MAX_FORMULA_LEN, sizeof(char));
    ScanString(string);

    Node* root = GetG(string);
    CHECK_ROOT(root, string);
    TreeDump(root, "GetG");

    Simplify(root);
    TreeDump(root, "Simplify");

    Node* diff_root = Diff(root);
    TreeDump(diff_root, "Diff");

    Simplify(diff_root);
    TreeDump(diff_root, "Simplify");

    TreeDtor(root);
    TreeDtor(diff_root);
    free(string);
}