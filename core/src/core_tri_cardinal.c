#include "core_tri_cardinal.h"

void _nullFunc( void* nullPointer );
tNode* _newBlankTNode( tNode* _root );
bool _tNodeDataUse( tNode* _mainRoot, dataUseFunction _orderFunc[] );
tNode** _positioning( coordinates *_coords  );

/*  -   EXTERNAL FUNCTIONS  -   */

bool isLeaf( tNode *_thisNode ){
    return( ( _thisNode->left == NULL ) && ( _thisNode->right == NULL ) );
}

bool insertNewTNode( coordinates *_coords, void* _data ){
    tNode *newNode = _newBlankTNode( *_coords->root );
    assert( newNode != NULL );
    newNode->data = _data;
    
    if( insertTNode( _coords, &newNode ) ){
        return true;
    }

    free( newNode );
    return false;
}

bool insertTNode( coordinates *_coords, tNode** _thisNode ){
    if( _coords->position == ROOT ){
        *_coords->root = *_thisNode;
        return true;
    }

    tNode **position = NULL;
    position = _positioning( _coords );
    if( *position == NULL ){
        *position = *_thisNode;
        ( *_thisNode )->root = *_coords->root;
        return true;
    }
    return false;
}
coordinates *allocCoordinates(){
    coordinates *result = calloc( 0, sizeof( coordinates ) );
    assert( result != NULL );
    assert( ( result->root == NULL ) && ( result->position == 0 ) );
    return result;
}

leftOver *allocLeftOver(){
    leftOver *result = calloc( 0, sizeof( leftOver ) );
    assert( result != NULL );
    assert( ( result->right == NULL) && ( result->left == NULL ) );
    return result;
}

leftOver* removeTNode_c( tNode** root, tNode** _deadNode ){
    return NULL;
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

tNode* removeTNode( coordinates *_coords ){
    tNode **position = NULL;
    tNode *leftOverSubTree = NULL;
    coordinates* coords = allocCoordinates();

    if( coords->position == ROOT ){
        leftOverSubTree = *coords->root;
        *coords->root = NULL;
        free( leftOverSubTree->data );
        return leftOverSubTree;
    }

    position = _positioning( coords );
    if( *position != NULL ){
        leftOverSubTree = *position;
        *coords->root = NULL;
        free( leftOverSubTree->data );
        leftOverSubTree->data = NULL;
        return leftOverSubTree;
    }
    return leftOverSubTree;
}

bool tNodeDataUse( tNode* _mainRoot, dataUseFunction dataUseFunc, int type ){
    assert( _mainRoot != NULL );
    dataUseFunction orderFunc[3] = { &_nullFunc,  &_nullFunc,  &_nullFunc };
    orderFunc[type] = dataUseFunc;

    return _tNodeDataUse( _mainRoot, orderFunc );
}

/*  -   INTERNAL FUNCTIONS  -   */

void _nullFunc( void* nullPointer ){ return; }

tNode* _newBlankTNode( tNode* _root ){
    tNode* newNode;
    newNode = malloc( sizeof( tNode ) );
    assert( newNode != NULL );

    newNode->data = NULL;
    newNode->root = _root;
    newNode->left = newNode->right = NULL;
    return newNode;
}

bool _tNodeDataUse( tNode* _mainRoot, dataUseFunction _orderFunc[] ){
    _orderFunc[INORDER]( _mainRoot->data );
    
    if( _mainRoot->left != NULL ){
       _tNodeDataUse( _mainRoot->left, _orderFunc );
    }

    _orderFunc[PREORDER]( _mainRoot->data );

    if( _mainRoot->right != NULL ){
        _tNodeDataUse( _mainRoot->right, _orderFunc );
    }

    _orderFunc[POSTORDER]( _mainRoot->data );
    return true;
}

tNode** _positioning( coordinates *_coords ){
    tNode* _root = *_coords->root;
    
    switch ( _coords->position  ){
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

