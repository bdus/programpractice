#include <iostream>

using std::cout;
using std::endl;

// test node
// #include "listNode.h"
// int main()
// {
//     MyDSA::ListNode<int> node;
//     node.data = 0;
//     cout << node.data << endl;

//     MyDSA::ListNode<int> * nodepi = new MyDSA::ListNode<int>;
//     nodepi->data = 1;
//     cout << nodepi->data << endl;
//     delete nodepi;
//     return 0;
// }

//test list 
#include "list.h"

// int main()
// {
//     MyDSA::List<int> list;
//     cout << list.size() << endl;
//     return 0;
// }


template <typename T>
void test(MyDSA::ListNode<T>* list)
{
    while(list->succ != NULL)
    {
        cout << list->data << ' ';
        list = list->succ;        
    }
    cout << endl;
}