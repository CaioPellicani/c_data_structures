#ifndef __CORE_TRI_CARDINAL_H__
#define __CORE_TRI_CARDINAL_H__

    #include "stdHeader.h"

    enum coordinates{ ROOT, LEFT, RIGHT, BOTHER };
    enum order{ PREORDER, INORDER, POSTORDER };

    typedef void ( *dataUseFunction ) ( void* data );

    typedef struct tNode {
        void * data;
        struct tNode* root;
        struct tNode* left;
        struct tNode* right;
    }tNode;

    bool insertTNode( tNode** _root, int _where, void* _data );
    tNode* removeTNode( tNode** _root, int _where );
    void tNodeDataUse( tNode* _mainRoot, dataUseFunction dataUseFunc, int type );
#endif