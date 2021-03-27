#include "binary_tree.h"

node* newBlankNode();

binaryTree* initBinaryTree(){
    binaryTree* newTree;
    newTree = ( binaryTree* ) malloc( sizeof( binaryTree ) );
    if( newTree == NULL ){
        die( MSG_NO_MEM ); 
    }
    else{
        newTree->size = 0;
        newTree->mainRoot = NULL;
        return newTree;
    }
}

node* newBlankNode(){
    node* newNode;
    newNode = malloc( sizeof( node ) );
    newNode->data = NULL;
    newNode->root = newNode->left = newNode->right = NULL;
    return newNode;
}

bool addRightNode( node* _root, void* _data ){
    node* newNode = newBlankNode();
    newNode->root = _root;
    newNode->data = _data;
    _root->right = newNode;
    return true;    
}

bool addLeftNode( node* _root, void* _data ){
    node* newNode = newBlankNode();
    newNode->root = _root;
    newNode->data = _data;
    _root->left = newNode;
    return true;    
}

