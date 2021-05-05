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

    typedef struct strCoordinates{
        tNode** root;
        int position;
    }coordinates;
    
    typedef struct leftOver{
        struct tNode* left;
        struct tNode* right;
    }leftOver;

    bool isLeaf( tNode *_thisNode );
    bool insertTNode( coordinates *_coords, tNode** _thisNode );
    bool insertNewTNode( coordinates *_coords, void* _data );
    tNode* removeTNode( coordinates *_coords, leftOver* _leftOver );
    bool tNodeDataUse( tNode* _mainRoot, dataUseFunction dataUseFunc, int type );

    leftOver *allocLeftOver();  
    coordinates *allocCoordinates();
#endif