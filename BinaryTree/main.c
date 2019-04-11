#include <unistd.h>
//#define checkMemoryLeak

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>
#include "BinaryTree.h"

//////////////////////////////////////////////////
typedef struct Element {
    int value;
} Element_t;

//////////////////////////////////////////////////
void test(void);
Element_t *createElement(int value);
bool destroyElement(Element_t *element);
bool levelOrderProcess(void *R);
bool preOrderProcess(void *R);
bool inOrderProcess(void *R);
bool postOrderProcess(void *R);

//////////////////////////////////////////////////
int main(int argc, const char * argv[]) {
    
#ifdef checkMemoryLeak
    while (true) {
        test();
        sleep(1);
    }
#else
    test();
#endif
    
    return EXIT_SUCCESS;
}

void test() {
    int numNode = 10;
    int findValue = 5;
    int deleteValue = 2;
    
    BTN_t *root = NULL;
    for (int i=0; i<numNode; i++) {
        Element_t *element = createElement(i*10);
        root = insertElementIntoBT(root, i, element);
        if (root == NULL) {
            printf("error [%s] : could not insert %d.\n", __func__, i);
            destroyElement(element);
            return;
        }
    }
    printf("--- Binary Tree ---\n");
    viewBT(root, BT_OPTION_VIEW_INT);

    printf("*** level-order traversal ***\n");
    levelOrderTraversalOnBT(root, levelOrderProcess);
    
    printf("*** pre-order traversal ***\n");
    preOrderTraversalOnBT(root, preOrderProcess);
    
    printf("*** in-order traversal ***\n");
    inOrderTraversalOnBT(root, inOrderProcess);
    
    printf("*** post-order traversal ***\n");
    postOrderTraversalOnBT(root, postOrderProcess);
    
    printf("*** breadth first find ***\n");
    int value = findElementOnBT(root, findValue, BT_OPTION_TYPE_BREADTH_FIRST_SEARCH);
    printf("breadth first find %d [%s] : found value = %d\n", findValue, __func__, value);
    
    printf("*** depth first find ***\n");
    value = findElementOnBT(root, findValue, BT_OPTION_TYPE_DEPTH_FIRST_SEARCH);
    printf("depth first find %d [%s] : found value = %d\n", findValue, __func__, value);
    
    printf("*** delete ***\n");
    printf("--- Binary Tree ---\n");
    viewBT(root, BT_OPTION_VIEW_INT);
    bool check = deleteElementFromBT(root, deleteValue);
    if (check) {
        printf("delete value %d [%s] : success.\n", deleteValue, __func__);
    }
    else {
        printf("error [%s] : could not delete value %d.\n", __func__, deleteValue);
    }
//    printf("*** level-order traversal ***\n");
//    levelOrderTraversalOnBT(root);
    printf("--- Binary Tree ---\n");
    viewBT(root, BT_OPTION_VIEW_INT);
    
    destroyNodeBT(root, BT_OPTION_WITH_ELEMENT);
}

Element_t *createElement(int value) {
    Element_t *element = malloc(sizeof(Element_t));
    if (element == NULL) return NULL;
    element->value = value;
    return element;
}

bool destroyElement(Element_t *element) {
    // Block illegal parameters.
    if (element == NULL) return false;
    free(element);
    return true;
}

bool levelOrderProcess(void *R) {
    printf("level-order traversal : %d\n", ((BTN_t*)R)->value);
    return false;
}

bool preOrderProcess(void *R) {
    printf("pre-order traversal : %d\n", ((BTN_t*)R)->value);
    return false;
}

bool inOrderProcess(void *R) {
    printf("in-order traversal : %d\n", ((BTN_t*)R)->value);
    return false;
}

bool postOrderProcess(void *R) {
    printf("post-order traversal : %d\n", ((BTN_t*)R)->value);
    return false;
}

