//---------Operators--------------

#define IS_OP \
node->type == OP

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
