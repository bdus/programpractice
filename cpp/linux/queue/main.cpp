#include <iostream>
#include "queue.h"

template <typename T>
void test(MyDSA::List<T> & list)
{
    MyDSA::ListNode<T> * l = list.first();
    std::cout << "queue [end=>begin] :";
    while(l->succ != NULL)
    {
        std::cout << l->data << ' ';
        l = l->succ;
    }
    std::cout << std::endl;
}
int main()
{
    MyDSA::Queue<int> aq;
    aq.enqueue(0); // :0
    aq.enqueue(1); // :01
    test(aq);
    aq.enqueue(2); // :012
    std::cout <<"unqueue : " <<  aq.dequeue() << std::endl;
    test(aq); //:12

    return 0;
}
