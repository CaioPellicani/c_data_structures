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
    printf( "%d - ", aData->value );
}

int main( int argc, char **argv ){
    binaryTree *aTree;
    aTree = initBinaryTree();

    



    return 0;
}