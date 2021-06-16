#include "../../src/trie.h"
#include "minunit.h"
#include "base_tests.h"

trie* Trie;
trie* nTrie;
trie* aTrie;
trie* ATrie;
trie* vTrie;

runTrieTest(){
    INIT_TESTS( "Trie" );

    Trie = initTrie( "teste_0123" );
    EX_NOT_NULL( "init", Trie );
    getConvertTable( Trie, result, RESULT_SIZE );
    EX_STR_EQ( "getConvertTable", "tes_0123", result );
    EX_TRUE( "isEmptyTrie", isEmptyTrie( Trie ) ); 

    trieInsert( Trie, "teste_0" );
    EX_FALSE( "isEmptyTrie", isEmptyTrie( Trie ) );

    deleteTrie( &Trie );
    EX_NULL( "deleteTrie", Trie );

    /* NUMBERS */
    
    nTrie = initTrie( "-n" );
    getConvertTable( nTrie, result, RESULT_SIZE );
    EX_STR_EQ( "getConvertTable numbers", "0123456789", result );
    
    trieInsert( nTrie, "1978" );
    EX_FALSE( "isEmptyTrie", isEmptyTrie( nTrie ) );
    
    deleteTrie( &nTrie );

    /* LOWER ALPHABET */

    aTrie = initTrie( "-a" );
    getConvertTable( aTrie, result, RESULT_SIZE );
    EX_STR_EQ( "getConvertTable lower alphabet", "abcdefghijklmnopqrstuvwxyz", result );
    deleteTrie( &aTrie );

    /* UPPER ALPHABET */

    ATrie = initTrie( "-A" );
    getConvertTable( ATrie, result, RESULT_SIZE );
    EX_STR_EQ( "getConvertTable upper alphabet", "ABCDEFGHIJKLMNOPQRSTUVWXYZ", result );
    deleteTrie( &ATrie );

    /* VARCHAR */

    vTrie = initTrie( "-v" ); 
    const char test[] = { " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~" };
    getConvertTable( vTrie, result, RESULT_SIZE );
    EX_STR_EQ( "getConvertTable numbers", test, result );

    trieInsert( vTrie, "varchar_0" );
    EX_FALSE( "isEmptyTrie", isEmptyTrie( vTrie ) );
    deleteTrie( &vTrie );
    END_TESTS;
}