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
void *levelOrderProcess(void *R);
void *preOrderProcess(void *R);
void *inOrderProcess(void *R);
void *postOrderProcess(void *R);

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
    int findKey = 5;
    int deleteKey = 2;
    
    BTN_t *root = NULL;
    for (int i=0; i<numNode; i++) {
        Element_t *element = createElement(i*10);
        root = insertElementOnBT(root, i, element);
        if (root == NULL) {
            printf("error [%s] : could not insert %d.\n", __func__, i);
            destroyElement(element);
            return;
        }
    }
    printf("--- Binary Tree ---\n");
    viewBT(root, BT_OPTION_VIEW_INT);

    printf("*** level-order traversal ***\n");
    levelOrderElementTraversalOnBT(root, levelOrderProcess);
    
    printf("*** pre-order traversal ***\n");
    preOrderElementTraversalOnBT(root, preOrderProcess);
    
    printf("*** in-order traversal ***\n");
    inOrderElementTraversalOnBT(root, inOrderProcess);
    
    printf("*** post-order traversal ***\n");
    postOrderElementTraversalOnBT(root, postOrderProcess);
    
    printf("*** breadth first find ***\n");
    Element_t *element1 = findElementOnBT(root, findKey, BT_OPTION_TYPE_BREADTH_FIRST_SEARCH);
    printf("breadth first find key %d [%s] : found value = %d\n", findKey, __func__, element1->value);
    
    printf("*** depth first find ***\n");
    Element_t *element2 = findElementOnBT(root, findKey, BT_OPTION_TYPE_DEPTH_FIRST_SEARCH);
    printf("depth first find key %d [%s] : found value = %d\n", findKey, __func__, element2->value);
    
    printf("*** delete ***\n");
    printf("--- Binary Tree ---\n");
    viewBT(root, BT_OPTION_VIEW_INT);
    bool check = deleteElementOnBT(root, deleteKey);
    if (check) {
        printf("delete key %d [%s] : success.\n", deleteKey, __func__);
    }
    else {
        printf("error [%s] : could not delete key %d.\n", __func__, deleteKey);
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

void *levelOrderProcess(void *R) {
    printf("level-order traversal : %d\n", ((BTN_t*)R)->key);
    return NULL;    // none stop.
}

void *preOrderProcess(void *R) {
    printf("pre-order traversal : %d\n", ((BTN_t*)R)->key);
    return NULL;    // none stop.
}

void *inOrderProcess(void *R) {
    printf("in-order traversal : %d\n", ((BTN_t*)R)->key);
    return NULL;    // none stop.
}

void *postOrderProcess(void *R) {
    printf("post-order traversal : %d\n", ((BTN_t*)R)->key);
    return NULL;    // none stop.
}

