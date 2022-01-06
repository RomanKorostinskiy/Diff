//---------Operators--------------

#define IS_OP(node) \
node->type == OP

#define IS_LEFT_OP(node) \
node->left->type == OP

#define IS_RIGHT_OP(node) \
node->right->type == OP

//is node a specified operator
#define IS_SPEC_OP(node, op) \
node->type == OP && *(char*)node->data == op

//---------Numbers--------------

//is right
#define IS_NUM(node) \
node->type == NUM

#define IS_RIGHT_NUM(node) \
node->right->type == NUM

#define IS_LEFT_NUM(node) \
node->left->type == NUM

#define IS_RIGHT_SPEC_NUM(node, val) \
node->right->type == NUM && *(double*)node->right->data == val

#define IS_LEFT_SPEC_NUM(node, val) \
node->left->type == NUM && *(double*)node->left->data == val

//---------Variables--------------

#define IS_VAR(node) \
node->type == VAR

#define IS_RIGHT_VAR(node) \
node->right->type == VAR

#define IS_LEFT_VAR(node) \
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

#define REPLACE_NODE_BY_NEGATIVE_RIGHT_NUM_CHILD(node, cnt_adr)     \
do {                                                                \
    node->type = NUM;                                               \
    double old_value = *(double*)node->right->data;                 \
    node->data = (double *) realloc(node->data, sizeof(double));    \
    *(double *) node->data = -old_value;                            \
    FreeChildNodes(node);                                           \
    (*cnt_adr)++;                                                   \
} while(0)


#define REPLACE_NODE_BY_VALUE(node, cnt_adr, val)                   \
do {                                                                \
    node->type = NUM;                                               \
    node->data = (double *) realloc(node->data, sizeof(double));    \
    *(double *) node->data = val;                                   \
    FreeChildNodes(node);                                           \
    (*cnt_adr)++;                                                   \
} while(0)

#define REPLACE_NODE_BY_SUM(node, cnt_adr)                                              \
do {                                                                                    \
    node->type = NUM;                                                                   \
    node->data = (double *) realloc(node->data, sizeof(double));                        \
    *(double *) node->data = *(double*) node->left->data + *(double*) node->right->data;\
    FreeChildNodes(node);                                                               \
    (*cnt_adr)++;                                                                       \
                                                                                        \
} while(0)

#define REPLACE_NODE_BY_SUB(node, cnt_adr)                                              \
do {                                                                                    \
    node->type = NUM;                                                                   \
    node->data = (double *) realloc(node->data, sizeof(double));                        \
    *(double *) node->data = *(double*) node->left->data - *(double*) node->right->data;\
    FreeChildNodes(node);                                                               \
    (*cnt_adr)++;                                                                       \
                                                                                        \
} while(0)

#define REPLACE_NODE_BY_PROD(node, cnt_adr)                                             \
do {                                                                                    \
    node->type = NUM;                                                                   \
    node->data = (double *) realloc(node->data, sizeof(double));                        \
    *(double *) node->data = *(double*) node->left->data * *(double*) node->right->data;\
    FreeChildNodes(node);                                                               \
    (*cnt_adr)++;                                                                       \
} while(0)

#define REPLACE_NODE_BY_DIV(node, cnt_adr)                                              \
do {                                                                                    \
    node->type = NUM;                                                                   \
    node->data = (double *) realloc(node->data, sizeof(double));                        \
    *(double *) node->data = *(double*) node->left->data / *(double*) node->right->data;\
    FreeChildNodes(node);                                                               \
    (*cnt_adr)++;                                                                       \
} while(0)