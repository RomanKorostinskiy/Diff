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
        op = '+';
        return CreateNode(OP, &op, term1, term2);
    }

    return CopyNode(node);
}

int Simplify(Node* node, int* smpl_cnt)
{
    if (*smpl_cnt == FIRST_CALL)
        *smpl_cnt = 0;

    if (IS_SPEC_OP('*') && IS_RIGHT_SPEC_NUM(1)) {
        REPLACE_NODE_BY_LEFT_CHILD(node, smpl_cnt);
    } else if (IS_SPEC_OP('*') && IS_LEFT_SPEC_NUM(1)) {
        REPLACE_NODE_BY_RIGHT_CHILD(node, smpl_cnt);
    } else if (IS_SPEC_OP('*') && (IS_RIGHT_SPEC_NUM(0) || IS_LEFT_SPEC_NUM(0))) {
        REPLACE_NODE_BY_ZERO(node, smpl_cnt);
    }

    if (IS_SPEC_OP('+') && IS_RIGHT_SPEC_NUM(0)) {
        REPLACE_NODE_BY_LEFT_CHILD(node, smpl_cnt);
    } else if (IS_SPEC_OP('+') && IS_LEFT_SPEC_NUM(0)) {
        REPLACE_NODE_BY_RIGHT_CHILD(node, smpl_cnt);
    }

    if (node->left != nullptr && node->right != nullptr) {
        Simplify(node->left, smpl_cnt);
        Simplify(node->right, smpl_cnt);
    }

    return 0;
}

int LoopSimplify(Node* root)
{
    int smpl_cnt = FIRST_CALL;
    while (smpl_cnt != 0) {
        smpl_cnt = FIRST_CALL;
        Simplify(root, &smpl_cnt);
        TreeDump(root, "Simplify");
    }

    return 0;
}