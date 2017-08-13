#include<iostream>
int main()
{
    std::cout << "$1.9" << std::endl;
    int sum = 0;
    for(int i = 50; i <= 100; i++)
    {
        sum += i;
    }
    std::cout << sum << "\n$1.10 "<<std::endl;
    for(int i = 10; i >= 0; i--)
    {
        std::cout << i << std::endl;
    }
    std::cout << "$1.11" <<std::endl;
    int v1 = 0, v2 = 0;
    std::cout << "Input two number" << std::endl;
    std::cin >> v1 >> v2;
    for(int i = v1; i <= v2; i++)
    {
        std::cout << i << std::endl;
    }
    
    
    return 0;
}
