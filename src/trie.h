#ifndef __TRIE_H__
#define __TRIE_H__

    #include "../core/src/stdHeader.h"

    #define TABLE_SIZE 128

    typedef struct strTrie trie;

    trie* initTrie( char* _charPattern );
    void deleteTrie( trie** _trie );

    bool getConvertTable( trie* _trie, char dest[], int destSize );
    bool isEmptyTrie( trie* _trie );

    bool trieInsert( trie* _trie, char key[], void* data );
    bool trieSearch( trie* _trie, char key[] );
    void *trieGetData( trie* _trie, char key[] );
    bool trieRemove( trie* _trie, char key[] );

    bool getAllPartialKeys( trie* _trie, char partialKey[], char dest[], int destSize, char delimiter );

    void emptyTrie( trie* _trie );
#endif