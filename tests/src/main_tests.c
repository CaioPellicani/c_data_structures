
#include "../../core/src/stdHeader.h"
#include "../../core/src/core.h"
#include "stackTest.h"  
#include "queueTest.h" 
#include "linkedListTest.h"
#include "orderLinkedListTests.h"
   
int main( int argc, char** argv ){ 
    runStackTest();  
    runQueueTest(); 
    runLinkedListTest();
    runOrderLinkedListTest();
    return 0;  
}
 