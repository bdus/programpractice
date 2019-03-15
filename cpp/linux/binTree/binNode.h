#pragma once
#ifndef NULL
#define NULL 0
#endif
#define BinNodePosi(T) BinNode<T>*
#define stature(p) ((p) ? (p)->height : -1) //节点高度（与“空树高度为-1”的约定相统一）
typedef enum { RB_RED, RB_BLACK } RBColor; //节点颜色

namespace MyDSA
{
    template <typename T>
    struct BinNode
    {
        T data;
        BinNodePosi(T) parent; BinNodePosi(T) lc; BinNodePosi(T) rc;
        int height;
        int npl; //Null Path Length
        RBColor color; //红黑树

        BinNode() : parent(NULL), lc(NULL), rc(NULL), height(0), npl(1), color(RB_RED) {}
        BinNode ( T e, BinNodePosi(T) p = NULL, BinNodePosi(T) lc = NULL, BinNodePosi(T) rc = NULL,
                             int h = 0, int l = 1, RBColor c = RB_RED ) :
            data ( e ), parent ( p ), lc ( lc  ), rc ( rc  ), height ( h ), npl ( l ), color ( c ) {  }

        //op
        
        int size();
        BinNodePosi(T) insertAsLC ( T const& ); //作为当前节点的左孩子插入新节点
        BinNodePosi(T) insertAsRC ( T const& ); //作为当前节点的右孩子插入新节点
        // BinNodePosi(T) succ(); //取当前节点的直接后继
        template <typename VST> void travLevel ( VST& ); //子树层次遍历
        template <typename VST> void travPre ( VST& ); //子树先序遍历
        template <typename VST> void travIn ( VST& ); //子树中序遍历
        template <typename VST> void travPost ( VST& ); //子树后序遍历

        // 比较器、判等器（各列其一，其余自行补充）
        bool operator< ( BinNode const& bn ) { return data < bn.data; } //小于
        bool operator== ( BinNode const& bn ) { return data == bn.data; } //等于
      
    };

}

#include "binNode_implemention.h"