#ifndef __CORE_BI_CARDINAL_H__
#define __CORE_BI_CARDINAL_H__

    #include "stdHeader.h"

    typedef void ( *dataUseFunction ) ( void* data );
    typedef struct bNode{
        void * data;
        struct bNode* nextNode;
        struct bNode* prevNode;
    }bNode;

    bool insertInFontOf( bNode** _firstNode, bNode** _lastNode, int* _size, bNode* _thisNode, void* _data );
    bool removeBNode( bNode** _firstNode, bNode** _lastNode, int* _size, bNode* _thisNode );
    bNode* getBNodeAt( bNode** _firstNode, bNode** _lastNode, int* _size, int pos );
    bool bNodeDataUse( bNode* _firstNode, dataUseFunction dataUseFunc  );
#endif