#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include "BinaryTree.h"

//////////////////////////////////////////////////
//  private
void *insertElementAsChildOnBT(BTN_t *node, void *child);
BTN_t *findNodeOnBT(BTN_t *R, int key, BT_OPTION_e option);
void *breadthFirstFindElementOnBT(BTN_t *R, int key);
BTN_t *breadthFirstFindNodeOnBT(BTN_t *R, int key);
void *depthFirstFindElementOnBT(BTN_t *R, int key);
BTN_t *depthFirstFindNodeOnBT(BTN_t *R, int key);
BTN_t *findLeftmostLeefNodeOnBT(BTN_t *B);
//  debug
void *convertBTtoArray(BTN_t *R);
void insertBTtoArray(BTN_t *R, void **array, int index);
int getHeightBT(BTN_t *R);
int getHeightBTslave(BTN_t *R, int initValue);

//////////////////////////////////////////////////
//  public
BTN_t *createNodeBT(int key, void *element) {
    // Block illegal parameters.
    if (element == NULL) return NULL;
    
    BTN_t *node = malloc(sizeof(BTN_t));
    if (node == NULL) return NULL;
    
    node->key = key;
    node->element = element;
    node->parent = NULL;
    node->left = NULL;
    node->right = NULL;
    
    return node;
}

bool destroyNodeBT(BTN_t *R, int option) {
    // Block illegal parameters
    if (R == NULL) return false;
    
    // post-order traversal.
    destroyNodeBT(R->left, option);
    destroyNodeBT(R->right, option);
    if ((option == BT_OPTION_WITH_ELEMENT) &&
        (R->element != NULL)) {
        free(R->element);
    }
    free(R);
    
    return true;
}

BTN_t *insertElementOnBT(BTN_t *R, int key, void *element) {
    // Block illegal parameters.
    if (element == NULL) return NULL;
    
    BTN_t *node = createNodeBT(key, element);
    if (node == NULL) return NULL;
    if (R == NULL) return node;
    
    levelOrderTraversalOnBT(R, insertElementAsChildOnBT, node);
    
    return R;
}

bool deleteElementOnBT(BTN_t *R, int key) {
    // Block illegal parameters.
    if (R == NULL) return false;
    
    //    Consider a subtree rooted at the node to be deleted.
    //    Replace the deletion node with the leftmost leaf of the subtree.
    BTN_t *target = findNodeOnBT(R, key, BT_OPTION_TYPE_BREADTH_FIRST_SEARCH);
    if (target == NULL) return false;
    BTN_t *leftmost = findLeftmostLeefNodeOnBT(target);

    // change a value and element of target node. then delete a leftmost node.
    target->key = leftmost->key;
    free(target->element);
    target->element = leftmost->element;
    if (leftmost->parent != NULL) {
        if (leftmost->parent->left == leftmost) {
            leftmost->parent->left = NULL;
        }
        else {
            leftmost->parent->right = NULL;
        }
    }
    destroyNodeBT(leftmost, BT_OPTION_NONE);
    
    return true;
}

void *findElementOnBT(BTN_t *R, int key, BT_OPTION_e option) {
    BTN_t *findNode = findNodeOnBT(R, key, option);
    if (findNode == NULL) return NULL;
    return findNode->element;
}

void *levelOrderTraversalOnBT(BTN_t *R, void *(*func)(BTN_t*, void*), void *parameter) {
    // Block illegal paramaters.
    if (R == NULL) return false;
    
    QUEUE_t *Q = createQueue();
    enQueue(Q, R);
    while (true) {
        BTN_t *node = deQueue(Q);
        if (node == NULL) break;
        
        void *p = func(node, parameter);
        if (p != NULL) {
            destroyQueue(Q, QUEUE_OPTION_NONE);
            return p;
        }
        if (node->left != NULL) {
            enQueue(Q, node->left);
        }
        if (node->right != NULL) {
            enQueue(Q, node->right);
        }
    }
    destroyQueue(Q, QUEUE_OPTION_NONE);
    return NULL;
}

