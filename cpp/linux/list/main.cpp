#include <iostream>
#include "list.h"
using std::cout;
using std::endl;

#include "test.cpp"

int main()
{
    //init list
    MyDSA::List<int> list;
    cout << "size : " << list.size()   << endl;

    //insert 
    list.insertAsFirst(0);    
    list.insertAsLast(3);
    list.insertAfter(list.first(),1);
    list.insertBefore(list.last(),2);
    list.push_back(4);
    test<int>(list.first());
    cout << "size : " << list.size()   << endl;
    list.remove(list.first());
    
    test(list.first());
    cout << "size : " << list.size()   << endl;

       
    return 0;
}
