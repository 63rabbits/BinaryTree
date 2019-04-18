#ifndef BinaryTree_h
#define BinaryTree_h

#include <stdbool.h>

//////////////////////////////////////////////////
typedef enum BTOption {
    BT_OPTION_NONE,
    BT_OPTION_WITH_ELEMENT,
    
    BT_OPTION_BREADTH_FIRST_SEARCH = 10,
    BT_OPTION_DEPTH_FIRST_SEARCH,
    
    BT_OPTION_VIEW_INT = 20,
    BT_OPTION_VIEW_CHAR
} BT_OPTION_e;

typedef struct BinaryTeee_Node {
    int keyValue;
    void *element;
    struct BinaryTeee_Node *parent;
    struct BinaryTeee_Node *left;
    struct BinaryTeee_Node *right;
} BTN_t;

//////////////////////////////////////////////////
bool destroyBT(BTN_t *R, BT_OPTION_e option);
BTN_t *insertElementOnBT(BTN_t *R, int keyValue, void *element);
bool deleteElementOnBT(BTN_t *R, int keyValue);
void *findElementOnBT(BTN_t *R, int keyValue, BT_OPTION_e option);
void *levelOrderTraversalOnBT(BTN_t *R, void *(*func)(BTN_t*, void*), void *parameter);
void *preOrderTraversalOnBT(BTN_t *R, void *(*func)(BTN_t*, void*), void *parameter);
void *inOrderTraversalOnBT(BTN_t *R, void *(*func)(BTN_t*, void*), void *parameter);
void *postOrderTraversalOnBT(BTN_t *R, void *(*func)(BTN_t*, void*), void *parameter);
int getHeightBT(BTN_t *R);
void *getElementOnBT(BTN_t *R);

#ifdef DEBUG
void viewBT(BTN_t *R, BT_OPTION_e option);
#endif

#endif
