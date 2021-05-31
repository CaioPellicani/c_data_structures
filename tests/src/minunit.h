 /* file: minunit.h
based on http://www.jera.com/techinfo/jtns/jtn002.html

 #define mu_assert(message, test) do { if (!(test)) return message; } while (0)
 #define mu_run_test(test) do { char *message = test(); tests_run++; \
                                if (message) return message; } while (0)
*/

#ifndef _MINUNIT_
#define _MINUNIT_

#define INIT_TESTS( groupName )                               \
  int tests_run = 0;                                          \
  char groupTestName[30] = groupName;                         \
  searchTemplate = calloc( sizeof( data ), sizeof( data ) );  \
  dataSearch = NULL;              

#define EX_STR_EQ( testName, expect, result )                \
  if( strcmp( expect, result ) != 0 ){                       \
    printf( "\nGroup: \033[33m%s\033[0m", groupTestName );   \
    printf( "\nRun %d tests\n", tests_run );                 \
    printf( "\n\033[31mTEST %s FAILED\n\033[0m", testName ); \
    printf( "EXPECT -> %s\n", expect );                      \
    printf( "GET    -> %s\n\n", result );                    \
    free( searchTemplate );                                  \
    return tests_run;                                        \
  }                                                          \
  tests_run++


#define EX_INT_EQ( testName, expect, result )                \
  if( expect != result ){                                    \
    printf( "\nGroup: \033[33m%s\033[0m", groupTestName );   \
    printf( "\nRun %d tests\n", tests_run );                 \
    printf( "\n\033[31mTEST %s FAILED\n\033[0m", testName ); \
    printf( "EXPECT -> %d\n", expect );                      \
    printf( "GET    -> %d\n\n", result );                    \
    free( searchTemplate );                                  \
    return tests_run;                                        \
  }                                                          \
  tests_run++


#define EX_NULL( testName , result )                         \
  if( result != NULL ){                                      \
    printf( "\nGroup: \033[33m%s\033[0m", groupTestName );   \
    printf( "\nRun %d tests\n", tests_run );                 \
    printf( "\n\033[31mTEST %s FAILED\n\033[0m", testName ); \
    printf( "EXPECT -> NULL\n" );                            \
    free( searchTemplate );                                  \
    return tests_run;                                        \
  }                                                          \
  tests_run++

#define EX_NOT_NULL( testName , result )                     \
  if( result == NULL ){                                      \
    printf( "\nGroup: \033[33m%s\033[0m", groupTestName );   \
    printf( "\nRun %d tests\n", tests_run );                 \
    printf( "\n\033[31mTEST %s FAILED\n\033[0m", testName ); \
    printf( "EXPECT -> NOT NULL\n" );                        \
    free( searchTemplate );                                  \
    return tests_run;                                        \
  }                                                          \
  tests_run++

#define EX_TRUE( testName , result )                         \
  if( !result ){                                             \
    printf( "\nGroup: \033[33m%s\033[0m", groupTestName );   \
    printf( "\nRun %d tests\n", tests_run );                 \
    printf( "\n\033[31mTEST %s FAILED\n\033[0m", testName ); \
    printf( "EXPECT -> TRUE\n" );                            \
    free( searchTemplate );                                  \
    return tests_run;                                        \
  }                                                          \
  tests_run++

#define EX_FALSE( testName , result )                        \
  if( result ){                                              \
    printf( "\nGroup: \033[33m%s\033[0m", groupTestName );   \
    printf( "\nRun %d tests\n", tests_run );                 \
    printf( "\n\033[31mTEST %s FAILED\n\033[0m", testName ); \
    printf( "EXPECT -> FALSE\n" );                           \
    free( searchTemplate );                                  \
    return tests_run;                                        \
  }                                                          \
  tests_run++

#define END_TESTS                                            \
  if( tests_run > 0 ){                                       \
    printf( "\nGroup: \033[33m%s\033[0m\n", groupTestName ); \
    printf( "Run %d tests\n", tests_run );                   \
    printf( "\033[32mALL TESTS PASSED!!\033[0m\n" );         \
    free( searchTemplate );                                  \
    return tests_run;                                        \
  }                                                          \
  printf( "\nGroup: \033[33m%s\033[0m\n", groupTestName );   \
  printf( "\033[35mNOT FOUND ANY TEST!!\033[0m\n" );         \
  free( searchTemplate );                                    \
  return tests_run;                                                    

#endif