
namespace MyDSA
{
    template <typename T>
    BinNode<T> * BinNode<T>::insertAsLC(T const& e)
    {
        return this->lc = new BinNode(e,this);
    }

    template <typename T>
    BinNode<T> * BinNode<T>::insertAsRC(T const& e)
    {
        return this->rc = new BinNode(e,this);
    }

    template <typename T>
    int BinNode<T>::size()
    {
        int sz = 1;
        if( this->lc ) sz += lc->size();
        if( this->rc ) sz += rc->size();
        return sz;
    }

    // template <typename T>
    // BinNodePosi(T) BinNode<T>::succ()
    // {

    // }
        
} 