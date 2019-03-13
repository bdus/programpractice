//#include <iostream>
#pragma once
#include "listNode.h"

namespace MyDSA
{
    template <typename T>
    class List
    {
    private:
        int _size;
        ListNodePosi(T) header;
        ListNodePosi(T) trailer;
    
    protected:
        void init();
        int clear();
        void copyNodes(ListNodePosi(T), int);

    public:
        List(){ init(); }
        List(List<T> const & L) {copyNodes(L,L._size); };
        List(List<T> const & L, int n) {copyNodes(L,n); };
        List(List<T> const & L, int r, int n) {copyNodes(L[r],n); };
        //List(T * A, Rank lo, Rank hi)；

        ~List();

        //
        Rank size() { return _size; };
        ListNodePosi(T) first() { return header->succ; };
        ListNodePosi(T) last() { return trailer->prev; };

        //write
        T & operator[] (Rank r) const;
        ListNodePosi(T) insertAsFirst( T const & e);
        ListNodePosi(T) insertAsLast( T const & e);
        ListNodePosi(T) insertAfter(ListNodePosi(T) p, T const & e);
        ListNodePosi(T) insertBefore(ListNodePosi(T) p, T const & e);
        ListNodePosi(T) push_back(T const & e) { return insertAsLast(e); };

        T remove (ListNodePosi(T) p);
        
    };
    
}

#include "list_implemention.h"