#include <iostream>
#include "Vector.h"

using std::cout;
using std::endl;

//
#include "test.cpp"

int main()
{
    std::cout << "hello" << std::endl;
    MyDSA::Vector<int> avector;
    std::cout << "size : " << avector.size() << std::endl;
    
    char A[] = "0123";
    MyDSA::Vector<char> b(A,4);
    test(b);
    MyDSA::Vector<char> c(b);
    test(c);
    permute(b);
    test(b);
    cout << "c order: " << c.disordered() << ", b: " << b.disordered() << endl;
       
    b.insert(0,65);
    b.insert(b.size(),76);
    b.push_back(78);
    test(b);
    cout << "b find L:" << b.find('L') << " , b find 9 :" << b.find('9') << endl;
    b.erase(2,b.size());
    test(b);
    b.push_back('F');
    b.push_back('G');
    b.push_back('H');
    test(b);
    b.erase(0);
    test(b,"b.erase(0) : ");
    cout << b.pop_back() << endl;
    test(b);
    return 0;
}
