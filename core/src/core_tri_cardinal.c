#include "core_tri_cardinal.h"

void _nullFunc( void* nullPointer );
tNode* _newBlankTNode( tNode* _root );
bool _tNodeDataUse( tNode* _mainRoot, dataUseFunction _orderFunc[] );
tNode** _positioning( coordinates *_coords  );
void _disconnectFromRoot(  tNode** _mainRoot, tNode *_thisNode );

/*  -   EXTERNAL FUNCTIONS  -   */

bool isLeaf( tNode *_thisNode ){
    return( ( _thisNode->left == NULL ) && ( _thisNode->right == NULL ) );
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
    if( *position == NULL ){ //assert possition is vacancy of node
        *position = *_thisNode;
        ( *_thisNode )->root = *_coords->root;
        return true;
    }
    return false;
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
    assert( *_coords->root != NULL );
    tNode **result = NULL;
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
    }  
    printf( "\npostioning %p", result );
    return result;
}

