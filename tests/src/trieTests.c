#include "../../src/trie.h"
#include "minunit.h"
#include "base_tests.h"

trie* aTrie;

runTrieTest(){
    INIT_TESTS( "Trie" );

    aTrie = initTrie( "abc123" );
    EX_NOT_NULL( "init", aTrie );

    getConvertTable( aTrie ); 

    trieInsert( aTrie );

    deleteTrie( &aTrie );
    EX_NULL( "deleteTrie", aTrie );

    END_TESTS;
}