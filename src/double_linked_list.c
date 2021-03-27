#include "double_linked_list.h"

bool validList( list* _list, bool _seeIfEmpty );
bool insertInFontOf( list* _list, node* _thisNode, void* data );
node* getNodeAt( list* _list, int pos );
bool removeNode( list* _list, node* _thisNode );

list* initList(){
    list* newList;
    newList = (list*) malloc( sizeof( list ) );
    if( newList == NULL ){
        die( MSG_NO_MEM ); 
        return NULL;   
    }
    else{
        newList->head = NULL;
        newList->tail = NULL;
        newList->size = 0;
        return newList;
    }
}

bool isEmpty( list* _list ){
    return ( _list->head == NULL ) && ( _list->tail == NULL );
}

bool validList( list* _list, bool _seeIfEmpty ){
    if( _list == NULL ){
        die( MSG_NODEF_LIST );
        return false;
    }
    if( ( _seeIfEmpty ) && ( isEmpty( _list ) ) ){
        die( MSG_EMPTY_LIST );
        return false;
    }

    return true;
}

bool insertInFontOf( list* _list, node* _thisNode, void* _data ){
    node* newNode;
    newNode = malloc( sizeof( node ) );
    newNode->data = _data;
    newNode->prevNode = newNode->nextNode = NULL;

    if( isEmpty( _list ) ){ 
        _list->head = _list->tail = newNode;
    }
    else if( ( _thisNode == NULL ) ){ //PushTail
        newNode->prevNode = _list->tail;
        _list->tail->nextNode = newNode;
        _list->tail = newNode;
    }
    else if( ( _list->head == NULL ) || ( _thisNode->prevNode == NULL) ){ //PushHead
        if( _list->head != NULL ){
            newNode->nextNode = _list->head;
            _list->head->prevNode = newNode;
            _list->head = newNode;
        }
        _list->head = newNode;
    }
    else{
        newNode->nextNode = _thisNode;
        newNode->prevNode = _thisNode->prevNode;
        newNode->prevNode->nextNode = newNode;
        newNode->nextNode->prevNode = newNode;
    }
    _list->size++;
    return true;
}

bool pushHead( list* _list, void* _data ){  
   if( validList( _list, false ) ){
       return insertInFontOf( _list, _list->head, _data );
   } 
   return false;
}

bool pushTail( list* _list, void* _data ){
    if( validList( _list, false ) ){
        return insertInFontOf( _list, NULL, _data );
    }
    return false;
}

bool insertAt( list* _list, void* _data, int pos ){
    if( validList( _list, false ) ){
        if( pos > _list->size ){
            die( MGS_OUT_RANGE("'insert'") );
            exit(1);
        }
        else{
            return insertInFontOf( _list, getNodeAt( _list, pos ), _data );
        }
    }
    return false;
}

bool removeNode( list* _list, node* _thisNode ){
    if( _list->head == _list->tail ){
        _list->head = _list->tail = NULL;
    }
    else if( _thisNode == _list->head ){
        _list->head = _thisNode->nextNode;
        _list->head->prevNode = NULL;
    }
    else if( _thisNode == _list->tail ){
        _list->tail = _thisNode->prevNode;
        _list->tail->nextNode = NULL;
    }
    else{
        _thisNode->nextNode->prevNode = _thisNode->prevNode;
        _thisNode->prevNode->nextNode = _thisNode->nextNode;
    }

    free( _thisNode->data );
    free( _thisNode );
    _list->size--;
    return true;  
}

bool removeAt( list* _list, int pos ){
    if( validList( _list, false ) ){
        if( pos > _list->size ){
            die( MGS_OUT_RANGE( "'remove'"));
            exit(1);
        }
        if( pos == _list->size ){
            return popTail( _list );
        }
        else{
            return removeNode( _list, getNodeAt( _list, pos ) );
        }
    }
    return false;
}

bool popHead( list* _list ){
    if( validList( _list, true ) ){
        return removeNode( _list, _list->head );
    }  
    return false; 

}
bool popTail( list* _list ){
    if( validList( _list, true ) ){
        return removeNode( _list, _list->tail );
    }   
    return false;
}

void emptyList( list* _list ){
    while( _list->head != NULL ){
        popTail( _list );  
    }
}

node* getNodeAt( list* _list, int pos ){
    if( pos > _list->size ){
        die( MGS_OUT_RANGE( "'getData'" ) );
        exit(1);
    }
    else if( pos == _list->size ){
        return NULL;
    }
    node* seeingNode;
    if( pos <= _list->size/2 ){
        seeingNode = _list->head;
        for( int i = 0; i < pos; i++ ){
            seeingNode = seeingNode->nextNode;
        }
    }
    else{
        seeingNode = _list->tail;
        for( int i = _list->size - 1; i > pos; i-- ){
            seeingNode = seeingNode->prevNode;
        }
    }

    return seeingNode;
}

void* getDataAt( list* _list, int pos ){
    return getNodeAt( _list, pos )->data;

}

bool showList( list* _list, void (*showData) ( void* data )  ){
    node* seeingNode;

    if( validList( _list, true ) ){
        seeingNode = _list->head;
        while ( seeingNode != NULL ){
            showData( seeingNode->data );
            seeingNode = seeingNode->nextNode;
        }
        return true;
    }
    return false;
}

void deleteList( list* _list ){
    emptyList( _list );
    free( _list );
    _list = NULL;
}


