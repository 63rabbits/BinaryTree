#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include "BinaryTree.h"

//////////////////////////////////////////////////
//  private
BTN_t *findNodeOnBT(BTN_t *R, int keyValue, BT_OPTION_e option);
BTN_t *findLeftmostLeefNodeOnBT(BTN_t *B);
void *insertElementOnBTslave(BTN_t *R, void *child);
void *destroyNodeBTslave(BTN_t *R, void *option);
void *findNodeOnBTslave(BTN_t *R, void *option);
//  debug
void *convertBTtoArray(BTN_t *R);
void insertBTtoArray(BTN_t *R, void **array, int index);
int getHeightBTslave(BTN_t *R, int initValue);

//////////////////////////////////////////////////
//  public
BTN_t *createNodeBT(int keyValue, void *element) {
    // Block illegal parameters.
    if (element == NULL) return NULL;
    
    BTN_t *node = malloc(sizeof(BTN_t));
    if (node == NULL) return NULL;
    node->keyValue = keyValue;
    node->element = element;
    node->parent = NULL;
    node->left = NULL;
    node->right = NULL;
    
    return node;
}

bool destroyNodeBT(BTN_t *R, BT_OPTION_e option) {
    // Block illegal parameters
    if (R == NULL) return false;
    
    preOrderTraversalOnBT(R, destroyNodeBTslave, &option);
    
    return true;
}

BTN_t *insertElementOnBT(BTN_t *R, int keyValue, void *element) {
    // Block illegal parameters.
    if (element == NULL) return NULL;
    
    BTN_t *node = createNodeBT(keyValue, element);
    if (node == NULL) return NULL;
    if (R == NULL) return node;
    levelOrderTraversalOnBT(R, insertElementOnBTslave, node);
    
    return R;
}

bool deleteElementOnBT(BTN_t *R, int keyValue) {
    // Block illegal parameters.
    if (R == NULL) return false;
    
    //    Consider a subtree rooted at the node to be deleted.
    //    Replace the deletion node with the leftmost leaf of the subtree.
    BTN_t *target = findNodeOnBT(R, keyValue, BT_OPTION_BREADTH_FIRST_SEARCH);
    if (target == NULL) return false;
    BTN_t *leftmost = findLeftmostLeefNodeOnBT(target);

    // change a value and element of target node. then delete a leftmost node.
    target->keyValue = leftmost->keyValue;
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

void *findElementOnBT(BTN_t *R, int keyValue, BT_OPTION_e option) {
    BTN_t *findNode = findNodeOnBT(R, keyValue, option);
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

int getHeightBT(BTN_t *R) {
    return getHeightBTslave(R, -1);
}

void *getElementOnBT(BTN_t *R) {
    // Block illegal parameters.
    if (R == NULL) return NULL;
    
    return R->element;
}

//////////////////////////////////////////////////
//  private
BTN_t *findNodeOnBT(BTN_t *R, int keyValue, BT_OPTION_e option) {
    BTN_t *node = NULL;
    switch (option) {
        case BT_OPTION_BREADTH_FIRST_SEARCH:
            node = levelOrderTraversalOnBT(R, findNodeOnBTslave, &keyValue);
            if (node != NULL) return node;
            break;
        case BT_OPTION_DEPTH_FIRST_SEARCH:
            node = preOrderTraversalOnBT(R, findNodeOnBTslave, &keyValue);
            if (node != NULL) return node;
            break;
        default:
            break;
    }
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

void *insertElementOnBTslave(BTN_t *R, void *parameter) {
    if (R == NULL) return NULL;
    
    BTN_t *parent = R;
    BTN_t *child = parameter;
    if (parent->left == NULL) {
        child->parent = parent;
        parent->left = child;
        return child;
    }
    if (parent->right == NULL) {
        child->parent = parent;
        parent->right = child;
        return child;
    }
    
    return NULL;
}

void *destroyNodeBTslave(BTN_t *R, void *parameter) {
    // Block illegal parameters.
    if (R == NULL) return NULL;
    
    int option = *((int *)parameter);
    if ((option == BT_OPTION_WITH_ELEMENT) &&
        (R->element != NULL)) {
        free(R->element);
    }
    free(R);
    
    return NULL;
}

void *findNodeOnBTslave(BTN_t *R, void *parameter) {
    // Block illegal parameters.
    if (R == NULL) return NULL;
    
    if (R->keyValue == *((int*)parameter)) return R;
    return NULL;
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
                    sprintf(view[i], format10, view[i], ((BTN_t *)array[j])->keyValue);
                }
                else {
                    sprintf(view[i], format11, view[i], (char)((BTN_t *)array[j])->keyValue);
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

int getHeightBTslave(BTN_t *R, int initValue) {
    // pre-order traversal.
    if (R == NULL) return initValue;
    
    initValue++;
    int leftHeight = getHeightBTslave(R->left, initValue);
    int rightHeight = getHeightBTslave(R->right, initValue);
    return max(leftHeight, rightHeight);
}
