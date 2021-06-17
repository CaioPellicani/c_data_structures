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

    trieInsert( Trie, "teste_0", NULL );
    EX_TRUE( "trieSearch", trieSearch( Trie, "teste_0") );

    EX_FALSE( "isEmptyTrie", isEmptyTrie( Trie ) );

    EX_FALSE( "trieSearch fail", trieSearch( Trie, "teste_1") );

    EX_FALSE( "charValidation", trieInsert( Trie, "teste_0", NULL ) );
    EX_FALSE( "charValidation", trieSearch( Trie, "failTest") );

    deleteTrie( &Trie );
    EX_NULL( "deleteTrie", Trie );

    /* NUMBERS */
    
    nTrie = initTrie( "-n" );
    getConvertTable( nTrie, result, RESULT_SIZE );
    EX_STR_EQ( "getConvertTable", "0123456789", result );
    
    trieInsert( nTrie, "1978", NULL );
    EX_TRUE( "trieSearch", trieSearch( nTrie, "1978") );
    
    deleteTrie( &nTrie );

    /* LOWER ALPHABET */

    aTrie = initTrie( "-a" );
    getConvertTable( aTrie, result, RESULT_SIZE );
    EX_STR_EQ( "getConvertTable", "abcdefghijklmnopqrstuvwxyz", result );
    deleteTrie( &aTrie );

    /* UPPER ALPHABET */

    ATrie = initTrie( "-A" );
    getConvertTable( ATrie, result, RESULT_SIZE );
    EX_STR_EQ( "getConvertTable", "ABCDEFGHIJKLMNOPQRSTUVWXYZ", result );
    deleteTrie( &ATrie );

    /* VARCHAR */

    vTrie = initTrie( "-v" ); 
    const char test[] = { " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~" };
    getConvertTable( vTrie, result, RESULT_SIZE );
    EX_STR_EQ( "getConvertTable", test, result );

    trieInsert( vTrie, "varchar_0", NULL );
    EX_TRUE( "trieSearch", trieSearch( vTrie, "varchar_0") );
    deleteTrie( &vTrie );
    END_TESTS;
}