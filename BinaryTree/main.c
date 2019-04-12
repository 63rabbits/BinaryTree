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
void *levelOrderProcess(BTN_t *R, void *parameter);
void *preOrderProcess(BTN_t *R, void *parameter);
void *inOrderProcess(BTN_t *R, void *parameter);
void *postOrderProcess(BTN_t *R, void *parameter);

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
    levelOrderTraversalOnBT(root, levelOrderProcess, NULL);
    
    printf("*** pre-order traversal ***\n");
    preOrderTraversalOnBT(root, preOrderProcess, NULL);
    
    printf("*** in-order traversal ***\n");
    inOrderTraversalOnBT(root, inOrderProcess, NULL);
    
    printf("*** post-order traversal ***\n");
    postOrderTraversalOnBT(root, postOrderProcess, NULL);
    
    printf("*** breadth first find ***\n");
    Element_t *element1 = findElementOnBT(root, findKey, BT_OPTION_TYPE_BREADTH_FIRST_SEARCH);
    printf("breadth first find keyValue %d [%s] : found value = %d\n", findKey, __func__, element1->value);
    
    printf("*** depth first find ***\n");
    Element_t *element2 = findElementOnBT(root, findKey, BT_OPTION_TYPE_DEPTH_FIRST_SEARCH);
    printf("depth first find keyValue %d [%s] : found value = %d\n", findKey, __func__, element2->value);
    
    printf("*** delete ***\n");
    printf("--- Binary Tree ---\n");
    viewBT(root, BT_OPTION_VIEW_INT);
    bool check = deleteElementOnBT(root, deleteKey);
    if (check) {
        printf("delete keyValue %d [%s] : success.\n", deleteKey, __func__);
    }
    else {
        printf("error [%s] : could not delete keyValue %d.\n", __func__, deleteKey);
    }
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

void *levelOrderProcess(BTN_t *R, void *parameter) {
    printf("level-order traversal : %d\n", R->keyValue);
    return NULL;    // none stop.
}

void *preOrderProcess(BTN_t *R, void *parameter) {
    printf("pre-order traversal : %d\n", R->keyValue);
    return NULL;    // none stop.
}

void *inOrderProcess(BTN_t *R, void *parameter) {
    printf("in-order traversal : %d\n", R->keyValue);
    return NULL;    // none stop.
}

void *postOrderProcess(BTN_t *R, void *parameter) {
    printf("post-order traversal : %d\n", R->keyValue);
    return NULL;    // none stop.
}

