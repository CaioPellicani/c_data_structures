#include "binary_search_tree.h"
#include "../core/src/core_tri_cardinal.h"

#define BOOL_VALID_BST( TREE ) if( ! _bstIsValid( TREE ) ){ return false; }
#define BOOL_EMPTY_BST( TREE ) if( bstIsEmpty( TREE ) ){ return false; }
#define NULL_EMPTY_DLL( TREE ) if( bstIsEmpty( TREE ) ){ return NULL; }

typedef int( *comparisonFunction )( void *larger, void *smaller );

typedef struct strBinarySearchTree{
    tNode * mainRoot;
    int size;
    comparisonFunction comparison;
}binarySearchTree;


bool _bstIsValid( binarySearchTree *_tree );
tNode* _bstSearchTNode( binarySearchTree* _tree, void *_searchData );
tNode *_getLimits( binarySearchTree *_tree, int direction );
coordinates* _bstGetInsertCoordinates( coordinates* coords, binarySearchTree*_tree, void* _data );
coordinates* _bstGetSearchCoordinates( coordinates* coords, binarySearchTree* _tree, void *_searchData );
bool _rellocateLeftOver( binarySearchTree* _tree, tNode** _oldRoot, leftOver* _treeLeftOver );
tNode* _test( binarySearchTree* _tree, coordinates* coords );

/*  -   EXTERNAL FUNCTIONS  -   */

binarySearchTree* bstInit( comparisonFunction _comparison ){
    binarySearchTree* newTree;
    newTree = ( binarySearchTree* ) malloc( sizeof( binarySearchTree ) );
    assert( _bstIsValid( newTree ) );
    newTree->size = 0;
    newTree->mainRoot = NULL;
    newTree->comparison = _comparison;
    return newTree;
}

void bstDelete( binarySearchTree** _tree ){
    bstEmptyTree( *_tree );
    free( *_tree );
    *_tree = NULL;
    assert( *_tree == NULL );
}

bool bstIsEmpty( binarySearchTree* _tree ){
    BOOL_VALID_BST( _tree );
    return _tree->mainRoot == NULL;
}

bool bstInsert( binarySearchTree*_tree, void* _data ){
    BOOL_VALID_BST( _tree );
    bool result = false;
    coordinates* coords = allocCoordinates();
    coords = _bstGetInsertCoordinates( coords, _tree, _data );

    if( insertNewTNode( coords, _data ) ){
        result = true;
    }
    free( coords );
    return result;
}

bool bstRemove( binarySearchTree* _tree, void* _searchData ){
    BOOL_EMPTY_BST( _tree );
    bool result = false;
    coordinates* coords = allocCoordinates();
    coords = _bstGetSearchCoordinates( coords, _tree, _searchData );

    tNode** firstNode = &_tree->mainRoot;    
    tNode** positionInRoot = NULL;
    tNode* deadNode = NULL;
    if( coords->root != NULL ){
        tNode* seeingNode = NULL;

        switch ( coords->position ) { 
            case RIGHT : 
                deadNode = ( *coords->root )->right;
                positionInRoot = &( *coords->root )->right;
                break;

            case LEFT : 
                deadNode = ( *coords->root )->left;
                positionInRoot = &( *coords->root )->left;
                break;
            
            case ROOT : 
                deadNode = ( *coords->root );
                positionInRoot = firstNode;
                break;          
        }   
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
    }  

    if( deadNode != NULL ){
        free( deadNode->data );
        free( deadNode );
        result = true;
    }

    free( coords );
    return result;
}

bool bstEmptyTree( binarySearchTree*_tree ){
    void* deadNode = NULL;
    while( ! bstIsEmpty( _tree ) ){
        deadNode = bstGetBiggerData( _tree );
        bstRemove( _tree, deadNode );
    }
    return true;
}

bool bstInorderDataUse( binarySearchTree* _tree, dataUseFunction dataUseFunc ){
    BOOL_EMPTY_BST( _tree );
    return tNodeDataUse( _tree->mainRoot, dataUseFunc, INORDER );
}
bool bstPreorderDataUse( binarySearchTree* _tree, void ( *dataUseFunc ) ( void* data )  ){
    BOOL_EMPTY_BST( _tree );
    return tNodeDataUse( _tree->mainRoot, dataUseFunc, PREORDER );
}
bool bstPostorderDataUse( binarySearchTree* _tree, void ( *dataUseFunc ) ( void* data )  ){
    BOOL_EMPTY_BST( _tree );
    return tNodeDataUse( _tree->mainRoot, dataUseFunc, POSTORDER );
}

