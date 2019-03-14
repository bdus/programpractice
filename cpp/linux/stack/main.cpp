#include <iostream>
#include "stack.h"

template <typename T>
void test(const MyDSA::Vector<T> & v ) //, char s[] = "print ： ") 
{       
    std::cout << "\nprint ： ";
    for(int i = 0; i < v.size(); i++)
    {
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;    
}

template <typename T>
void test(MyDSA::ListNode<T>* list)
{
    while(list->succ != NULL)
    {
        std::cout << list->data << ' ';
        list = list->succ;        
    }
    std::cout << std::endl;
}

int main()
{
    //Vector Stack
    MyDSA::VStack<int> astk;
    astk.push(10);
    astk.pop();
    astk.push(9); 
    std::cout << astk.top() << std::endl;    
    test(astk);
    
    //List Stack
    MyDSA::LStack<int> bstk;
    bstk.push(10);    
    bstk.push(9);
    test(bstk.first());
    std::cout << bstk.pop() << std::endl;
    std::cout << bstk.top() << std::endl;
    test(bstk.first());

    return 0;
}