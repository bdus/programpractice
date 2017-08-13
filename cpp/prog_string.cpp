/*************************************************************************
	> File Name: prog_string.cpp
	> Author: 
	> Mail: 
	> Created Time: 2017年08月09日 星期三 10时38分34秒
 ************************************************************************/

#include<iostream>
#include<string>
//using std::string;
//using std::cout; using std::cin; using std::endl;
using namespace std;

int main()
{
    //string s(10,'c');
    int cnt_line = 0,cnt_words = 0;
    string word,line;

    /*while(cin >> word)
    { 
        cout << word << endl;
    }*/

    while(getline(cin,line))
    {
        cout << line << endl;
        cnt_line++;
        while(line >> word)
        {
            cout << word <<endl;
            cnt_words++;
        }

    }

    return 0;
}
