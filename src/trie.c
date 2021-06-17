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

typedef struct strKeyControl{
    int steps;
    char* key;
    trieNode* seeingNode;
}keyControl;

trieNode* _newBlankTrieNode( int size );
trieNode** _allocNextNodesArray( int size );

bool _validTrie( trie *_trie );
bool _isLeaf( trieNode *_node, int arraySize );

int _convertPattern( trie* _trie, const char *pattern );
int _convertString( trie* _trie, const char *string );
int _setConvertTable( trie *_trie, char* baseChar );

bool _findLastTrieNode( trie* _trie, keyControl* _control );
bool _deleteTrieNode( trieNode** deadNode, int _arraySize );
void _recursiveRemove( trie* _trie, trieNode *seeingNode, char key[], int step );
void _recursiveCleaning( trieNode** seeingNode, int* arraySize )

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
    keyControl control = { -1, key, _trie->mainRoot };

    while( ! _findLastTrieNode( _trie, &control ) ){
        int keyChar = _trie->charToInt[ abs( key[ control.steps ] ) ];
        if( keyChar == -1 ){ return false; }

        control.seeingNode->nextNodes[ keyChar ] = _newBlankTrieNode( _trie->arraySize );
        control.seeingNode->nextNodes[ keyChar ]->root = control.seeingNode;      
        control.seeingNode = control.seeingNode->nextNodes[ keyChar ];      
    }
    control.seeingNode->isTerminal = true;
    control.seeingNode->data = _data;

    return true;
}

bool trieSearch( trie* _trie, char key[] ){ 
    BOOL_VALID_TRIE( _trie );
    keyControl control = { -1, key, _trie->mainRoot };
    return ( ( _findLastTrieNode( _trie, &control ) ) && ( control.seeingNode->isTerminal ) );
}

void *trieGetData( trie* _trie, char key[] ){ 
    BOOL_EMPTY_TRIE( _trie );
    keyControl control = { -1, key, _trie->mainRoot };
    if( ( _findLastTrieNode( _trie, &control ) ) && ( control.seeingNode->isTerminal ) ){
        return control.seeingNode->data;
    }
    return NULL; 
}

bool trieRemove( trie* _trie, char key[] ){ 
    BOOL_EMPTY_TRIE( _trie );   
    if( !trieSearch( _trie, key ) ) return false;

    _recursiveRemove( _trie, _trie->mainRoot, key, 0 );
    return true;
}

bool isEmptyTrie( trie* _trie ){
    BOOL_VALID_TRIE( _trie );
    return _isLeaf( _trie->mainRoot, _trie->arraySize );
}

void emptyTrie( trie* _trie ){
    VALID_TRIE( _trie );
    if( !_isLeaf( _trie->mainRoot, _trie->arraySize ) ){
        _recursiveCleaning( &_trie->mainRoot, &_trie->arraySize );
    }
}

void deleteTrie( trie** _trie ){
    emptyTrie( *_trie );
    _deleteTrieNode( &( *_trie )->mainRoot, ( *_trie )->arraySize );
    free( *_trie );
    *_trie = NULL;
    assert( *_trie == NULL );
}

/*  -   INTERNAL FUNCTIONS  -   */

bool _validTrie( trie *_trie ){
    return ( _trie != NULL );
}

bool _isLeaf( trieNode *_node, int arraySize ){
    assert( _node != NULL );
    assert( arraySize > 0 );
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

bool _deleteTrieNode( trieNode** deadNode, int _arraySize ){
    assert( *deadNode != NULL );
    assert( _isLeaf( *deadNode, _arraySize ) );

    free( ( *deadNode )->data );
    free( ( *deadNode )->nextNodes );
    free( ( *deadNode ) );
    *deadNode = NULL;
    return true;
}

trieNode** _allocNextNodesArray( int size ){
    assert( size > 0 );
    trieNode** newArray = ( typeof( newArray ) ) malloc( sizeof( *newArray ) * size );
    assert( newArray != NULL );

    for( int i = 0; i < size; i++ ){
        newArray[i] = NULL;
    }
    return newArray;
}

bool _findLastTrieNode( trie* _trie, keyControl* _control ){
    while( _control->key[ ++_control->steps ] != '\0' ){
        int keyChar = _trie->charToInt[ abs( _control->key[ _control->steps ] ) ];
        if( ( keyChar == -1 ) || ( _control->seeingNode->nextNodes[ keyChar ] == NULL ) ){
            break;
        }
        _control->seeingNode = _control->seeingNode->nextNodes[ keyChar ];
    }

    return ( _control->steps == strlen( _control->key ) );
}

void _recursiveRemove( trie* _trie, trieNode *seeingNode, char key[], int step ){
    int keyChar = _trie->charToInt[ abs( key[ step ] ) ];
    if( key[ step + 1 ] != '\0' ){
        _recursiveRemove( _trie, seeingNode->nextNodes[keyChar], key, step + 1 );
    }
    if( ( _isLeaf( seeingNode->nextNodes[keyChar], _trie->arraySize ) ) && 
        ( ( step + 1 == strlen( key ) ) || ( !seeingNode->nextNodes[keyChar]->isTerminal ) ) ){
            
        _deleteTrieNode( &seeingNode->nextNodes[keyChar], _trie->arraySize );
    }
}

void _recursiveCleaning( trieNode** seeingNode, int* arraySize ){
    for( int i = 0; i < *arraySize; i++ ){
        if( ( *seeingNode )->nextNodes[i] != NULL ){
            _recursiveCleaning( &( *seeingNode )->nextNodes[i], arraySize );
             _deleteTrieNode( &( *seeingNode )->nextNodes[i], *arraySize );
        }
    }
}
