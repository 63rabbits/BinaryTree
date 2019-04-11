#ifndef BinaryTree_h
#define BinaryTree_h

#include <stdbool.h>
#include "Queue.h"

//////////////////////////////////////////////////
typedef enum BTOption {
    BT_OPTION_NONE,
    BT_OPTION_WITH_ELEMENT,
    
    BT_OPTION_TYPE_BREADTH_FIRST_SEARCH = 10,
    BT_OPTION_TYPE_DEPTH_FIRST_SEARCH,
    
    BT_OPTION_VIEW_INT = 20,
    BT_OPTION_VIEW_CHAR
} BT_OPTION_e;

typedef struct BinaryTeee_Node {
    int key;
    void *element;
    struct BinaryTeee_Node *parent;
    struct BinaryTeee_Node *left;
    struct BinaryTeee_Node *right;
} BTN_t;

//////////////////////////////////////////////////
BTN_t *createNodeBT(int key, void *element);
bool destroyNodeBT(BTN_t *R, int option);
BTN_t *insertElementOnBT(BTN_t *R, int key, void *element);
bool deleteElementOnBT(BTN_t *R, int key);
void *findElementOnBT(BTN_t *R, int key, BT_OPTION_e option);
void *levelOrderElementTraversalOnBT(BTN_t *R, void *(*func)(void *));
void *preOrderElementTraversalOnBT(BTN_t *R, void *(*func)(void *));
void *inOrderElementTraversalOnBT(BTN_t *R, void *(*func)(void *));
void *postOrderElementTraversalOnBT(BTN_t *R, void *(*func)(void *));
// for debug
void viewBT(BTN_t *R, BT_OPTION_e option);

#endif
