#include "stackTest.h"  
#include "queueTest.h" 
#include "linkedListTest.h"
#include "orderLinkedListTests.h"
#include "doubleLinkedListTest.h"
#include "orderDoubleLinkedListTests.h"
   
int main( int argc, char** argv ){ 
    runStackTest();  
    runQueueTest(); 
    runLinkedListTest();
    runOrderLinkedListTest();
    runDoubleLinkedListTest();
    runOrderDoubleLinkedListTest();
    return 0;  
}
 