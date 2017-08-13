#include<iostream>
int main()
{
    int sum = 0, vol = 50;
    while(vol <= 100)
    {
        sum += vol;
        vol++;
    }
    std::cout << "The sum of 50 to 100 inclusive is " <<sum<<std::endl;
    return 0;
}
