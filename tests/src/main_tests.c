#include "stackTest.h"  
#include "queueTest.h" 
#include "linkedListTest.h"
#include "orderLinkedListTests.h"
#include "doubleLinkedListTest.h"
   
int main( int argc, char** argv ){ 
    runStackTest();  
    runQueueTest(); 
    runLinkedListTest();
    runOrderLinkedListTest();
    runDoubleLinkedListTest();
    return 0;  
}
 