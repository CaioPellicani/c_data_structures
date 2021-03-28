#include "../src/stdHeader.h"
#include "../src/binary_tree.h"
    
typedef struct data{
    int value;
}data;

data* newData( int _value ){
    data* newData = ( data* ) malloc( sizeof( data ) );
    newData->value = _value;
    return newData;
}

void showData( void* _data ){
    data* aData = ( data* )_data;
    printf( "%d\n", aData->value );
}

int main( int argc, char **argv ){
    binaryTree *aTree;
    aTree = initBinaryTree();
    node* root = aTree->mainRoot;

    root->data = (data*)newData( 0 );
    addLeftNode( root, (data*)newData( 1 ) );
    addRightNode( root, (data*)newData( 2 ) );
    addLeftNode( root->left, (data*)newData( 3 ));
    addRightNode( root->left, (data*)newData( 4 ));
    addLeftNode( root->right, (data*)newData( 5 ));
    addRightNode( root->right, (data*)newData( 7 ));

    printf( "### SHOW TREE\n" );
    showTree( root, 0, 0, &showData );

    return 0;
}