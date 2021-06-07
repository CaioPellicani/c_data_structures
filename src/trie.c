#include "trie.h"
#include "../core/src/core_multi_cardinal.h"

#define BOOL_VALID_TRIE( TRIE ) if( !_validTrie( TRIE ) ){ return false; }
#define BOOL_EMPTY_TRIE( TRIE ) if( isEmptyTrie( TRIE ) ){ return false; }
#define NULL_VALID_TRIE( TRIE ) if( !_validTrie( TRIE ) ){ return; }
#define NULL_EMPTY_TRIE( TRIE ) if( isEmptyTrie( TRIE ) ){ return NULL; }

int convertPattern( trie* _trie, const char *pattern );
int _setConvertTable( trie *_trie, char* baseChar );

typedef struct strTrie{
    int arraySize;
    trieNode **mainRoot; 
    int charToInt[TABLE_SIZE];
    char intToChar[TABLE_SIZE];
}trie;

/*  -   INTERNAL FUNCTIONS  -   */
trie* initTrie( char* _charPattern ){
    trie* newTrie = ( typeof( newTrie ) )malloc( sizeof( *newTrie ) );
    assert( newTrie != NULL );

    newTrie->mainRoot = NULL;
    newTrie->arraySize = _setConvertTable( newTrie, _charPattern );

    assert( newTrie->mainRoot == NULL );
    return newTrie;
}


void getConvertTable( trie* _trie ){
    for( int i = 0; i < _trie->arraySize; i++ ){
        printf( "%d - '%c'\n", i, _trie->intToChar[i] );
    }
}

bool trieInsert( trie*_trie ){
    insertTrieNode( _trie->mainRoot, _trie->arraySize );
    return true;
}

void emptyTrie( trie* _trie ){
    //NULL_VALID_TRIE( _trie );
    return;
}

void deleteTrie( trie** _trie ){
    emptyTrie( *_trie );
    free( *_trie );
    *_trie = NULL;
    assert( *_trie == NULL );
}

/*  -   EXTERNAL FUNCTIONS  -   */

bool _validTrie( trie *_trie ){
    return ( _trie != NULL );
}

int _setConvertTable( trie *_trie, char* baseChar ){
    int lenght = 0;
    memset( &_trie->charToInt, -1, sizeof ( _trie->charToInt ) );

    if( *baseChar == '-' ){ 
        switch( *( baseChar + 1 ) ){
            case 'v': return convertPattern( _trie, " -~" ); break; //varchar
            case 'a': return convertPattern( _trie, "a-z" ); break; //lower alphabet
            case 'A': return convertPattern( _trie, "A-Z" ); break; //upper alphabet
            case 'n': return convertPattern( _trie, "0-9" ); break; //numbers
        }
    }
    else{ 
        int j = '0';
        lenght = strlen( baseChar ); 
        for( int i = 0; i < lenght; i++ ){
            j = abs( baseChar[i] );
            _trie->charToInt[j] = i;
            _trie->intToChar[i] = j;
        }
    }
    return lenght;
}

int convertPattern( trie* _trie, const char *pattern ){
    char _start = pattern[0];
    char _finish = pattern[2];

    for( int i = 0; i <= ( _finish - _start ); i++ ){
        _trie->charToInt[ i + _start ] = i;
        _trie->intToChar[i] = i + _start;
    } 
    return _finish - _start + 1;
}
