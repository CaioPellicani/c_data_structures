#include "linked_list.h"

#define MSG_NO_MEM "Not sufficient memory!\n"
#define MSG_NODEF "List is not defined!\n"
#define MSG_EMPTY "The List is Empty!\n"
#define MGS_OUT_RANGE(TYPE) "\n\nNot possible to %s. Position '%d' is out ouf range.\n", TYPE, position + 1 

typedef struct node {
    void * data;
    struct node* nextNode;
}node;

typedef struct strLinkedList{
    node * head;
    int size;
}linkedList;

bool validList( linkedList* _list, bool _seeIfEmpty );
bool insertInBetween( linkedList* _list, node* _prevNode, void* _data );
node* newBlankNode();
node* getNodeAt( linkedList* _list, int position, char* from );
bool removeNextNode( linkedList* _list, node* _prevNode );

linkedList* initList(){
    linkedList* newList;
    newList = ( linkedList* ) malloc( sizeof( linkedList ) );
    if( newList == NULL ){
        die( MSG_NO_MEM ); 
        return false;
    }
    else{
        newList->head = NULL;
        newList->size = 0;
        return newList;
    }
}

int getListSize( linkedList* _list ){
    return _list->size;
}

bool isEmpty( linkedList* _list ){
    return ( _list->head == NULL );
}

node* newBlankNode(){
    node* newNode;
    newNode = malloc( sizeof( node ) );
    newNode->data = NULL;
    newNode->nextNode = NULL;
    return newNode;
}

bool validList( linkedList* _list, bool _seeIfEmpty ){
    if( _list == NULL ){
        die( MSG_NODEF );
    }
    if( ( _seeIfEmpty ) && ( isEmpty( _list ) ) ){
        die( MSG_EMPTY );
    }

    return true;
}

node* getNodeAt( linkedList* _list, int position, char* from ){
    int limitMax = _list->size - 1;
    int limitMin = -1;
    
    if( strcmp( "insert", from ) == 0 ){
        limitMax = _list->size;
    }

    if( ( position > limitMax ) || ( position < limitMin ) ){
        die( MGS_OUT_RANGE( from ) );
        exit(1);
    }
    else if( position < 0 ){
        return NULL;
    }
    node* seeingNode;
    seeingNode = _list->head;
    for( int i = 0; i < position; i++ ){
        seeingNode = seeingNode->nextNode;
    }
    return seeingNode;
}

bool insertInBetween( linkedList* _list, node* _prevNode, void* _data ){
    node* newNode = newBlankNode();
    newNode->data = _data;

    if( isEmpty( _list ) ){ 
        _list->head = newNode;
    }
    else if( _prevNode == NULL ){ //PushHead
        newNode->nextNode = _list->head;
        _list->head = newNode;
    }
    else{
        newNode->nextNode = _prevNode->nextNode;
        _prevNode->nextNode = newNode;
    }
    _list->size++;
    return true;
}


bool removeNextNode( linkedList* _list, node* _prevNode ){
    node* deadNode;

    if( _prevNode == NULL ){ //PopHead
        deadNode = _list->head;
        _list->head = deadNode->nextNode;
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

    free( deadNode->data );
    free( deadNode );
    _list->size--;
    return true;  
}

bool pushHead( linkedList* _list, void* _data ){  
   if( validList( _list, false ) ){
       return insertAt( _list, _data, 0 );
   } 
   return false;
}

bool pushTail( linkedList* _list, void* _data ){  
   if( validList( _list, false ) ){
       return insertAt( _list, _data, _list->size - 1 );
   } 
   return false;
}

bool insertAt( linkedList* _list, void* _data, int position ){
    int prevNodePostion = position - 1;
    if( validList( _list, false ) ){
        return insertInBetween( _list, getNodeAt( _list, prevNodePostion, "insert" ), _data );
    }
    return false;
}

bool removeAt( linkedList* _list, int position ){
    int prevNodePostion = position - 1;
    if( validList( _list, false ) ){
        return removeNextNode( _list, getNodeAt( _list, prevNodePostion, "remove" ) );
    }
    return false;
}

bool popHead( linkedList* _list ){
    if( validList( _list, true ) ){
        return removeAt( _list, 0 );
    }  
    return false; 
}

bool popTail( linkedList* _list ){
    if( validList( _list, true ) ){
        return removeAt( _list, _list->size - 1 );
    }  
    return false;  
}

void emptyList( linkedList* _list ){
    while( _list->head != NULL ){
        popHead( _list );  
    }
}

void* getDataAt( linkedList* _list, int position ){
    int prevNodePostion = position;
    node* result = getNodeAt( _list, prevNodePostion, "get data" );

    if ( result == NULL ){
        return _list->head->data;
    }
    else{
        return result->data;
    }

}

void* getHeadData( linkedList* _list ){
    return getDataAt( _list, 0 );
}
void* getTailData( linkedList* _list ){
    return getDataAt( _list, _list->size - 1 );
}

bool listDataUse( linkedList* _list, void ( *dataUseFunction ) ( void* data )  ){
    node* seeingNode;

    if( validList( _list, true ) ){
        seeingNode = _list->head;
        while ( seeingNode != NULL ){
            dataUseFunction( seeingNode->data );
            seeingNode = seeingNode->nextNode;
        }
        return true;
    }
    return false;
}

void deleteList( linkedList* _list ){
    emptyList( _list );
    free( _list );
}


