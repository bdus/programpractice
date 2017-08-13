/*************************************************************************
	> File Name: prog_3.20.cpp
	> Author: 
	> Mail: 
	> Created Time: 2017年08月13日 星期日 20时21分04秒
 ************************************************************************/

#include<iostream>
#include<vector>
using namespace std;
int main()
{
    vector<int>  vi;
    int i;

    while(cin >> i)
    {
        vi.push_back(i);
    }
    for( auto b = vi.begin(), e = vi.end()-1, mid = b + (e-b)/2, j = b;
     j != mid; j++ , e--)
    {
        cout << (*j) + (*e) << ' ';
    }
    cout << endl;

    return 0;
}

