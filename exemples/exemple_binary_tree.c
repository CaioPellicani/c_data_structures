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

    aTree->mainRoot->data = (data*)newData( 0 );
    addLeftNode( aTree->mainRoot, (data*)newData( 1 ) );
    addRightNode( aTree->mainRoot, (data*)newData( 2 ) );
    addLeftNode( aTree->mainRoot->left, (data*)newData( 3 ));
    addRightNode( aTree->mainRoot->left, (data*)newData( 4 ));
    addLeftNode( aTree->mainRoot->right, (data*)newData( 5 ));
    addRightNode( aTree->mainRoot->right, (data*)newData( 6 ));

    printf( "|Root -> " );
    showData( (data*)aTree->mainRoot->data );

    printf( "\t|Left-> " );
    showData( (data*)getLeft( aTree->mainRoot )->data );  
    printf( "\t\t|Left-> " );
    showData( (data*)getLeft( aTree->mainRoot->left )->data ); 
    printf( "\t\t|Right-> " );
    showData( (data*)getRight( aTree->mainRoot->left )->data ); 

    printf( "\t|Right-> " );
    showData( (data*)getRight( aTree->mainRoot )->data );   
    printf( "\t\t|Left-> " );
    showData( (data*)getLeft( aTree->mainRoot->right )->data ); 
    printf( "\t\t|Right-> " );
    showData( (data*)getRight( aTree->mainRoot->right )->data ); 

    return 0;
}