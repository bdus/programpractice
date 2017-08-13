#include<iostream>
using namespace std;
void swap1(int *a, int *b)
{
    (*a) = (*a) ^ (*b);
    (*b) = (*a) ^ (*b);
    (*a) = (*a) ^ (*b);

}
void swap2(int &a, int &b)
{
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;
}
int main()
{
    int a = 1 , b = 2;
    cout << "1 a = " <<a<<" b = "<<b<<endl;
    swap1(&a,&b);
    cout << "2 a = " <<a<<" b = "<<b<<endl;
    swap2(a,b);
    cout << "3 a = " <<a<<" b = "<<b<<endl;

    return 0;
}
