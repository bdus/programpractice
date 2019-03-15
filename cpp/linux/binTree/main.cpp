#include <iostream>
#include "binTree.h"
//#include "release.h"

using std::cout;
using std::endl;

int main()
{
    MyDSA::binTree<int> t;

    cout << "size : " << t.size() << endl; //0

    t.insertAsRoot(0);

    cout << "size : " << t.size() << endl; //1

    t.insertAsLC(t.root(),1);
    t.insertAsLC(t.root(),2);

    cout << "size : " << t.size() << endl; //3

    
    return 0;
}