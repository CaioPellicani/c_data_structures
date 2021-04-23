#ifndef __CORE_B_CARDINAL_H__
#define __CORE_B_CARDINAL_H__

    #include "stdHeader.h"

    #define MSG_NO_MEM "Not sufficient memory!\n"
    #define MSG_NODEF "List is not defined!\n"
    #define MSG_EMPTY "The List is Empty!\n"
    #define MGS_OUT_RANGE(TYPE) "\n\nNot possible to %s. Position '%d' is out ouf range. Size of the List is '%d'\n", TYPE, pos, *_size 

    typedef struct bNode{
        void * data;
        struct bNode* nextNode;
        struct bNode* prevNode;
    }bNode;

    bNode* newBlankBNode();
    bool insertInFontOf( bNode** _firstNode, bNode** _lastNode, int* _size, bNode* _thisNode, void* _data );
    bool removeBNode( bNode** _firstNode, bNode** _lastNode, int* _size, bNode* _thisNode );
    bNode* getBNodeAt( bNode** _firstNode, bNode** _lastNode, int* _size, int pos );

#endif