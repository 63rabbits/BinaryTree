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
    int value;
    void *element;
    struct BinaryTeee_Node *parent;
    struct BinaryTeee_Node *left;
    struct BinaryTeee_Node *right;
} BTN_t;

//////////////////////////////////////////////////
BTN_t *createNodeBT(int value, void *element);
bool destroyNodeBT(BTN_t *R, int option);
BTN_t *insertElementIntoBT(BTN_t *R, int value, void *element);
bool deleteElementFromBT(BTN_t *R, int key);
int findElementOnBT(BTN_t *R, int value, int type);
BTN_t *findNodeOnBT(BTN_t *R, int value, int type);
int breadthFirstFindElementOnBT(BTN_t *R, int value);
BTN_t *breadthFirstFindNodeOnBT(BTN_t *R, int value);
int depthFirstFindElementOnBT(BTN_t *R, int value);
BTN_t *depthFirstFindNodeOnBT(BTN_t *R, int value);
BTN_t *findLeftmostLeefNodeOnBT(BTN_t *B);
bool levelOrderTraversalOnBT(BTN_t *R, bool (*func)(void *));
bool preOrderTraversalOnBT(BTN_t *R, bool (*func)(void *));
bool inOrderTraversalOnBT(BTN_t *R, bool (*func)(void *));
bool postOrderTraversalOnBT(BTN_t *R, bool (*func)(void *));
void viewBT(BTN_t *R, int type);
void *convertBTtoArray(BTN_t *R);
void insertBTtoArray(BTN_t *R, void **array, int index);
int getHeightBT(BTN_t *R);
int getHeightBTslave(BTN_t *R, int initValue);

#endif
