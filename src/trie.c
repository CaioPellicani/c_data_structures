#include "trie.h"
#include "../core/src/core_multi_cardinal.h"

#define BOOL_VALID_TRIE( TRIE ) if( !_validTrie( TRIE ) ){ return false; }
#define BOOL_EMPTY_TRIE( TRIE ) if( isEmptyTrie( TRIE ) ){ return false; }
#define NULL_VALID_TRIE( TRIE ) if( !_validTrie( TRIE ) ){ return; }
#define NULL_EMPTY_TRIE( TRIE ) if( isEmptyTrie( TRIE ) ){ return NULL; }

int _convertPatterns(  trie* _trie, int _start, int _finish );
int _setConvertTable( trie *_trie, char* baseChar );

typedef struct strTrie{
    int arraySize;
    trieNode **mainRoot; 
    int charToInt[128];
    char intToChar[128];
}trie;

/*  -   INTERNAL FUNCTIONS  -   */
trie* initTrie( ){
    trie* newTrie = ( typeof( newTrie ) )malloc( sizeof( *newTrie ) );
    assert( newTrie != NULL );

    newTrie->mainRoot = NULL;
    newTrie->arraySize = 128;
    _setConvertTable( newTrie, "-n" );

    assert( newTrie->mainRoot == NULL );
    return newTrie;
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
        int start, finish;
        switch( *( baseChar + 1 ) ){
            case 'v': start = ' '; finish = '~'; break; //varchar
            case 'a': start = 'a'; finish = 'z'; break; //lower alphabet
            case 'A': start = 'A'; finish = 'Z'; break; //upper alphabet
            case 'n': start = '0'; finish = '9'; break; //numbers
        }
        lenght = _convertPatterns( _trie, start, finish );
    }
    else{ 
        lenght = strlen( baseChar ); 
        for( int i = 0; i < lenght; i++ ){
            _trie->charToInt[ abs( baseChar[i] ) ] = i;
            _trie->intToChar[i] = baseChar[i];
        }
    }
    return lenght;
}

int _convertPatterns(  trie* _trie, int _start, int _finish ){
    for( int i = 0; i <= ( _finish - _start ); i++ ){
        _trie->charToInt[ i + _start ] = i;
        _trie->intToChar[i] = i + _start;
    } 
    return _finish - _start;
}
