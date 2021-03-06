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

    bool isLeaf( tNode *_thisNode );
    bool insertNewTNode( coordinates *_coords, void* _data );
    bool removeTNode( tNode** _mainRoot, coordinates *coords );
    bool tNodeDataUse( tNode* _mainRoot, dataUseFunction dataUseFunc, int type );

    coordinates *allocCoordinates();
#endif