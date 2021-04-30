#include "binary_search_tree.h"
#include "../core/src/core_tri_cardinal.h"

typedef int( *comparisonFunction )( void *larger, void *smaller );

typedef struct strBinarySearchTree{
    tNode * mainRoot;
    int size;
    comparisonFunction comparison;
}binarySearchTree;

typedef struct coordinatesToInsert{
    tNode** root;
    int position;
}coordinatesToInsert;

bool _bstInsertMainRoot( binarySearchTree* _tree, void* data );
tNode* _bstRemoveMainRoot( binarySearchTree* _tree );
tNode* _bstSearchTNode( binarySearchTree* _tree, void *_searchData );

binarySearchTree* bstInit( comparisonFunction _comparison ){
    binarySearchTree* newTree;
    newTree = ( binarySearchTree* ) malloc( sizeof( binarySearchTree ) );
    assert( newTree != NULL );

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
    return _tree->mainRoot == NULL;
}

bool _bstInsertMainRoot( binarySearchTree* _tree, void* _data ){
    return insertNewTNode( &_tree->mainRoot, ROOT, _data );
}

tNode* _bstRemoveMainRoot( binarySearchTree* _tree ){
    return removeTNode( &_tree->mainRoot, ROOT );
}

coordinatesToInsert* _bstGetCoordinatesToInsert( coordinatesToInsert* result, binarySearchTree*_tree, void* _data ){
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
    return result;
}

bool bstInsert( binarySearchTree*_tree, void* _data ){
    bool result = false;
    coordinatesToInsert* coords = malloc( sizeof( coordinatesToInsert ) );
    coords = _bstGetCoordinatesToInsert( coords, _tree, _data );

    if( insertNewTNode( coords->root, coords->position, _data ) ){
        result = true;
    }
    free( coords );
    return result;
}

bool _btsRealocate( binarySearchTree* _tree, tNode* _thisNode ){
    bool result = false;
    coordinatesToInsert* coords = malloc( sizeof( coordinatesToInsert ) );
    coords = _bstGetCoordinatesToInsert( coords, _tree, _thisNode->data );

    if( insertTNode( coords->root, coords->position, &_thisNode ) ){
        result = true;
    }
    free( coords );
    return result;  
}

bool bstRemove( binarySearchTree* _tree, void* _searchData ){
    assert( ! bstIsEmpty( _tree ) );
    tNode *deadNode = _bstSearchTNode( _tree, _searchData );
    if( deadNode == NULL ){
        return false;
    }

    tNode *leftOverSubTree = NULL;

    leftOverSubTree = removeTNode_b( &_tree->mainRoot, &deadNode );

    if( leftOverSubTree->right != NULL ){
        _btsRealocate( _tree, leftOverSubTree->right );
        leftOverSubTree->right = NULL;
    }
 
    if( leftOverSubTree->left != NULL ){
        _btsRealocate( _tree, leftOverSubTree->left );
        leftOverSubTree->left = NULL;
    }

    free( leftOverSubTree );
    return true;

}

bool bstEmptyTree( binarySearchTree*_tree ){
    if( ! bstIsEmpty( _tree ) ){
        free( _bstRemoveMainRoot( _tree ) );
    }
    return true;
}

void bstInorderDataUse( binarySearchTree* _tree, dataUseFunction dataUseFunc ){
    tNodeDataUse( _tree->mainRoot, dataUseFunc, INORDER );
}
void bstPreorderDataUse( binarySearchTree* _tree, void ( *dataUseFunc ) ( void* data )  ){
    tNodeDataUse( _tree->mainRoot, dataUseFunc, PREORDER );
}
void bstPostorderDataUse( binarySearchTree* _tree, void ( *dataUseFunc ) ( void* data )  ){
    tNodeDataUse( _tree->mainRoot, dataUseFunc, POSTORDER );
}

tNode* _bstSearchTNode( binarySearchTree* _tree, void *_searchData ){
    tNode* seeingNode = _tree->mainRoot;
    
    while ( ( seeingNode->left != NULL ) || ( seeingNode->right != NULL ) ){

        if( _tree->comparison( _searchData, seeingNode->data ) == SMALLER && puts( "\tL ") ){
            seeingNode = seeingNode->left;
        }
        if( _tree->comparison( _searchData, seeingNode->data ) == LARGER && puts( "\tR ") ){
            seeingNode = seeingNode->right;
        }
        if( _tree->comparison( _searchData, seeingNode->data ) == EQUAL && puts( "\tE ")){
            return seeingNode;
        }
    }
    return NULL;
}

void* bstSearch( binarySearchTree* _tree, void *_seachData ){
    tNode* searchNode = _bstSearchTNode( _tree, _seachData );
    if( searchNode != NULL ){
        return searchNode->data;
    }
    return NULL;
}