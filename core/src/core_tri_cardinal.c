#include "core_tri_cardinal.h"

void _nullFunc( void* nullPointer );
tNode* _newBlankTNode( tNode* _root );
bool _tNodeDataUse( tNode* _mainRoot, dataUseFunction _orderFunc[] );
tNode** _positioning( coordinates *_coords  );
tNode *_diconnectTNode( tNode** _mainRoot, coordinates *coords );


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

bool removeTNode( tNode** _mainRoot, coordinates *coords ){
    tNode* deadNode = _diconnectTNode( _mainRoot, coords );

    if( deadNode != NULL ){
        free( deadNode->data );
        free( deadNode );
        return true;
    }
    return false;
}

bool tNodeDataUse( tNode* _mainRoot, dataUseFunction dataUseFunc, int type ){
    assert( _mainRoot != NULL );
    dataUseFunction lookUpTable[3] = { &_nullFunc,  &_nullFunc,  &_nullFunc };
    lookUpTable[type] = dataUseFunc;

    return _tNodeDataUse( _mainRoot, lookUpTable );
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
    tNode* _root = *_coords->root;

    tNode **lookUpTable[3];
    lookUpTable[ROOT] = &_root->root;
    lookUpTable[LEFT] = &_root->left;
    lookUpTable[RIGHT] = &_root->right;
    
    return lookUpTable[ _coords->position ];
}

tNode *_diconnectTNode( tNode** firstNode, coordinates * coords ){
    tNode* deadNode = NULL;
    tNode** positionInRoot;

    enum { DEAD_NODE, ROOT_POS };    
    tNode** lookUpTable[2][3];
    int position = coords->position;

    if( coords->root != NULL ){
        lookUpTable[DEAD_NODE][RIGHT] = &( *coords->root )->right;
        lookUpTable[ROOT_POS][RIGHT] = &( *coords->root )->right;

        lookUpTable[DEAD_NODE][LEFT] = &( *coords->root )->left;
        lookUpTable[ROOT_POS][LEFT] = &( *coords->root )->left;

        lookUpTable[DEAD_NODE][ROOT] = &( *coords->root );
        lookUpTable[ROOT_POS][ROOT] = firstNode;

        deadNode = *( lookUpTable[DEAD_NODE][position] );
        positionInRoot = lookUpTable[ROOT_POS][position];
    }  

    if( deadNode != NULL ){
        tNode* seeingNode = NULL;
        if( ( deadNode->left == NULL ) && ( deadNode->right == NULL ) ){
            *positionInRoot = NULL;
        } 
        if( ( deadNode->right != NULL ) && (deadNode->left == NULL ) ){
            *positionInRoot = deadNode->right;
            deadNode->right->root = deadNode->root;
        }
        if( ( deadNode->left != NULL ) && (deadNode->right == NULL ) ){
            *positionInRoot = deadNode->left;
            deadNode->left->root = deadNode->root;
        }
        if( ( deadNode->right != NULL ) && (deadNode->left != NULL ) ){
            *positionInRoot= deadNode->right;
            deadNode->right->root = deadNode->root;
            seeingNode = deadNode->right;
            while( seeingNode->left != NULL ){
                seeingNode = seeingNode->left;
            }
            seeingNode->left = deadNode->left;
        }
        return deadNode;
    }
    return NULL;
}

