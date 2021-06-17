#include "trie.h"

#define BOOL_VALID_TRIE( TRIE ) if( !_validTrie( TRIE ) ){ return false; }
#define BOOL_EMPTY_TRIE( TRIE ) if( isEmptyTrie( TRIE ) ){ return false; }
#define VALID_TRIE( TRIE ) if( !_validTrie( TRIE ) ){ return; }
#define NULL_EMPTY_TRIE( TRIE ) if( isEmptyTrie( TRIE ) ){ return NULL; }

#define BOOL_ARRAY_SIZE( ARRAY_SIZE, TRIE_SIZE ) if( ARRAY_SIZE < TRIE_SIZE ){ return false; }

typedef void ( *dataUseFunction ) ( void* data );

typedef struct trieNode{
    void * data;
    bool isTerminal;
    struct trieNode* root;
    struct trieNode** nextNodes;
}trieNode;

typedef struct strTrie{
    int arraySize;
    trieNode *mainRoot; 
    int charToInt[TABLE_SIZE];
    char intToChar[TABLE_SIZE];
}trie;

trieNode* _newBlankTrieNode( int size );
trieNode** _allocNextNodesArray( int size );

bool _validTrie( trie *_trie );
bool _isLeaf( trieNode *_node, int arraySize );

int _convertPattern( trie* _trie, const char *pattern );
int _convertString( trie* _trie, const char *string );
int _setConvertTable( trie *_trie, char* baseChar );

/*  -   EXTERNAL FUNCTIONS  -   */

trie* initTrie( char* _charPattern ){
    trie* newTrie = ( typeof( newTrie ) )malloc( sizeof( *newTrie ) );
    assert( newTrie != NULL );

    newTrie->arraySize = _setConvertTable( newTrie, _charPattern );
    newTrie->mainRoot = _newBlankTrieNode( newTrie->arraySize );

    return newTrie;
}

bool getConvertTable( trie* _trie, char dest[], int destSize ){
    BOOL_VALID_TRIE( _trie );

    if( destSize < _trie->arraySize ) return false;

    for( int i = 0; i < _trie->arraySize; i++ ){
        dest[i] = _trie->intToChar[i];
    }
    dest[ _trie->arraySize ] = '\0';

    return true;
}

bool trieInsert( trie*_trie, char key[], void* _data ){
    BOOL_VALID_TRIE( _trie );
    trieNode *seeingNode = _trie->mainRoot;

    int i = -1;
    int keyChar = -1;
    while( key[++i] != '\0' ){
        keyChar = _trie->charToInt[ abs( key[i] ) ];
        if( keyChar == -1 ){ return false; }

        if( seeingNode->nextNodes[ keyChar ] == NULL ){
            seeingNode->nextNodes[ keyChar ] = _newBlankTrieNode( _trie->arraySize );
            seeingNode->nextNodes[ keyChar ]->root = seeingNode;
        }
        seeingNode = seeingNode->nextNodes[ keyChar ];
    }
    seeingNode->isTerminal = true;
    seeingNode->data = _data;
    return true;
}

bool trieSearch( trie* _trie, char key[] ){ 
    BOOL_EMPTY_TRIE( _trie );
    trieNode *seeingNode = _trie->mainRoot;

    int i = -1;
    int keyChar = -1;
    while( key[++i] != '\0' ){
        keyChar = _trie->charToInt[ abs( key[i] ) ];
        if( ( keyChar == -1 ) || ( seeingNode->nextNodes[ keyChar ] == NULL ) ){
            break;
        }
        seeingNode = seeingNode->nextNodes[ keyChar ];
    }
    
    return ( ( i == strlen( key ) ) && ( seeingNode->isTerminal ) ); 
}

void *trieGetData( trie* _trie, char key[] ){ 
    BOOL_EMPTY_TRIE( _trie );
    return NULL; 
}

bool trieRemove( trie* _trie, char key[] ){ 
    BOOL_EMPTY_TRIE( _trie );   
    return true; 
}

bool isEmptyTrie( trie* _trie ){
    BOOL_VALID_TRIE( _trie );
    return _isLeaf( _trie->mainRoot, _trie->arraySize );
}

void emptyTrie( trie* _trie ){
    VALID_TRIE( _trie );
    return;
}

void deleteTrie( trie** _trie ){
    emptyTrie( *_trie );
    free( *_trie );
    *_trie = NULL;
    assert( *_trie == NULL );
}

/*  -   INTERNAL FUNCTIONS  -   */

bool _validTrie( trie *_trie ){
    return ( _trie != NULL );
}

bool _isLeaf( trieNode *_node, int arraySize ){
    size_t result = 0;

    for( int i = 0; i < arraySize; i++ ){
        result += ( typeof( result ) )_node->nextNodes[i];
    }
    return !result;
}

int _setConvertTable( trie *_trie, char* baseChar ){
    memset( &_trie->charToInt, -1, sizeof ( _trie->charToInt ) );

    if( *baseChar == '-' ){ 
        switch( *( baseChar + 1 ) ){
            case 'v': return _convertPattern( _trie, " -~" ); break; //varchar
            case 'a': return _convertPattern( _trie, "a-z" ); break; //lower alphabet
            case 'A': return _convertPattern( _trie, "A-Z" ); break; //upper alphabet
            case 'n': return _convertPattern( _trie, "0-9" ); break; //numbers
        }
    }
    return _convertString( _trie, baseChar );
}

int _convertString( trie* _trie, const char *string ){
    int result = 0;
    int j;
    int i = -1;
    int pos = 0;
    while( string[++i] != '\0' ){
        j = abs( string[i] );
        if( _trie->charToInt[j] == -1 ){
            _trie->charToInt[j] = pos;
            _trie->intToChar[pos] = j;
            result ++;
            pos++;
        }
    }
    return result;
}

int _convertPattern( trie* _trie, const char *pattern ){
    char _start = pattern[0];
    char _finish = pattern[2];

    for( int i = 0; i <= ( _finish - _start ); i++ ){
        _trie->charToInt[ i + _start ] = i;
        _trie->intToChar[i] = i + _start;
    } 
    return _finish - _start + 1;
}

trieNode* _newBlankTrieNode( int size ){
    trieNode* newNode = ( typeof( newNode ) ) malloc( sizeof( *newNode ) );
    assert( newNode != NULL );

    newNode->data = NULL;
    newNode->isTerminal = false;
    newNode->root = NULL;
    newNode->nextNodes = _allocNextNodesArray( size );

    return newNode;
}

trieNode** _allocNextNodesArray( int size ){
    trieNode** newArray = ( typeof( newArray ) ) malloc( sizeof( *newArray ) * size );
    assert( newArray != NULL );

    for( int i = 0; i < size; i++ ){
        newArray[i] = NULL;
    }
    return newArray;
}
