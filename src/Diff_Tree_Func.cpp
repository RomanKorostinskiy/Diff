#include "../include/Diff.h"

int ScanString(char* str)
{
    printf("Enter the formula you want to differentiate:\n");
    scanf("%s", str);

    return 0;
}

Node* GetG(const char* str)
{
    s = str;

    Node* root = GetE();
    CHECK_NODE(root);
    Require('\0');

    return root;
}

Node* GetE()
{
    Node* t_node = GetT();
    CHECK_NODE(t_node);

    while (*s == '+' || *s == '-') {
        char op = *s;
        s++;

        Node* t_node2 = GetT();
        CHECK_NODE(t_node2);
        t_node = CreateNode(OP, &op, t_node, t_node2);
    }

    return t_node;
}

Node* GetT()
{
    Node* p_node = GetP();
    CHECK_NODE(p_node);

    while (*s == '*' || *s == '/') {
        char op = *s;
        s++;

        Node* p_node2 = GetP();
        CHECK_NODE(p_node2);
        p_node = CreateNode(OP, &op, p_node, p_node2);
    }

    return p_node;
}

Node* GetP()
{
    if (*s == '(') {
        s++;
        Node* e_node = GetE();
        CHECK_NODE(e_node);
        Require(')');
        return e_node;
    } else {
        Node* n_node = GetN();
        CHECK_NODE(n_node);
        return n_node;
    }
}

Node* GetN()
{
    double val , power;
    const char* old_s = s;

    for (val = 0.0; isdigit(*s); s++)
        val = 10.0 * val + *s - '0';
    if (*s == '.')
        s++;
    for (power = 1.0; isdigit(*s); s++) {
        val = 10.0 * val + *s - '0';
        power *= 10.0;
    }

    val = val / power;

    if(old_s == s){
        SyntaxError(__FUNCTION__);
        return nullptr;
    }

    return CreateNode(NUM, &val, nullptr, nullptr);
}

Node* CreateNode(int type, void* data, Node* left, Node* right)
{
    Node* new_node = (Node*)calloc(1, sizeof(Node));
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

int Require(const char sign)
{
    if (*s == sign) {
        s++;
    }
    else {
        SyntaxError(__FUNCTION__);
        printf("Required sign %c\n", sign);
        return SYNTAX_ERROR;
    }

    return 0;
}

int SyntaxError(const char* function)
{
    printf("SyntaxError: in function %s\n", function);
    return SYNTAX_ERROR;
}

int TreeDtor(Node* node)
{
    free(node->data);

    if (node->left != nullptr && node->right != nullptr) {
        TreeDtor(node->left);
        TreeDtor(node->right);
    }

    free(node);

    return 0;
}

//int LexicalAnalysis(char* s, Node* tokens_array)
//{
//    int i = 0;
//    int j = 0;
//
//    while(j < MAX_FORMULA_LEN) {
//        while(s[i] >= '0' && s[i] <= '9') {
//            int value = 0;
//
//            do
//        }
//
//    }
//
//    return 0;
//}