void* bstSearch( binarySearchTree* _tree, void* _searchData ){
    NULL_EMPTY_DLL( _tree );
    coordinates* coords = allocCoordinates();
    coords = _bstGetSearchCoordinates( coords, _tree, _searchData );

    if( coords->root != NULL ){
        void* lookUpTable[3];
        lookUpTable[ROOT] = ( *coords->root )->data;
        lookUpTable[RIGHT] = ( *coords->root )->right->data;
        lookUpTable[LEFT] = ( *coords->root )->left->data;

        return lookUpTable[ coords->position ]; 
    }
    free( coords );
    return NULL;
}

void* bstGetLowerData( binarySearchTree *_tree ){
    NULL_EMPTY_DLL( _tree );
    return _getLimits( _tree, LEFT )->data;
}

void* bstGetBiggerData( binarySearchTree *_tree ){
    NULL_EMPTY_DLL( _tree );
    return _getLimits( _tree, RIGHT )->data;
}

/*  -   INTERNAL FUNCTIONS  -   */

bool _bstIsValid( binarySearchTree *_tree ){
    return ( _tree != NULL );
}

tNode *_getLimits( binarySearchTree *_tree, int direction ){
    assert( ! bstIsEmpty( _tree ) );
    assert( ( direction == LEFT) || ( direction == RIGHT ) );
   
    if( isLeaf( _tree->mainRoot ) ){
        return _tree->mainRoot;
    }

    tNode *seeingNode = _tree->mainRoot; 

    if( direction == LEFT ){
        while ( seeingNode->left != NULL ){
            seeingNode = seeingNode->left;
        }
        return seeingNode;
    }

    if( direction == RIGHT ){
        while ( seeingNode->right != NULL ){
            seeingNode = seeingNode->right;
        }
        return seeingNode;

    }
    return NULL;
}

coordinates* _bstGetSearchCoordinates( coordinates* coords, binarySearchTree* _tree, void *_searchData ){
    assert( ! bstIsEmpty( _tree ) );

    coordinates* result = coords;
    result->root = NULL;
    result->position = ROOT;
    tNode* seeingNode = _tree->mainRoot;

    if( _tree->comparison( _searchData, seeingNode->data ) == EQUAL ){
        result->root = &_tree->mainRoot;
        result->position = ROOT;
        return result;
    }

    while ( !isLeaf( seeingNode ) ){            
        if( _tree->comparison( _searchData, seeingNode->data ) == SMALLER ){
            if( seeingNode->right == NULL ){ break; }
            if( _tree->comparison( _searchData, seeingNode->left->data ) == EQUAL ){
                result->root = &seeingNode;
                result->position = LEFT;
                break;
            } else{
                seeingNode = seeingNode->left;
            }
        }

        if( _tree->comparison( _searchData, seeingNode->data ) == LARGER ){
            if( seeingNode->right == NULL ){ break; }
            if( ( _tree->comparison( _searchData, seeingNode->right->data ) ) == EQUAL ){
               result->root = &seeingNode;
               result->position = RIGHT;
               break;
            } else{
                seeingNode = seeingNode->right;
            }
        }
    }
    
    return result;
}

coordinates* _bstGetInsertCoordinates( coordinates* coords, binarySearchTree*_tree, void* _data ){
    coordinates *result = coords;

    result->root = &_tree->mainRoot;
    result->position = ROOT;

    if( bstIsEmpty( _tree ) ){
        return result;
    }

    while( true ){
        if( _tree->comparison( _data, ( *result->root )->data ) == SMALLER ){
            if( ( *result->root )->left == NULL ){
                result->position = LEFT;
                break;            
            }
            result->root = &( *result->root )->left;
        }
        if( ( _tree->comparison( _data, ( *result->root )->data ) == LARGER ) ||
            ( _tree->comparison( _data, ( *result->root )->data ) == EQUAL ) ){
            if( ( *result->root )->right == NULL ){
                result->position = RIGHT;
                break;            
            }
            result->root = &( *result->root )->right;
        }
    }
    assert( result->root != NULL );
    return result;
}

