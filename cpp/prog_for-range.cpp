/*************************************************************************
	> File Name: prog_for-range.cpp
	> Author: 
	> Mail: 
	> Created Time: 2017年08月11日 星期五 20时17分09秒
 ************************************************************************/

#include<iostream>
#include<string>
using namespace std;

int main()
{
    string str("123456");

    for (char c : str)
        cout << c << endl;

    return 0;
}