void *preOrderTraversalOnBT(BTN_t *R, void *(*func)(BTN_t*, void*), void *parameter) {
    if (R == NULL) return NULL;
    
    void *p = NULL;
    p = func(R, parameter);
    if (p != NULL) return p;
    p = preOrderTraversalOnBT(R->left, func, parameter);
    if (p != NULL) return p;
    p = preOrderTraversalOnBT(R->right, func, parameter);
    if (p != NULL) return p;
    
    return NULL;
}

void *inOrderTraversalOnBT(BTN_t *R, void *(*func)(BTN_t*, void*), void *parameter) {
    if (R == NULL) return NULL;
    
    void *p = NULL;
    p = inOrderTraversalOnBT(R->left, func, parameter);
    if (p != NULL) return p;
    p = func(R, parameter);
    if (p != NULL) return p;
    p = inOrderTraversalOnBT(R->right, func, parameter);
    if (p != NULL) return p;
    
    return NULL;
}

void *postOrderTraversalOnBT(BTN_t *R, void *(*func)(BTN_t*, void*), void *parameter) {
    if (R == NULL) return NULL;
    
    void *p = NULL;
    p = postOrderTraversalOnBT(R->left, func, parameter);
    if (p != NULL) return p;
    p = postOrderTraversalOnBT(R->right, func, parameter);
    if (p != NULL) return p;
    p = func(R, parameter);
    if (p != NULL) return p;
    
    return NULL;
}

//////////////////////////////////////////////////
//  private
void *insertElementAsChildOnBT(BTN_t *node, void *child) {
    if (node == NULL) return NULL;
    
    if (node->left == NULL) {
        ((BTN_t *)child)->parent = node;
        node->left = child;
        return child;
    }
    if (node->right == NULL) {
        ((BTN_t *)child)->parent = node;
        node->right = child;
        return child;
    }
    
    return NULL;
}

BTN_t *findNodeOnBT(BTN_t *R, int key, BT_OPTION_e option) {
    switch (option) {
        case BT_OPTION_TYPE_BREADTH_FIRST_SEARCH:
            return breadthFirstFindNodeOnBT(R, key);
        case BT_OPTION_TYPE_DEPTH_FIRST_SEARCH:
            return depthFirstFindNodeOnBT(R, key);
        default:
            break;
    }
    return NULL;
}

void *breadthFirstFindElementOnBT(BTN_t *R, int key) {
    BTN_t *findNode = breadthFirstFindNodeOnBT(R, key);
    if (findNode == NULL) return NULL;
    return findNode->element;
}

BTN_t *breadthFirstFindNodeOnBT(BTN_t *R, int key) {
    // Block illegal parameters.
    if (R == NULL) return NULL;
    //　level-order traversal.
    BTN_t *findNode = NULL;
    QUEUE_t *Q = createQueue();
    enQueue(Q, R);
    while (true) {
        BTN_t * node = deQueue(Q);
        if (node == NULL) break;
        
        if (node->key == key) {
            findNode = node;
            break;
        }
        if (node->left != NULL) {
            enQueue(Q, node->left);
        }
        if (node->right != NULL) {
            enQueue(Q, node->right);
        }
    }
    destroyQueue(Q, QUEUE_OPTION_NONE);
    return findNode;
}

void *depthFirstFindElementOnBT(BTN_t *R, int key) {
    BTN_t *findNode = depthFirstFindNodeOnBT(R, key);
    if (findNode == NULL) return NULL;
    return findNode->element;
}

BTN_t *depthFirstFindNodeOnBT(BTN_t *R, int key) {
    // Block illegal parameters.
    if (R == NULL) return NULL;
    
    //  pre-order traversal.
    if (R->key == key) return R;
    BTN_t *node = NULL;
    node =depthFirstFindNodeOnBT(R->left, key);
    if (node != NULL) return node;
    node = depthFirstFindNodeOnBT(R->right, key);
    if (node != NULL) return node;
    
    return NULL;
}

