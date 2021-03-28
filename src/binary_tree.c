#include "binary_tree.h"

node* newBlankNode();
bool addNode( node* _root, void* _data, int letfNode );
node* getNode( node* _root, int where );

enum cordenates{ ROOT, LEFT, RIGHT, BOTHER };

binaryTree* initBinaryTree(){
    binaryTree* newTree;
    newTree = ( binaryTree* ) malloc( sizeof( binaryTree ) );
    if( newTree == NULL ){
        die( MSG_NO_MEM ); 
        return NULL;
    }
    else{
        newTree->size = 0;
        newTree->mainRoot = newBlankNode();
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

node** positioning( node* _root, int where ){
    switch ( where ){
    case ROOT:
        return &_root->root;
        break;
    case LEFT:
        return &_root->left;
        break;
    case RIGHT:
        return &_root->right;
        break;
    case BOTHER:
        if( _root->root->left == _root ){
            return &_root->root->right;     
        }
        else{
            return &_root->root->left;
        }
    }
}

bool addNode( node* _root, void* _data, int where ){
    node **position = positioning( _root, where );

    if( *position != NULL ){
        return false;
    }
    node* newNode = newBlankNode();
    newNode->root = _root;
    newNode->data = _data;
    *position = newNode;

    return true; 
}

bool addRightNode( node* _root, void* _data ){ return addNode( _root, _data, RIGHT );}
bool addLeftNode( node* _root, void* _data ){  return addNode( _root, _data, LEFT ); }

node* getNode( node* _root, int where ){
    node **position = positioning( _root, where );

    if( position == NULL ){
        return NULL;
    } 
    else{
        return *position;
    }
}

node* getRoot( node* _root ){  return getNode( _root, ROOT ); }
node* getLeft( node* _root ){  return getNode( _root, LEFT ); }
node* getRight( node* _root ){ return getNode( _root, RIGHT ); }