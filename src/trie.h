#ifndef __TRIE_H__
#define __TRIE_H__

    #include "../core/src/stdHeader.h"

    #define TABLE_SIZE 128
    #define CONTROL_CHAR 29 // GROUP SEPARATOR

    typedef struct strTrie trie;

    trie* initTrie( char* _charPattern );
    void deleteTrie( trie** _trie );

    bool getConvertTable( trie* _trie, char dest[], int destSize );
    bool isEmptyTrie( trie* _trie );

    bool trieInsert( trie* _trie, char key[], void* data );
    bool trieSearch( trie* _trie, char key[] );
    void *trieGetData( trie* _trie, char key[] );
    bool trieRemove( trie* _trie, char key[] );

    bool getAllKeys( trie* _trie, char partialKey[], char dest[], int destSize );
    
    void emptyTrie( trie* _trie );
#endif

/*
bool llIsEmpty( linkedList* _list );
int llGetSize( linkedList* _list );

void* llGetDataAt( linkedList* _list, int pos );
void* llGetHeadData( linkedList* _list );
void* llGetTailData( linkedList* _list );

bool llPushHead( linkedList* _list, void* _data );
bool llPushTail( linkedList* _list, void* _data );
bool llInsertAt( linkedList* _list, void* _data, int pos );

bool llPopHead( linkedList* _list );
bool llPopTail( linkedList* _list );
bool llRemoveAt( linkedList* _list, int pos );

void llEmptyList( linkedList* _list );

bool llDataUse( linkedList* _list, void ( *dataUseFunction ) ( void* data) );
*/