#include "../../core/src/stdHeader.h"
#include "stackTest.h"  
#include "queueTest.h" 
#include "linkedListTest.h"
#include "orderLinkedListTests.h"
#include "doubleLinkedListTest.h"
#include "orderDoubleLinkedListTests.h"
#include "binarySearchTreeTests.h"
   
int main( int argc, char** argv ){ 
    getData( NULL );
    runStackTest();  
    runQueueTest(); 
    runLinkedListTest();
    runOrderLinkedListTest();
    runDoubleLinkedListTest();
    runOrderDoubleLinkedListTest();
    runBinarySearchTreeTest();
    return 0;  
}
 