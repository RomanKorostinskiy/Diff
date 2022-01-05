#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct Node {
    void* data;
    int type;

    Node* left;
    Node* right;

}Node;

enum Constants {
    ROOT            = -1,
    MAX_FORMULA_LEN = 1024,
    FIRST_CALL      = -1
};

enum NodeTypes {
    NUM = 1,
    VAR = 2,
    OP  = 3,
};

enum Errors {
    SYNTAX_ERROR = 1,
};

extern const char* s;

#define CHECK_ROOT(root, string)   \
do{                                \
    if((root) == nullptr) {        \
        free(string);              \
        return 0;                  \
    }                              \
} while(0)

#define CHECK_NODE(node)    \
do{                         \
    if((node) == nullptr)   \
        return nullptr;     \
} while(0)

//---------Diff_Tree_Func---------

int LexicalAnalysis(char* string, Node* tokens_array); //дроп

Node* GetG(const char* string);

Node* GetE();

Node* GetT();

Node* GetP();

Node* GetN();

Node* GetId();

Node* CreateNode(int type, void* data, Node* left, Node* right);

Node* CopyNode(Node* node);

int FreeChildNodes(Node* node);

int TreeDtor(Node* node);

//---------Diff_Differentiate_Func---------

Node* Diff(Node* node);

int Simplify(Node* node, int* smpl_cnt);

int LoopSimplify(Node* root);

//---------Diff_Errors_Func--------------

int Require(const char sign);

int SyntaxError(const char* function);

//---------Diff_Text_Func--------------

int ScanFormula(char* str);

int ScanString(char* array);

//---------Diff_Dump--------------

int TreeDump(Node* root, const char* current_function);

int MakeGraphDumpTxt(Node* root, const char* current_function, int dump_cnt);

int MakePngFromTxt(int dump_cnt);

int RecursiveTreeDump(Node* node, FILE* dump_fp, int parents_num, bool left_node);

char* DumpFileName(int dump_cnt, const char* format);