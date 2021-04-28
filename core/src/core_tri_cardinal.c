#include "core_tri_cardinal.h"

void _tNodeDataUse( tNode* _mainRoot, dataUseFunction _orderFunc[] );
void _nullFunc( void* nullPointer ){ return; }

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

bool insertTNode( tNode** _root, int _where, void* _data ){
    tNode **position = NULL;
    tNode *newNode = newBlankTNode( *_root );

    newNode->data = _data;

    if( _where == ROOT ){
        *_root = newNode;
        return true;
    }

    position = positioning( *_root, _where );
    if( *position == NULL ){
        *position = newNode;
        newNode->root = *position;
        return true;
    }

    free( newNode );
    return false;
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


