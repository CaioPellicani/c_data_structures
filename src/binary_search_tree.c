#include "binary_search_tree.h"
#include "../core/src/core_tri_cardinal.h"

typedef int( *comparisonFunction )( void *larger, void *smaller );

typedef struct strBinarySearchTree{
    tNode * mainRoot;
    int size;
    comparisonFunction comparison;
}binarySearchTree;

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
    return insertTNode( &_tree->mainRoot, ROOT, _data );
}

tNode* _bstRemoveMainRoot( binarySearchTree* _tree ){
    return removeTNode( &_tree->mainRoot, ROOT );
}

bool bstInsert( binarySearchTree*_tree, void* _data ){
    tNode* seeingNode = NULL;
    int position = ROOT;

    if( bstIsEmpty( _tree ) ){
        return insertTNode( &_tree->mainRoot, position, _data );
    }
    seeingNode = _tree->mainRoot;
    while( true ){
        if( _tree->comparison( _data, seeingNode->data ) == SMALLER ){
            if( seeingNode->left == NULL ){
                position = LEFT;
                break;            
            }
            seeingNode = seeingNode->left;
        }
        if( ( _tree->comparison( _data, seeingNode->data ) == LARGER ) ||
            ( _tree->comparison( _data, seeingNode->data ) == EQUAL ) ){
            if( seeingNode->right == NULL ){
                position = RIGHT;
                break;            
            }
            seeingNode = seeingNode->right;
        }
    }
    return insertTNode( &seeingNode, position, _data );
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

void* bstSearch( binarySearchTree* _tree, void *_seachData ){
    tNode* searchNode = _bstSearchTNode( _tree, _seachData );
    if( searchNode != NULL ){
        return searchNode->data;
    }
    return NULL;
}