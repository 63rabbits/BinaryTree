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
void *levelOrderTraversalOnBTslave(BTN_t *R, void *parameter);
void *preOrderTraversalOnBTslave(BTN_t *R, void *parameter);
void *inOrderTraversalOnBTslave(BTN_t *R, void *parameter);
void *postOrderTraversalOnBTslave(BTN_t *R, void *parameter);

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
        Element_t *element = createElement(i);
        root = insertElementOnBT(root, i, element);
        if (root == NULL) {
            printf("error [%s] : could not insert %d.\n", __func__, i);
            destroyElement(element);
            return;
        }
    }

#ifdef DEBUG
    viewBT(root, BT_OPTION_VIEW_INT);
#endif
    
    printf("\n*** level-order traversal ***\n");
    levelOrderTraversalOnBT(root, levelOrderTraversalOnBTslave, NULL);
    
    printf("\n*** pre-order traversal ***\n");
    preOrderTraversalOnBT(root, preOrderTraversalOnBTslave, NULL);
    
    printf("\n*** in-order traversal ***\n");
    inOrderTraversalOnBT(root, inOrderTraversalOnBTslave, NULL);
    
    printf("\n*** post-order traversal ***\n");
    postOrderTraversalOnBT(root, postOrderTraversalOnBTslave, NULL);
    
    printf("\n*** breadth first find ***\n");
    Element_t *element1 = findElementOnBT(root, findKey, BT_OPTION_BREADTH_FIRST_SEARCH);
    printf("breadth first find keyValue %d [%s] : found value = %d\n", findKey, __func__, element1->value);
    
    printf("\n*** depth first find ***\n");
    Element_t *element2 = findElementOnBT(root, findKey, BT_OPTION_DEPTH_FIRST_SEARCH);
    printf("depth first find keyValue %d [%s] : found value = %d\n", findKey, __func__, element2->value);
    
    printf("\n*** delete ***\n");
#ifdef DEBUG
    viewBT(root, BT_OPTION_VIEW_INT);
#endif
    bool check = deleteElementOnBT(root, deleteKey);
    if (check) {
        printf("delete keyValue %d [%s] : success.\n", deleteKey, __func__);
    }
    else {
        printf("error [%s] : could not delete keyValue %d.\n", __func__, deleteKey);
    }

#ifdef DEBUG
    viewBT(root, BT_OPTION_VIEW_INT);
#endif
    
    destroyBT(root, BT_OPTION_WITH_ELEMENT);
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

void *levelOrderTraversalOnBTslave(BTN_t *R, void *parameter) {
    Element_t *element = getElementOnBT(R);

    printf("level-order traversal : %d\n", element->value);
    return NULL;    // none stop.
}

void *preOrderTraversalOnBTslave(BTN_t *R, void *parameter) {
    Element_t *element = getElementOnBT(R);

    printf("pre-order traversal : %d\n", element->value);
    return NULL;    // none stop.
}

void *inOrderTraversalOnBTslave(BTN_t *R, void *parameter) {
    Element_t *element = getElementOnBT(R);

    printf("in-order traversal : %d\n", element->value);
    return NULL;    // none stop.
}

void *postOrderTraversalOnBTslave(BTN_t *R, void *parameter) {
    Element_t *element = getElementOnBT(R);

    printf("post-order traversal : %d\n", element->value);
    return NULL;    // none stop.
}

