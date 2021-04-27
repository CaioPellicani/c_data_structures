#include "double_linked_list.h"
#include "../core/src/core_bi_cardinal.h"

typedef struct strList{
    bNode * head;
    bNode * tail;
    int size;
}doubleLinkedList;

bool dllValidList( doubleLinkedList* _list, bool _seeIfEmpty );

doubleLinkedList* dllInit(){
    doubleLinkedList* newList = ( doubleLinkedList* ) malloc( sizeof( doubleLinkedList ) );
    assert( newList != NULL );
    newList->head = NULL;
    newList->tail = NULL;
    newList->size = 0;
    return newList;
}

int dllGetSize( doubleLinkedList* _list ){
    return _list->size;
}

bool dllIsEmpty( doubleLinkedList* _list ){
    return ( _list->head == NULL ) && ( _list->tail == NULL );
}

bool dllValidList( doubleLinkedList* _list, bool _seeIfEmpty ){
    if( _list == NULL ){
        die( MSG_NODEF );
    }
    if( ( _seeIfEmpty ) && ( dllIsEmpty( _list ) ) ){
        die( MSG_EMPTY );
    }

    return true;
}

bool _dllInsertInFontOf( doubleLinkedList* _list, bNode* _thisNode, void* _data ){
    return insertInFontOf( &_list->head, &_list->tail, &_list->size, _thisNode, _data );
}
bool _dllRemoveBNode( doubleLinkedList* _list, bNode* _thisNode ){
    return removeBNode( &_list->head, &_list->tail, &_list->size, _thisNode ); 
}

bNode* _dllGetBNodeAt( doubleLinkedList* _list, int pos ){
    return getBNodeAt( &_list->head, &_list->tail, &_list->size, pos );
}

bool dllPushHead( doubleLinkedList* _list, void* _data ){  
   if( dllValidList( _list, false ) ){
       return _dllInsertInFontOf( _list, _list->head, _data );
   } 
   return false;
}

bool dllPushTail( doubleLinkedList* _list, void* _data ){
    if( dllValidList( _list, false ) ){
        return _dllInsertInFontOf( _list, NULL, _data );
    }
    return false;
}

bool dllInsertAt( doubleLinkedList* _list, void* _data, int pos ){
    if( dllValidList( _list, false ) ){
        if( pos > _list->size ){
            die( "'insert'" );
        }
        else{
            return _dllInsertInFontOf( _list, _dllGetBNodeAt( _list, pos ), _data );
        }
    }
    return false;
}

bool dllRemoveAt( doubleLinkedList* _list, int pos ){
    if( dllValidList( _list, false ) ){
        if( pos > _list->size ){
            die( "'remove'" );
        }
        if( pos == _list->size ){
            return dllPopTail( _list );
        }
        else{
            return _dllRemoveBNode( _list, _dllGetBNodeAt( _list, pos ) );
        }
    }
    return false;
}

bool dllPopHead( doubleLinkedList* _list ){
    if( dllValidList( _list, true ) ){
        return _dllRemoveBNode( _list, _list->head );
    }  
    return false; 

}
bool dllPopTail( doubleLinkedList* _list ){
    if( dllValidList( _list, true ) ){
        return _dllRemoveBNode( _list, _list->tail );
    }   
    return false;
}

void dllEmptyList( doubleLinkedList* _list ){
    while( _list->head != NULL ){
        dllPopTail( _list );  
    }
}

void* dllGetDataAt( doubleLinkedList* _list, int pos ){
    return _dllGetBNodeAt( _list, pos )->data;
}

void* dllGetHeadData( doubleLinkedList* _list ){
    return _list->head->data;
}
void* dllGetTailData( doubleLinkedList* _list ){
    return _list->tail->data;
}

bool dllDataUse( doubleLinkedList* _list, void (*dataUseFunc) ( void* data )  ){
    assert( _list != NULL );
    assert( ! dllIsEmpty( _list ) );

    return bNodeDataUse( _list->head, dataUseFunc );
}

void dllDelete( doubleLinkedList** _list ){
    dllEmptyList( *_list );
    free( *_list );
    *_list = NULL;
    assert( *_list == NULL );
}


