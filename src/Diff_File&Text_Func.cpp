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

int DeleteSpaces(char* str)
{
    size_t len = strlen(str);
    size_t i = 0;

    for (size_t j = 0; j < len; j++) {
        if (!isspace(str[j])) {
            str[i] = str[j];
            i++;
        }
    }

    str[i] = '\0';

    return 0;
}

int PrintFormulaTex (Node* root) //TODO: сделать чтобы можно было вписывать все изменения формулы
{
    static int res_cnt = 0;

    FILE* tex_file = fopen("../ResultInTex/Result.tex", "a");

    if (res_cnt == 0) {
        fprintf(tex_file, "\\documentclass{article}\n"
                          "\\begin{document}\n\n"
                          "Your formula:\n");
    } else if (res_cnt == 1) {
        fprintf(tex_file, "Simplified formula:\n");
    } else if (res_cnt == 2) {
        fprintf(tex_file, "Derivative:\n");
    } else if (res_cnt == 3) {
        fprintf(tex_file, "Simplified derivative:\n");
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

int PrintFormula(Node* node, FILE* fp)
{
    fprintf(fp, "{");

    if (node->left != nullptr && node->right != nullptr) {
        if (IS_SPEC_OP(node, '*'))
            PrintMultiplication(node, fp);
        else if (IS_SPEC_OP(node, '/'))
            PrintDivision(node, fp);
        else if (IS_SPEC_OP(node, '+') || IS_SPEC_OP(node, '-'))
            PrintExpression(node, fp);
        else
            PrintOtherOperators(node, fp);
    } else if (IS_NUM(node)) {
        if (*(double*)node->data < 0)
            fprintf(fp, "(%0.2f)", *(double*)node->data);
        else
            fprintf(fp, "%0.2f", *(double*)node->data);
    } else if (IS_VAR(node)) {
        fprintf(fp, "%c", *(char*)node->data);
    } else if (IS_FUNC(node)) {
        fprintf(fp, "%s \\left( ", (char*)node->data);
        PrintFormula(node->left, fp);
        fprintf(fp, "\\right) ");
    }

    fprintf(fp, "}");

    return 0;
}

int PrintExpression(Node* node, FILE* fp)
{
    fprintf(fp, "\\left( ");
    PrintFormula(node->left, fp);
    fprintf(fp, "%c", *(char*)node->data);
    PrintFormula(node->right, fp);
    fprintf(fp, "\\right) ");

    return 0;
}

int PrintMultiplication(Node* node, FILE* fp)
{
    PrintFormula(node->left, fp);
    fprintf(fp, "\\cdot ");
    PrintFormula(node->right, fp);

    return 0;
}

int PrintDivision(Node* node, FILE* fp)
{
    fprintf(fp, "\\frac{");
    PrintFormula(node->left, fp);
    fprintf(fp, "}");

    fprintf(fp, "{");
    PrintFormula(node->right, fp);
    fprintf(fp, "}");

    return 0;
}

int PrintOtherOperators(Node* node, FILE* fp)
{
    PrintFormula(node->left, fp);
    fprintf(fp, "%c", *(char*)node->data);
    PrintFormula(node->right, fp);

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

int RemoveOldTexFile()
{
    system("cd ../ResultInTex/ && rm Result.tex");

    return 0;
}

int MakePdfFromTex()
{
    system("cd ../ResultInTex/ && pdflatex Result.tex");

    return 0;
}