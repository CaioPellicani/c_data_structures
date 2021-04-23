#include "double_linked_list.h"
#include "../core/src/core_b_cardinal.h"

typedef struct strList{
    bNode * head;
    bNode * tail;
    int size;
}doubleList;

bool _validList( doubleList* _list, bool _seeIfEmpty );

doubleList* _initList(){
    doubleList* newList = ( doubleList* ) malloc( sizeof( doubleList ) );
    assert( newList != NULL );
    newList->head = NULL;
    newList->tail = NULL;
    newList->size = 0;
    return newList;
}

int getDListSize( doubleList* _list ){
    return _list->size;
}

bool _isEmpty( doubleList* _list ){
    return ( _list->head == NULL ) && ( _list->tail == NULL );
}

bool _validList( doubleList* _list, bool _seeIfEmpty ){
    if( _list == NULL ){
        die( MSG_NODEF );
    }
    if( ( _seeIfEmpty ) && ( _isEmpty( _list ) ) ){
        die( MSG_EMPTY );
    }

    return true;
}

bool _insertInFontOf( doubleList* _list, bNode* _thisNode, void* _data ){
    return insertInFontOf( &_list->head, &_list->tail, &_list->size, _thisNode, _data );
}
bool _removeBNode( doubleList* _list, bNode* _thisNode ){
    return removeBNode( &_list->head, &_list->tail, &_list->size, _thisNode ); 
}

bNode* _getBNodeAt( doubleList* _list, int pos ){
    return getBNodeAt( &_list->head, &_list->tail, &_list->size, pos );
}

bool _pushHead( doubleList* _list, void* _data ){  
   if( _validList( _list, false ) ){
       return _insertInFontOf( _list, _list->head, _data );
   } 
   return false;
}

bool _pushTail( doubleList* _list, void* _data ){
    if( _validList( _list, false ) ){
        return _insertInFontOf( _list, NULL, _data );
    }
    return false;
}

bool _insertAt( doubleList* _list, void* _data, int pos ){
    if( _validList( _list, false ) ){
        if( pos > _list->size ){
            die( "'insert'" );
        }
        else{
            return _insertInFontOf( _list, _getBNodeAt( _list, pos ), _data );
        }
    }
    return false;
}

bool _removeAt( doubleList* _list, int pos ){
    if( _validList( _list, false ) ){
        if( pos > _list->size ){
            die( "'remove'" );
        }
        if( pos == _list->size ){
            return _popTail( _list );
        }
        else{
            return _removeBNode( _list, _getBNodeAt( _list, pos ) );
        }
    }
    return false;
}

bool _popHead( doubleList* _list ){
    if( _validList( _list, true ) ){
        return _removeBNode( _list, _list->head );
    }  
    return false; 

}
bool _popTail( doubleList* _list ){
    if( _validList( _list, true ) ){
        return _removeBNode( _list, _list->tail );
    }   
    return false;
}

void _emptyList( doubleList* _list ){
    while( _list->head != NULL ){
        _popTail( _list );  
    }
}

void* _getDataAt( doubleList* _list, int pos ){
    return _getBNodeAt( _list, pos )->data;

}

bool _showList( doubleList* _list, void (*showData) ( void* data )  ){
    bNode* seeingNode;

    if( _validList( _list, true ) ){
        seeingNode = _list->head;
        while ( seeingNode != NULL ){
            showData( seeingNode->data );
            seeingNode = seeingNode->nextNode;
        }
        return true;
    }
    return false;
}

void _deleteList( doubleList** _list ){
    _emptyList( *_list );
    free( *_list );
    *_list = NULL;
    assert( *_list == NULL );
}


