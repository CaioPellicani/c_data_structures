#ifndef _TREE_H
#define _TREE_H

#include "stdHeader.h"

#define MSG_NO_MEM "Not sufficient memory!\n"
#define MSG_NODEF_TREE "List is not defined!\n"
#define MSG_EMPTY_TREE "The List is Empty!\n"

typedef struct node {
    void * data;
    struct node* root;
    struct node* left;
    struct node* right;
}node;

typedef struct{
    node * mainRoot;
    int size;
}binaryTree;

binaryTree* initBinaryTree();

bool addRightNode( node* _root, void* _data );
bool addLeftNode( node* _root, void* _data );

node* getRoot( node* _root );
node* getLeft( node* _root );
node* getRight( node* _root );

#endif