#include<iostream>
int main()
{
    int sum = 0, i = 0;
    std::cout << "Input numbers:" << std::endl;
    while( std::cin >> i)
    {
        sum += i;
    }
    std::cout << sum <<std::endl;


    return 0;
}
