#include "double_linked_list.h"
#include "../core/src/core_bi_cardinal.h"

typedef struct strList{
    bNode * head;
    bNode * tail;
    int size;
}doubleList;

bool validDList( doubleList* _list, bool _seeIfEmpty );

doubleList* initDList(){
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

bool dllIsEmpty( doubleList* _list ){
    return ( _list->head == NULL ) && ( _list->tail == NULL );
}

bool validDList( doubleList* _list, bool _seeIfEmpty ){
    if( _list == NULL ){
        die( MSG_NODEF );
    }
    if( ( _seeIfEmpty ) && ( dllIsEmpty( _list ) ) ){
        die( MSG_EMPTY );
    }

    return true;
}

bool _dllInsertInFontOf( doubleList* _list, bNode* _thisNode, void* _data ){
    return insertInFontOf( &_list->head, &_list->tail, &_list->size, _thisNode, _data );
}
bool _dllRemoveBNode( doubleList* _list, bNode* _thisNode ){
    return removeBNode( &_list->head, &_list->tail, &_list->size, _thisNode ); 
}

bNode* _dllGetBNodeAt( doubleList* _list, int pos ){
    return getBNodeAt( &_list->head, &_list->tail, &_list->size, pos );
}

bool pushDLLHead( doubleList* _list, void* _data ){  
   if( validDList( _list, false ) ){
       return _dllInsertInFontOf( _list, _list->head, _data );
   } 
   return false;
}

bool pushDLLTail( doubleList* _list, void* _data ){
    if( validDList( _list, false ) ){
        return _dllInsertInFontOf( _list, NULL, _data );
    }
    return false;
}

bool insertDLLAt( doubleList* _list, void* _data, int pos ){
    if( validDList( _list, false ) ){
        if( pos > _list->size ){
            die( "'insert'" );
        }
        else{
            return _dllInsertInFontOf( _list, _dllGetBNodeAt( _list, pos ), _data );
        }
    }
    return false;
}

bool removeDLLAt( doubleList* _list, int pos ){
    if( validDList( _list, false ) ){
        if( pos > _list->size ){
            die( "'remove'" );
        }
        if( pos == _list->size ){
            return popDLLTail( _list );
        }
        else{
            return _dllRemoveBNode( _list, _dllGetBNodeAt( _list, pos ) );
        }
    }
    return false;
}

bool popDLLHead( doubleList* _list ){
    if( validDList( _list, true ) ){
        return _dllRemoveBNode( _list, _list->head );
    }  
    return false; 

}
bool popDLLTail( doubleList* _list ){
    if( validDList( _list, true ) ){
        return _dllRemoveBNode( _list, _list->tail );
    }   
    return false;
}

void emptyDLL( doubleList* _list ){
    while( _list->head != NULL ){
        popDLLTail( _list );  
    }
}

void* getDLLDataAt( doubleList* _list, int pos ){
    return _dllGetBNodeAt( _list, pos )->data;

}

bool dllDataUse( doubleList* _list, void (*dataUseFunc) ( void* data )  ){
    assert( _list != NULL );
    assert( ! dllIsEmpty( _list ) );

    return bNodeDataUse( _list->head, dataUseFunc );
}

void deleteDLL( doubleList** _list ){
    emptyDLL( *_list );
    free( *_list );
    *_list = NULL;
    assert( *_list == NULL );
}