BTN_t *findLeftmostLeefNodeOnBT(BTN_t *B) {
    BTN_t *parent = NULL;
    BTN_t *leftmost = B;
    while (true) {
        if (leftmost->left != NULL) {
            parent = leftmost;
            leftmost = leftmost->left;
            continue;
        }
        if (leftmost->right != NULL) {
            parent = leftmost;
            leftmost = leftmost->right;
            continue;
        }
        break;
    }
    return leftmost;
}

//////////////////////////////////////////////////
//  debug
#define getParent(v) ((v - 1) / 2)
#define getLeftIndex(v) (v * 2 + 1)
#define getRightIndex(v) (v * 2 + 2)
#define max(a, b) (a > b ? a : b)

void viewBT(BTN_t *R, BT_OPTION_e option) {
    int wordWidth = 4;
    if (option == BT_OPTION_VIEW_CHAR) {
        wordWidth = 2;
    }
    int height = getHeightBT(R);
    
    // insert binary tree into array.
    void **array = convertBTtoArray(R);
    
    // veiw Binary Tree.
    int numOfNodes = (int)pow(2, height);
    int width = wordWidth * numOfNodes;
    char view[height+1][width+1];
    for (int i=0; i<=height; i++) {
        view[i][0] = '\0';
    }
    
    char format10[32] = "";
    char format11[32] = "";
    char format20[32] = "";
    char padding[32] = "";
    for (int i=0; i<wordWidth; i++) {
        strcat(padding, " ");
    }
//    padding[wordWidth-1] = '_';
    sprintf(format10, "%%s%%%dd", wordWidth);
    sprintf(format11, "%%s%%%dc", wordWidth);
    sprintf(format20, "%%s%s", padding);
    
    int leftmostIndex = pow(2, height) - 1;
    int rightmostIndex = pow(2, height+1) - 2;
    for (int i=height; i>=0; i--) {
        int numOfPadding = (width - (wordWidth * numOfNodes))/numOfNodes;
        for (int j=0; (i!=height) && (j<numOfPadding/2); j++) {
            strcat(view[i], " ");
        }
        for (int j=leftmostIndex; j<=rightmostIndex; j++) {
            if (array[j] != NULL) {
                if (option == BT_OPTION_VIEW_INT) {
                    sprintf(view[i], format10, view[i], ((BTN_t *)array[j])->key);
                }
                else {
                    sprintf(view[i], format11, view[i], (char)((BTN_t *)array[j])->key);
                }
            }
            else {
                sprintf(view[i], format20, view[i]);
            }
            for (int k=0; (i!=height) && (k<numOfPadding); k++) {
                strcat(view[i], " ");
                if (strlen(view[i]) >= width - 1) break;
            }
        }
        leftmostIndex = getParent(leftmostIndex);
        rightmostIndex = getParent(rightmostIndex);
        numOfNodes = numOfNodes >> 1;
    }
    for (int i=0; i<=height; i++) {
        printf("\nLevel #%02d %s\n", i, view[i]);
    }
    printf("\n");
    
    free(array);
}

void *convertBTtoArray(BTN_t *R) {
    int height = getHeightBT(R);
    if (height < 0) return NULL;
    
    int length = pow(2, height+1) - 1;
    void **array = calloc(length, sizeof(void*));
    if (array == NULL) {
        printf("error [%s] : could not allocation memory.\n", __func__);
        return NULL;
    }
    
    insertBTtoArray(R, array, 0);
    
    return array;
}

void insertBTtoArray(BTN_t *R, void **array, int index) {
    if (R == NULL) return;
    
    array[index] = R;
    insertBTtoArray(R->left, array, getLeftIndex(index));
    insertBTtoArray(R->right, array, getRightIndex(index));
}

int getHeightBT(BTN_t *R) {
    return getHeightBTslave(R, -1);
}

int getHeightBTslave(BTN_t *R, int initValue) {
    // pre-order traversal.
    if (R == NULL) return initValue;
    
    initValue++;
    int leftHeight = getHeightBTslave(R->left, initValue);
    int rightHeight = getHeightBTslave(R->right, initValue);
    return max(leftHeight, rightHeight);
}
