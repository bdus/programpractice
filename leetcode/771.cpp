#include <iostream>
#include <string>
using namespace std;
int numjew(string J,string S)
{
    int num = 0;
    for(int i = 0; i < S.size(); i++)
    {
        for(int j = 0; j < J.size(); j++)
        {
            //if(J.substr(j,1) == S.substr(i,1))
            if(J[j] == S[i])
                num++;
        }
    }
    return num;
}
int main()
{
    string j = "aA";
    string s = "aAAbbb";
    cout << numjew(j,s) <<endl;

    return 0;
}
