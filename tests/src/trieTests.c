#include "../../src/trie.h"
#include "minunit.h"
#include "base_tests.h"

trie* aTrie;

runTrieTest(){
    INIT_TESTS( "Trie" );

    aTrie = initTrie();
    EX_NOT_NULL( "init", aTrie ); 

    trieInsert( aTrie );

    deleteTrie( &aTrie );
    EX_NULL( "deleteTrie", aTrie );

    END_TESTS;
}