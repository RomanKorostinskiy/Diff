#include "../include/Diff.h"
#include "../include/Diff_DSL.h"

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

int PrintTree(Node* node)
{
    if (node->left != nullptr && node->right != nullptr) {
        if (IS_SPEC_OP(node, '+') || IS_SPEC_OP(node, '-'))
            printf("(");
        PrintTree(node->left);
        printf("%c", *(char*)node->data);
        PrintTree(node->right);
        if (IS_SPEC_OP(node, '+') || IS_SPEC_OP(node, '-'))
            printf(")");
    } else if (IS_NUM(node)) {
        printf("%0.2f", *(double*)node->data);
    } else if (IS_VAR(node)) {
        printf("%c", *(char*)node->data);
    }

    return 0;
}

int PrintFormula(Node* node, FILE* fp)
{
    if (node->left != nullptr && node->right != nullptr) {
        if (IS_SPEC_OP(node, '+') || IS_SPEC_OP(node, '-'))
            fprintf(fp, "(");
        PrintFormula(node->left, fp);
        fprintf(fp, "%c", *(char*)node->data);
        PrintFormula(node->right, fp);
        if (IS_SPEC_OP(node, '+') || IS_SPEC_OP(node, '-'))
            fprintf(fp, ")");
    } else if (IS_NUM(node)) {
        fprintf(fp, "%0.2f", *(double*)node->data);
    } else if (IS_VAR(node)) {
        fprintf(fp, "%c", *(char*)node->data);
    }

    return 0;
}

int PrintFormulaTex (Node* root) //TODO: сделать чтобы можно было вписывать все изменения формулы
{
    static int res_cnt = 0;

    FILE* tex_file = fopen("../ResultInTex/Result.tex", "a");

    if (res_cnt == 0) {
        fprintf(tex_file, "\\documentclass{article}\n"
                          "\\begin{document}\n");
    }

    fprintf(tex_file, "\\begin{equation}\n");
    PrintFormula(root, tex_file);
    fprintf(tex_file, "\n"
                      "\\end{equation}\n");

    if (res_cnt == 3) {
        fprintf(tex_file, "\n"
                          "\\end{document}");
    }

    res_cnt++;

    fclose(tex_file);

    return 0;
}

char* TexFileName(int res_cnt)
{
    char* tex_file_name = nullptr;

    tex_file_name = (char*) calloc(50, sizeof(char));

    if(tex_file_name == nullptr)
    {
        printf("In function TexFileName: tex_file_name is nullptr");
        return nullptr;
    }

    sprintf(tex_file_name, "../ResultInTex/Result%d.tex", res_cnt);

    return tex_file_name;
}

int MakePdfFromTex ()
{
    system("cd ../ResultInTex/ && pdflatex Result.tex");

    return 0;
}