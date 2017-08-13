/*************************************************************************
	> File Name: prog_readCapicity.cpp
	> Author: 
	> Mail: 
	> Created Time: 2017年08月13日 星期日 19时38分49秒
 ************************************************************************/

#include<iostream>
#include<vector>
#include<string>
using namespace std;
int main()
{
    vector<string> v_str;

    string str;
    
    while(cin >> str)
    {
        for(auto &c : str)
            c = toupper(c);

        v_str.push_back(str);
    }

    for(auto i : v_str)
        cout << i << endl;

    return 0;
}
