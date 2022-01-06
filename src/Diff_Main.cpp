#include "../include/Diff.h"

const char* s = nullptr;

int main()
{
    char* string = (char*) calloc(MAX_FORMULA_LEN, sizeof(char));
    ScanFormula(string);
    DeleteSpaces(string);

    RemoveOldTexFile();

    Node* root = GetG(string);
    CHECK_ROOT(root, string);
    TreeDump(root, "GetG");
    PrintFormulaTex(root);

    LoopSimplify(root);
    PrintFormulaTex(root);

    Node* diff_root = Diff(root);
    TreeDump(diff_root, "Diff");
    PrintFormulaTex(diff_root);

    LoopSimplify(diff_root);
    PrintFormulaTex(diff_root);

    MakePdfFromTex();

    TreeDtor(root);
    TreeDtor(diff_root);
    free(string);

    return 0;
}