#ifndef __CORE_S_CARDINAL_H__
#define __CORE_S_CARDINAL_H__

    #include "stdHeader.h"

    #define MSG_NO_MEM "Not sufficient memory!\n"
    #define MSG_NODEF "List is not defined!\n"
    #define MSG_EMPTY "The List is Empty!\n"
    #define MGS_OUT_RANGE(TYPE) "\n\nNot possible to %s. Position '%d' is out ouf range.\n", TYPE, position + 1 


    typedef struct node{
        void * data;
        struct node* nextNode;
    }node;

    node* newBlankNode();
    bool insertInBetween( node** firstNode, int* size, void* _data, node* _prevNode );
    bool removeNextNode( node** firstNode, int* size, node* _prevNode );
    node* getNodeAt( node* firstNode, int position, char* from, int size );
    void* getNodeData( node* firstNode, int position, int size );
    bool dataUse( node* firstNode, void ( *dataUseFunction ) ( void* data ) );

#endif