#include "../include/Diff.h"
#include "../include/Diff_DSL.h"

Node* Diff(Node* node)
{
    if (IS_NUM) {
        double val = 0;
        return CreateNode(NUM, &val, nullptr, nullptr);
    } else if (IS_VAR) {
        double val = 1;
        return CreateNode(NUM, &val, nullptr, nullptr);
    } else if (IS_SPEC_OP('+')) {
        char op = '+';
        return CreateNode(OP, &op, Diff(node->left), Diff(node->right));
    } else if (IS_SPEC_OP('*')) {
        char op = '*';
        Node* term1 = CreateNode(OP, &op, Diff(node->left), CopyNode(node->right));
        Node* term2 = CreateNode(OP, &op, CopyNode(node->left), Diff(node->right));
        return CreateNode(OP, &op, term1, term2);
    }

    return CopyNode(node);
}

int Simplify(Node* node)
{
    if(IS_SPEC_OP('*') && IS_RIGHT_SPEC_NUM(1)) {
        if(IS_LEFT_NUM) {
            node->type = NUM;
            node->data = (double *) realloc(node->data, sizeof(double));
            *(double *) node->data = *(double *) node->left->data;
            FreeChildNodes(node);
        }
    }

    if (node->left != nullptr && node->right != nullptr) {
        Simplify(node->left);
        Simplify(node->right);
    }

    return 0;
}