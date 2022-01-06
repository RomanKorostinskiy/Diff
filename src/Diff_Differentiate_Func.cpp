#include "../include/Diff.h"
#include "../include/Diff_DSL.h"

Node* Diff(Node* node)
{
    if (IS_NUM(node)) {
        double val = 0;
        return CreateNode(NUM, &val, nullptr, nullptr);
    } else if (IS_VAR(node)) {
        double val = 1;
        return CreateNode(NUM, &val, nullptr, nullptr);
    } else if (IS_SPEC_OP(node, '+')) {
        char op = '+';
        return CreateNode(OP, &op, Diff(node->left), Diff(node->right));
    } else if (IS_SPEC_OP(node, '-')) {
        char op = '-';
        return CreateNode(OP, &op, Diff(node->left), Diff(node->right));
    } else if (IS_SPEC_OP(node, '*')) {
        char op = '*';
        Node* term1 = CreateNode(OP, &op, Diff(node->left), CopyNode(node->right));
        Node* term2 = CreateNode(OP, &op, CopyNode(node->left), Diff(node->right));

        op = '+';
        return CreateNode(OP, &op, term1, term2);
    } else if (IS_SPEC_OP(node, '^')) { //E^n
        Node* term1 = CreateNode(NUM, node->right->data, nullptr, nullptr); //n

        double one_val = 1;
        Node* one = CreateNode(NUM, &one_val, nullptr, nullptr);
        char op = '-';
        Node* degree = CreateNode(OP, &op, CopyNode(node->right), one); //n-1

        op = '^';
        Node* term2 = CreateNode(OP, &op, CopyNode(node->left), degree); //E^(n-1)

        op = '*';
        Node* term3 = CreateNode(OP, &op, term2, Diff(node->left)); //E^(n-1)*(E')

        op = '*';
        return CreateNode(OP, &op, term1, term3); //n*E^(n-1)*(E')
    } else if (IS_SPEC_OP(node, '/')) { //P/Q
        char op = '*';
        Node* minuend = CreateNode(OP, &op, Diff(node->left), CopyNode(node->right)); //(P')*Q
        Node* subtrahend = CreateNode(OP, &op, CopyNode(node->left), Diff(node->right)); //P*(Q')

        op = '-';
        Node* dividend = CreateNode(OP, &op, minuend, subtrahend); //(P')*Q - P*(Q')

        double val = 2;
        Node* degree = CreateNode(NUM, &val, nullptr, nullptr);
        op = '^';
        Node* divider = CreateNode(OP, &op, CopyNode(node->right), degree); //Q^2

        op = '/';
        return CreateNode(OP, &op, dividend, divider); //((P')*Q - P*(Q'))/Q^2
    } else if (IS_SPEC_FUNC(node, "exp")) {
        char op = '*';
        return CreateNode(OP, &op, Diff(node->left), CopyNode(node));
    } else if (IS_SPEC_FUNC(node, "ln")) {
        char op = '/';
        return CreateNode(OP, &op, Diff(node->left), CopyNode(node->left));
    } else if (IS_SPEC_FUNC(node, "sin")) { //sin(E)
        char func_name[4] = "cos";
        Node* term1 = CreateNode(FUNC, func_name, CopyNode(node->left), nullptr); //cos(E)

        char op = '*';
        return CreateNode(OP, &op, Diff(node->left), term1); //(E')*cos(E)
    } else if (IS_SPEC_FUNC(node, "cos")) { //cos(E)
        char func_name[4] = "sin";
        Node* term = CreateNode(FUNC, func_name, CopyNode(node->left), nullptr); //sin(E)

        double minus_val = -1;
        Node* minus = CreateNode(NUM, &minus_val, nullptr, nullptr);//-1

        char op = '*';
        Node* term2 = CreateNode(OP, &op, Diff(node->left), term); //(E')*sin(E)

        op = '*';
        return CreateNode(OP, &op, minus, term2); //-1*(E')*sin(E)
    }

    return CopyNode(node);
}

int Simplify(Node* node, int* smpl_cnt)
{
    if (*smpl_cnt == FIRST_CALL)
        *smpl_cnt = 0;

    if (IS_SPEC_OP(node, '*')) {
        if (IS_RIGHT_SPEC_NUM(node, 1))
            REPLACE_NODE_BY_LEFT_CHILD(node, smpl_cnt);
        else if (IS_LEFT_SPEC_NUM(node, 1))
            REPLACE_NODE_BY_RIGHT_CHILD(node, smpl_cnt);
        else if (IS_RIGHT_SPEC_NUM(node, 0) || IS_LEFT_SPEC_NUM(node, 0))
            REPLACE_NODE_BY_VALUE(node, smpl_cnt, 0);
        else if (IS_LEFT_NUM(node) && IS_RIGHT_NUM(node))
            REPLACE_NODE_BY_PROD(node, smpl_cnt);
    }

    if (IS_SPEC_OP(node, '/')) { //TODO:обрабрабатывать случай деления на 0
        if (IS_RIGHT_SPEC_NUM(node, 1))
            REPLACE_NODE_BY_LEFT_CHILD(node, smpl_cnt);
        else if (IS_LEFT_SPEC_NUM(node, 0))
            REPLACE_NODE_BY_VALUE(node, smpl_cnt, 0);
        else if (IS_LEFT_NUM(node) && IS_RIGHT_NUM(node))
            REPLACE_NODE_BY_DIV(node, smpl_cnt);
    }

    if (IS_SPEC_OP(node, '+')) {
        if (IS_RIGHT_SPEC_NUM(node, 0))
            REPLACE_NODE_BY_LEFT_CHILD(node, smpl_cnt);
        else if (IS_LEFT_SPEC_NUM(node, 0))
            REPLACE_NODE_BY_RIGHT_CHILD(node, smpl_cnt);
        else if (IS_LEFT_NUM(node) && IS_RIGHT_NUM(node))
            REPLACE_NODE_BY_SUM(node, smpl_cnt);
    }

    if (IS_SPEC_OP(node, '-')) {
        if (IS_RIGHT_SPEC_NUM(node, 0))
            REPLACE_NODE_BY_LEFT_CHILD(node, smpl_cnt);
        else if (IS_LEFT_SPEC_NUM(node, 0) && IS_RIGHT_NUM(node))
            REPLACE_NODE_BY_NEGATIVE_RIGHT_NUM_CHILD(node, smpl_cnt);
        else if (IS_LEFT_NUM(node) && IS_RIGHT_NUM(node))
            REPLACE_NODE_BY_SUB(node, smpl_cnt);
    }

    if (IS_SPEC_OP(node, '^')) {
        if (IS_RIGHT_SPEC_NUM(node, 1))
            REPLACE_NODE_BY_LEFT_CHILD(node, smpl_cnt);
        else if (IS_RIGHT_SPEC_NUM(node, 0))
            REPLACE_NODE_BY_VALUE(node, smpl_cnt, 1);
        else if (IS_LEFT_NUM(node) && IS_RIGHT_NUM(node))
            REPLACE_NODE_BY_POW(node, smpl_cnt);
    }

    if (node->left != nullptr && node->right != nullptr) {
        Simplify(node->left, smpl_cnt);
        Simplify(node->right, smpl_cnt);
    } else if (node->left != nullptr && node->right == nullptr) {
        Simplify(node->left, smpl_cnt);
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