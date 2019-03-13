#include "Vector.h"
#include <iostream>
#include <time.h>
#include <cstdlib>

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
template <typename T, int N>
void test(MyDSA::Vector<T> & v, char const ( & s)[N]) //char & s[] 数组没有引用  char (& s)[5] https://www.cnblogs.com/ike_li/p/7339011.html 
{
    std::cout << "\n" << s;
    for(int i = 0; i < v.size(); i++)
    {
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;    
}

template <typename T>
void swap(T &left, T &right)
{
    T tmp = left;
    left = right;
    right = tmp;
}

template <typename T>
void permute(MyDSA::Vector<T> & V)
{
    srand(time(0));
    for(int i = 0; i < V.size(); i++)
    {
        swap<T>(V[i],V[rand() % (i+1) ]);
    }
}