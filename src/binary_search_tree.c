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
coordinates* _bstGetCoordinates( coordinates* result, binarySearchTree*_tree, void* _data );

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
    coords = _bstGetCoordinates( coords, _tree, _data );

    if( insertNewTNode( coords, _data ) ){
        result = true;
    }
    free( coords );
    return result;
}

bool bstRemove( binarySearchTree* _tree, void* _searchData ){
    BOOL_EMPTY_BST( _tree );
    bool result = false;
    leftOver *treeLeftOver = allocLeftOver();
    coordinates * coords = allocCoordinates();
    
    coords = _bstGetCoordinates( coords, _tree, _searchData );

    if( removeTNode( coords, NULL ) ){
        result = true;
    }

    printf( "\n\nl -> %p\nr -> %p\n\n", treeLeftOver->left, treeLeftOver->right );
    free( coords );
    free( treeLeftOver );
    return result;
}

bool bstEmptyTree( binarySearchTree*_tree ){
    if( ! bstIsEmpty( _tree ) ){
        bstRemove( _tree, _tree->mainRoot->data );
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

void* bstSearch( binarySearchTree* _tree, void *_seachData ){
    NULL_EMPTY_DLL( _tree );
    tNode* searchNode = _bstSearchTNode( _tree, _seachData );
    if( searchNode != NULL ){
        return searchNode->data;
    }
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

tNode* _bstSearchTNode( binarySearchTree* _tree, void *_searchData ){
    assert( ! bstIsEmpty( _tree ) );
    tNode* seeingNode = _tree->mainRoot;
    
    while ( !isLeaf( seeingNode ) ){            
        if( _tree->comparison( _searchData, seeingNode->data ) == SMALLER ){
            seeingNode = seeingNode->left;
        }
        if( _tree->comparison( _searchData, seeingNode->data ) == LARGER ){
            seeingNode = seeingNode->right;
        }
        if( _tree->comparison( _searchData, seeingNode->data ) == EQUAL ){
            return seeingNode;
        }
    }
    return NULL;
}

tNode *_getLimits( binarySearchTree *_tree, int direction ){
    assert( ! bstIsEmpty( _tree ) );
    assert( ( direction == LEFT) || ( direction == RIGHT ) );
    tNode *seeingNode = _tree->mainRoot;    

    if( direction == LEFT ){
        while ( seeingNode->left != NULL ){
            seeingNode = seeingNode->left;
        }
        if( isLeaf( seeingNode ) ){
            return seeingNode;
        }
        return seeingNode->right;
    }

    if( direction == RIGHT ){
        while ( seeingNode->right != NULL ){
            seeingNode = seeingNode->right;
        }
        if( isLeaf( seeingNode ) ){
            return seeingNode;
        }
        return seeingNode->left;
    }
    return NULL;
}

coordinates* _bstGetCoordinates( coordinates* result, binarySearchTree*_tree, void* _data ){
    result->root = &_tree->mainRoot;
    result->position = ROOT;

    if( bstIsEmpty( _tree ) || ( _tree->comparison( _data, ( *result->root )->data ) == EQUAL ) ){
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
    return result;
}