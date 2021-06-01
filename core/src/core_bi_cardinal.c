#include "core_bi_cardinal.h"

bNode* _newBlankBNode();

/*  -   EXTERNAL FUNCTIONS  -   */

bool insertInFontOf( bNode** _firstNode, bNode** _lastNode, int* _size, bNode* _thisNode, void* _data ){
    bNode* newNode = _newBlankBNode();

    newNode->data = _data;

    if( *_firstNode == NULL ){ 
        *_firstNode = *_lastNode = newNode;
    }
    else if( ( _thisNode == NULL ) ){ //PushTail
        newNode->prevNode = ( *_lastNode );
        ( *_lastNode )->nextNode = newNode;
        *_lastNode = newNode;
    }
    else if( ( *_firstNode == NULL ) || ( _thisNode->prevNode == NULL) ){ //PushHead
        if( *_firstNode != NULL ){
            newNode->nextNode = *_firstNode;
            ( *_firstNode )->prevNode = newNode;
            *_firstNode = newNode;
        }
        *_firstNode = newNode;
    }
    else{
        newNode->nextNode = _thisNode;
        newNode->prevNode = _thisNode->prevNode;
        newNode->prevNode->nextNode = newNode;
        newNode->nextNode->prevNode = newNode;
    }
    ( *_size )++;
    return true;
}

bool removeBNode( bNode** _firstNode, bNode** _lastNode, int* _size, bNode* _thisNode ){
    assert( _thisNode != NULL );
    if( *_firstNode == *_lastNode ){
        *_firstNode = *_lastNode = NULL;
    }
    else if( _thisNode == *_firstNode ){
        *_firstNode = _thisNode->nextNode;
        ( *_firstNode )->prevNode = NULL;
    }
    else if( _thisNode == *_lastNode ){
        *_lastNode = _thisNode->prevNode;
        ( *_lastNode )->nextNode = NULL;
    }
    else{
        _thisNode->nextNode->prevNode = _thisNode->prevNode;
        _thisNode->prevNode->nextNode = _thisNode->nextNode;
    }

    free( _thisNode->data );
    free( _thisNode );
    ( *_size )--;
    return true;  
}

bNode* getBNodeAt( bNode** _firstNode, bNode** _lastNode, int* _size, int pos ){
    if( pos >= *_size ){
        return NULL;
    }
    bNode* seeingNode;
    if( pos <= ( *_size )/2 ){
        seeingNode = *_firstNode;
        for( int i = 0; i < pos; i++ ){
            seeingNode = seeingNode->nextNode;
        }
    }
    else{
        seeingNode = *_lastNode;
        for( int i = ( *_size ) - 1; i > pos; i-- ){
            seeingNode = seeingNode->prevNode;
        }
    }
    return seeingNode;
}

bool bNodeDataUse( bNode* _firstNode, dataUseFunction dataUseFunc  ){
    bNode* seeingNode;

    if( _firstNode != NULL ){
        seeingNode = _firstNode;
        while ( seeingNode != NULL ){
            dataUseFunc( seeingNode->data );
            seeingNode = seeingNode->nextNode;
        }
        return true;
    }
    return false;
}

/*  -   INTERNAL FUNCTIONS  -   */

bNode* _newBlankBNode(){
    bNode* newNode = malloc( sizeof( *newNode ) );
    assert( newNode != NULL );

    newNode->data = NULL;
    newNode->nextNode =NULL;
    newNode->prevNode = NULL;

    assert( newNode->data == NULL );
    assert( newNode->nextNode == NULL );
    assert( newNode->prevNode == NULL );
    return newNode;
}