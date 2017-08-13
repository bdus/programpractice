/*************************************************************************
	> File Name: prog_vector.cpp
	> Author: 
	> Mail: 
	> Created Time: 2017年08月13日 星期日 11时06分48秒
 ************************************************************************/

#include<iostream>
#include<vector>
using namespace std;
int main()
{

    vector<int> v_int;

    for(int i = 0; i < 10; i++)
    {
        v_int.push_back(i);
    }

    for(auto &i: v_int)
    {
        i *= i;
    }
    // cout << v_int.size() << endl;
    for(int i : v_int)
    {
        cout << i << ' ';
    }
    
    cout << endl;

    for(auto i = v_int.begin(); i != v_int.end(); i++)
    {
        cout << *i << ' ';
    }

    cout << endl;


    return 0;
}
