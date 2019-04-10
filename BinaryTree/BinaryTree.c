#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include "BinaryTree.h"

//////////////////////////////////////////////////
BTN_t *createNodeBT(int value, void *element) {
    // Block illegal parameters.
    if (element == NULL) return NULL;
    
    BTN_t *node = malloc(sizeof(BTN_t));
    if (node == NULL) return NULL;
    
    node->value = value;
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

BTN_t *insertElementIntoBT(BTN_t *R, int value, void *element) {
    // Block illegal parameters.
    if (element == NULL) return NULL;
    
    BTN_t *target = createNodeBT(value, element);
    if (target == NULL) return NULL;
    if (R == NULL) return target;
    
    //　level-order traversal.
    QUEUE_t *Q = createQueue();
    enQueue(Q, R);
    while (!isEmptyQueue(Q)) {
        BTN_t *node = deQueue(Q);
        
        if (node->left == NULL) {
            target->parent = node;
            node->left = target;
            break;
        }
        else if (node->right == NULL) {
            target->parent = node;
            node->right = target;
            break;
        }
        enQueue(Q, node->left);
        enQueue(Q, node->right);
    }
    destroyQueue(Q, QUEUE_OPTION_NONE);
    
    return R;
}

bool deleteElementFromBT(BTN_t *R, int value) {
    // Block illegal parameters.
    if (R == NULL) return false;
    
    //    Consider a subtree rooted at the node to be deleted.
    //    Replace the deletion node with the leftmost leaf of the subtree.
    BTN_t *target = findNodeOnBT(R, value, BT_OPTION_TYPE_BREADTH_FIRST_SEARCH);
    if (target == NULL) return false;
    BTN_t *leftmost = findLeftmostLeefNodeOnBT(target);

    // change a value and element of target node. then delete a leftmost node.
    target->value = leftmost->value;
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

int findElementOnBT(BTN_t *R, int value, int type) {
    BTN_t *findNode = findNodeOnBT(R, value, type);
    if (findNode == NULL) return -1;
    return findNode->value;
}

BTN_t *findNodeOnBT(BTN_t *R, int value, int type) {
    switch (type) {
        case BT_OPTION_TYPE_BREADTH_FIRST_SEARCH:
            return breadthFirstFindNodeOnBT(R, value);
        case BT_OPTION_TYPE_DEPTH_FIRST_SEARCH:
            return depthFirstFindNodeOnBT(R, value);
        default:
            break;
    }
    return NULL;
}

int breadthFirstFindElementOnBT(BTN_t *R, int value) {
    BTN_t *findNode = breadthFirstFindNodeOnBT(R, value);
    if (findNode == NULL) return -1;
    return findNode->value;
}

BTN_t *breadthFirstFindNodeOnBT(BTN_t *R, int value) {
    // Block illegal parameters.
    if (R == NULL) return NULL;
    //　level-order traversal.
    BTN_t *findNode = NULL;
    QUEUE_t *Q = createQueue();
    enQueue(Q, R);
    while (!isEmptyQueue(Q)) {
        BTN_t * node = deQueue(Q);
        if (node->value == value) {
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

int depthFirstFindElementOnBT(BTN_t *R, int value) {
    BTN_t *findNode = depthFirstFindNodeOnBT(R, value);
    if (findNode == NULL) return -1;
    return findNode->value;
}

BTN_t *depthFirstFindNodeOnBT(BTN_t *R, int value) {
    // Block illegal parameters.
    if (R == NULL) return NULL;
    
    if (R->value == value) return R;
    BTN_t *node = NULL;
    node =depthFirstFindNodeOnBT(R->left, value);
    if (node != NULL) return node;
    node = depthFirstFindNodeOnBT(R->right, value);
    if (node != NULL) return node;
    
    return NULL;
}

void levelOrderTraversalOnBT(BTN_t *R) {
    QUEUE_t *Q = createQueue();
    enQueue(Q, R);
    while (!isEmptyQueue(Q)) {
        BTN_t * node = deQueue(Q);
        printf("level-order traversal : %d\n", node->value);
        if (node->left != NULL) {
            enQueue(Q, node->left);
        }
        if (node->right != NULL) {
            enQueue(Q, node->right);
        }
    }
    destroyQueue(Q, QUEUE_OPTION_WITH_ELEMENT);
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
        else if (leftmost->right != NULL) {
            parent = leftmost;
            leftmost = leftmost->right;
            continue;
        }
        break;
    }
    return leftmost;
}

void preOrderTraversalOnBT(BTN_t *R) {
    if (R == NULL) return;
    
    printf("pre-order traversal : %d\n", R->value);
    preOrderTraversalOnBT(R->left);
    preOrderTraversalOnBT(R->right);
}

void inOrderTraversalOnBT(BTN_t *R){
    if (R == NULL) return;
    
    inOrderTraversalOnBT(R->left);
    printf("in-order traversal : %d\n", R->value);
    inOrderTraversalOnBT(R->right);
    
}
void postOrderTraversalOnBT(BTN_t *R) {
    if (R == NULL) return;
    
    postOrderTraversalOnBT(R->left);
    postOrderTraversalOnBT(R->right);
    printf("post-order traversal : %d\n", R->value);
    
}

void viewBT(BTN_t *R, int type) {
    int wordWidth = 4;
    if (type == BT_OPTION_VIEW_CHAR) {
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
                if (type == BT_OPTION_VIEW_INT) {
                    sprintf(view[i], format10, view[i], ((BTN_t *)array[j])->value);
                }
                else {
                    sprintf(view[i], format11, view[i], (char)((BTN_t *)array[j])->value);
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
    //        printf("height = %d\n", height);    // debug
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
