#ifndef _TREE_H
#define _TREE_H

#include "../core/src/stdHeader.h"

typedef struct strBinarySearchTree binarySearchTree;

binarySearchTree* bstInit( int( *comparisonFunction )( void *larger, void *smaller ) );
void bstDelete( binarySearchTree** _tree );

bool bstIsEmpty( binarySearchTree* _tree );

bool bstInsert( binarySearchTree*_tree, void* _data );
bool bstRemove( binarySearchTree*_tree, void* _searchData );

bool bstInorderDataUse( binarySearchTree* _tree, void ( *dataUseFunc ) ( void* data )  );
bool bstPreorderDataUse( binarySearchTree* _tree, void ( *dataUseFunc ) ( void* data )  );
bool bstPostorderDataUse( binarySearchTree* _tree, void ( *dataUseFunc ) ( void* data )  );
void* bstSearch( binarySearchTree* _tree, void *_searchData );

bool bstEmptyTree( binarySearchTree*_tree );

#endif
