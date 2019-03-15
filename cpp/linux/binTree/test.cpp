#include <iostream>
#include "binNode.h"

int main()
{
    MyDSA::BinNode<int> a;

    a.size();
    a.insertAsLC(0);
    a.insertAsRC(1);
    std::cout << "size : " << a.size() << std::endl;

    return 0;
}