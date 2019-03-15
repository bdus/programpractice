#include "binNode.h"

namespace MyDSA
{
    template <typename T>
    class binTree
    {
    protected:
        int _size;
        BinNodePosi(T) _root;
        virtual int updateHeight( BinNodePosi(T) x);
        void updateHeightAbove( BinNodePosi(T) x);

    public:
        
        binTree() : _size(0), _root(NULL) {}
        ~binTree() { if(0 < _size) remove(_root); }

        int size() const { return _size; }
        bool empty() const {return !_root; }
        BinNodePosi(T) root() const {return _root;}

        BinNodePosi(T) insertAsRoot(T const& e);
        BinNodePosi(T) insertAsLC( BinNodePosi(T) x, T const & e);
        BinNodePosi(T) insertAsRC( BinNodePosi(T) x, T const & e);
        //BinNodePosi(T) attachAsLC( BinNodePosi(T) x, binTree<T> * &T );
        //BinNodePosi(T) attachAsRC( BinNodePosi(T) x, binTree<T> * &T );

        int remove(BinNodePosi(T) x);


    };
}

#include "binTree_implemention.h"