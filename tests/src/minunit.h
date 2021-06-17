 /* file: minunit.h
based on http://www.jera.com/techinfo/jtns/jtn002.html

 #define mu_assert(message, test) do { if (!(test)) return message; } while (0)
 #define mu_run_test(test) do { char *message = test(); thisGroup.testsRun++; \
                                if (message) return message; } while (0)
*/

#ifndef _MINUNIT_
#define _MINUNIT_

#include "base_tests.h"

typedef struct{
    int testsRun;
    char name[30];
    data **template;
}testGroup;

int testFailure( testGroup group, char* testName, char*file, int line, char* expect, char* get );
int closeTest( testGroup group );

#define INIT_TESTS( groupName )                                  \
  testGroup thisGroup;                                           \
  thisGroup.testsRun = 0;                                        \
  strcpy( thisGroup.name, groupName );                           \
  data *searchTemplate = malloc( sizeof( *searchTemplate ) );    \
  searchTemplate->value = 0;\
  thisGroup.template = &searchTemplate;    

#define EX_STR_EQ( testName, expect, result )                                     \
  if( strcmp( expect, result ) != 0 ){                                            \
    return testFailure( thisGroup, testName, __FILE__, __LINE__, expect, result );\
  }                                                                               \
  thisGroup.testsRun++


#define EX_INT_EQ( testName, expect, result )                                 \
  if( expect != result ){                                                     \
    char exp[30], res[30];                                                    \
    sprintf( exp, "%d", expect );                                             \
    sprintf( res, "%d", result );                                             \
    return testFailure( thisGroup, testName, __FILE__, __LINE__, exp, res );  \
  }                                                                           \
  thisGroup.testsRun++


#define EX_NULL( testName , result )                                           \
  if( result != NULL ){                                                        \
    return testFailure( thisGroup, testName, __FILE__, __LINE__, "NULL", "" ); \
  }                                                                            \
  thisGroup.testsRun++

#define EX_NOT_NULL( testName , result )                                          \
  if( result == NULL ){                                                           \
    return testFailure( thisGroup, testName, __FILE__, __LINE__, "NOT_NULL", "" );\
  }                                                                               \
  thisGroup.testsRun++

#define EX_TRUE( testName , result )                                           \
  if( !result ){                                                               \
    return testFailure( thisGroup, testName, __FILE__, __LINE__, "TRUE", "" ); \
  }                                                                            \
  thisGroup.testsRun++

#define EX_FALSE( testName , result )                                           \
  if( result ){                                                                 \
    return testFailure( thisGroup, testName, __FILE__, __LINE__, "FALSE", "" ); \
  }                                                                             \
  thisGroup.testsRun++

#define END_TESTS                                              \
  if( thisGroup.testsRun > 0 ){                                \
    printf( "\nGroup: \033[33m%s\033[0m\n", thisGroup.name );  \
    printf( "Run %d tests\n", thisGroup.testsRun );            \
    printf( "\033[32mALL TESTS PASSED!!\033[0m\n" );           \
  }                                                            \
  else{                                                        \
    printf( "\nGroup: \033[33m%s\033[0m\n", thisGroup.name );  \
    printf( "\033[35mNOT FOUND ANY TEST!!\033[0m\n" );         \
  }                                                            \
  return closeTest( thisGroup );                                                             

#endif