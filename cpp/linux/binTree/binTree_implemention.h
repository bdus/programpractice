#include "binnode_macro_basic.h"
//#include "release.h"

#undef release
#define release(x)  if(x) {delete x;} 

#ifndef stature
#define stature(p) ( (p)?(p)->height : -1)
#endif
#ifndef max
#define max(a,b)  ((a>b)?(a):(b))
#endif

namespace MyDSA
{
    //update
    template <typename T>
    int binTree<T>::updateHeight(BinNodePosi(T) x)
    {
        return x->height = 1 + 
            max( stature(x->lc) , stature(x->rc) );
    }

    template <typename T>
    void binTree<T>::updateHeightAbove(BinNodePosi(T) x)
    {
        while(x)
        {
            updateHeight(x);
            x = x->parent;
        }
    }

    //insert
    template <typename T>
    BinNodePosi(T) binTree<T>::insertAsRoot(T const & e)
    {
        _size = 1;
        _root = new BinNode<T> (e);
    }

    template <typename T>
    BinNodePosi(T) binTree<T>::insertAsLC(BinNodePosi(T) x, T const & e)
    {
        _size++; x->lc = new BinNode<T> (e);
        updateHeightAbove(x) ;
        return x->lc;
    }

    //remove 

    template <typename T>
    int binTree<T>::remove(BinNodePosi(T) x)
    {   //ASSERT x为二叉树中的合法位置
        FromParentTo(*x) = NULL;
        updateHeightAbove(x->parent);
        int n = removeAt(x);
        _size -= n;
        return n;
    }

    template <typename T> //删除二叉树中位置x处的节点及其后代，返回被删除节点的数值
    static int removeAt ( BinNodePosi(T) x ) { //assert: x为二叉树中的合法位置
        if ( !x ) return 0; //递归基：空树
        int n = 1 + removeAt ( x->lc ) + removeAt ( x->rc ); //递归释放左、右子树
        //release ( x->data );
        release ( x ); return n; //释放被摘除节点，并返回删除节点总数
    }    
}