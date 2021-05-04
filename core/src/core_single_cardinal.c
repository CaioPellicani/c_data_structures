#include "core_single_cardinal.h"

node* newBlankNode(){
    node* newNode;
    newNode = malloc( sizeof( node ) );
    assert( newNode != NULL );

    newNode->data = NULL;
    newNode->nextNode = NULL;
    return newNode;
}

bool insertInBetween( node** firstNode, int* size, void* _data, node* _prevNode ){
    node* newNode = newBlankNode();
    newNode->data = _data;
    if( *firstNode == NULL ){ 
        *firstNode = newNode;
    }
    else if( _prevNode == NULL ){ //PushHead
        newNode->nextNode = *firstNode;
        *firstNode = newNode;
    }
    else{
        newNode->nextNode = _prevNode->nextNode;
        _prevNode->nextNode = newNode;
    }
    (*size)++;
    return true;
}

bool removeNextNode( node** firstNode, int* size, node* _prevNode ){
    node* deadNode;
    if( _prevNode == NULL ){ //PopHead
        deadNode = *firstNode;
        *firstNode = deadNode->nextNode;
    }
    else{
        deadNode = _prevNode->nextNode;
        if( deadNode->nextNode != NULL ){
            _prevNode->nextNode = deadNode->nextNode;
        }
        else{
            _prevNode->nextNode = NULL;
        }
    }
    (*size)--;
    free( deadNode->data );
    free( deadNode );
    deadNode = NULL;
    assert( deadNode == NULL );
    return true;  
}
node* getNodeAt( node* firstNode, int position, bool insert, int size ){
    int limitMax = size - 1;
    int limitMin = -1;
    
    if( insert ){
        limitMax = size;
    }

    if( ( position > limitMax ) || ( position < limitMin ) ){
        return NULL;
    }

    node* seeingNode;
    seeingNode = firstNode;
    for( int i = 0; i < position; i++ ){
        seeingNode = seeingNode->nextNode;
    }
    return seeingNode;
}


void* getNodeData( node* firstNode, int position, int size ){
    int prevNodePostion = position;

    if ( ( firstNode != NULL ) && ( position == -1 ) ){
        return firstNode->data;
    }
    node* result = getNodeAt( firstNode, prevNodePostion, false, size );
    if( result != NULL ){
        return result->data;
    }
    return NULL;
}

bool dataUse( node* firstNode,dataUseFunction dataUseFunc ){
    node* seeingNode;
    seeingNode = firstNode;
    while ( seeingNode != NULL ){
        dataUseFunc( seeingNode->data );
        seeingNode = seeingNode->nextNode;
    }
    return true;
}

