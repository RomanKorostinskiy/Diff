//---------Operators--------------

#define IS_OP \
node->type == OP

#define IS_LEFT_OP \
node->left->type == OP

#define IS_RIGHT_OP \
node->right->type == OP

//is node a specified operator
#define IS_SPEC_OP(op) \
node->type == OP && *(char*)node->data == op

//---------Numbers--------------

//is right
#define IS_NUM \
node->type == NUM

#define IS_RIGHT_NUM \
node->right->type == NUM

#define IS_LEFT_NUM \
node->left->type == NUM

#define IS_RIGHT_SPEC_NUM(val) \
node->right->type == NUM && *(double*)node->right->data == val

#define IS_LEFT_SPEC_NUM(val) \
node->left->type == NUM && *(double*)node->left->data == val

//---------Variables--------------

#define IS_VAR \
node->type == VAR

#define IS_RIGHT_VAR \
node->right->type == VAR

#define IS_LEFT_VAR \
node->left->type == VAR

//---------Replace_Node--------------

#define REPLACE_NODE_BY_LEFT_CHILD(node, cnt_adr)   \
do {                                                \
    TreeDtor(node->right);                          \
    free(node->data);                               \
    Node* left = node->left;                        \
    memcpy(node, node->left, sizeof(Node));         \
    free(left);                                     \
    (*cnt_adr)++;                                   \
} while(0)

#define REPLACE_NODE_BY_RIGHT_CHILD(node, cnt_adr)  \
do {                                                \
    TreeDtor(node->left);                           \
    free(node->data);                               \
    Node* right = node->right;                      \
    memcpy(node, node->right, sizeof(Node));        \
    free(right);                                    \
    (*cnt_adr)++;                                   \
} while(0)

#define REPLACE_NODE_BY_ZERO(node, cnt_adr)                         \
do {                                                                \
    node->type = NUM;                                               \
    node->data = (double *) realloc(node->data, sizeof(double));    \
    *(double *) node->data = 0;                                     \
    FreeChildNodes(node);                                           \
    (*cnt_adr)++;                                                   \
} while(0)