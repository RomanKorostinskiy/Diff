#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct tnode
{
    int type;
    void* data;

    tnode* left;
    tnode* right;
}tnode;

enum Constants {
    ROOT = -1,
    MAX_FORMULA_LEN = 1024,
};

enum NodeTypes {
    NUM = 1,
    VAR = 2,
    OP  = 3,
};

char* string = (char*) calloc(MAX_FORMULA_LEN, sizeof(char));

//---------Diff_Tree_Func---------

int ScanString(char* formula);

int LexicalAnalysis(char* string, tnode* tokens_array); //дроп

tnode* GetN();

tnode* CreateNode(int type, void* data, tnode* left, tnode* right);

int TreeDtor(tnode* node);

//---------Diff_Dump--------------

int TreeDump(tnode* root, const char* current_function);

int MakeGraphDumpTxt(tnode* root, const char* current_function, int dump_cnt);

int MakePngFromTxt(int dump_cnt);

int RecursiveTreeDump(tnode* node, FILE* dump_fp, int parents_num, bool left_node);

char* DumpFileName(int dump_cnt, const char* format);