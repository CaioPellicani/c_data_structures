#include "core_tri_cardinal.h"

void _tNodeDataUse( tNode* _mainRoot, dataUseFunction _orderFunc[] );
void _nullFunc( void* nullPointer ){ return; }

typedef struct{
    tNode** self;
    tNode** root;
    tNode** brother;
}positions;

tNode* newBlankTNode( tNode* _root ){
    tNode* newNode;
    newNode = malloc( sizeof( tNode ) );
    assert( newNode != NULL );

    newNode->data = NULL;
    newNode->root = _root;
    newNode->left = newNode->right = NULL;
    return newNode;
}

tNode** positioning( tNode* _root, int where ){
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
        break;
    default: 
        return NULL;
    }  
}

bool insertNewTNode( tNode** _root, int _where, void* _data ){
    
    tNode *newNode = newBlankTNode( *_root );
    assert( newNode != NULL );
    newNode->data = _data;
    
    if( insertTNode( _root, _where, &newNode ) ){
 //                                                         static int cont = 0;
 //                                                         printf( "root - %p\n", newNode->root );
 //                                                         printf( "%d - %p\n\n", cont++, newNode );
        return true;
    }

    free( newNode );
    return false;
}

bool insertTNode( tNode** _root, int _where, tNode** _thisNode ){
    if( _where == ROOT ){
        *_root = *_thisNode;
        return true;
    }

    tNode **position = NULL;
    position = positioning( *_root, _where );
    if( *position == NULL ){
        *position = *_thisNode;
        ( *_thisNode )->root = *_root;
        return true;
    }
    return false;
}

tNode* removeTNode_b( tNode** root, tNode** _deadNode ){
    tNode *leftOverSubTree = *_deadNode;

    if( leftOverSubTree->root != NULL ){
        if( leftOverSubTree->root->left == *_deadNode ){
            leftOverSubTree->root->left = NULL;
        }
        else{
            leftOverSubTree->root->right = NULL;
        }
        leftOverSubTree->root = NULL;
    }
    else{
        *root = NULL;
    }

    free( leftOverSubTree->data );
    leftOverSubTree->data = NULL;
    return leftOverSubTree;
}

tNode* removeTNode( tNode** _root, int _where ){
    tNode **position = NULL;
    tNode *leftOverSubTree = NULL;

    if( _where == ROOT ){
        leftOverSubTree = *_root;
        *_root = NULL;
        free( leftOverSubTree->data );
        return leftOverSubTree;
    }

    position = positioning( *_root, _where );
    if( *position != NULL ){
        leftOverSubTree = *position;
        *_root = NULL;
        free( leftOverSubTree->data );
        leftOverSubTree->data = NULL;
        return leftOverSubTree;
    }
    return leftOverSubTree;
}

void tNodeDataUse( tNode* _mainRoot, dataUseFunction dataUseFunc, int type ){
    assert( _mainRoot != NULL );
    dataUseFunction orderFunc[3] = { &_nullFunc,  &_nullFunc,  &_nullFunc };
    orderFunc[type] = dataUseFunc;

    _tNodeDataUse( _mainRoot, orderFunc );
}

void _tNodeDataUse( tNode* _mainRoot, dataUseFunction _orderFunc[] ){
    _orderFunc[INORDER]( _mainRoot->data );
    
    if( _mainRoot->left != NULL ){
       _tNodeDataUse( _mainRoot->left, _orderFunc );
    }

    _orderFunc[PREORDER]( _mainRoot->data );

    if( _mainRoot->right != NULL ){
        _tNodeDataUse( _mainRoot->right, _orderFunc );
    }

    _orderFunc[POSTORDER]( _mainRoot->data );
}


