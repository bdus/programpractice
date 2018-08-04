#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <set>

using namespace std;

string moscode[] = {".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--.."};

int fun(vector<string> &words)
{
    set<string> myset = {};
    for(int i = 0; i < words.size(); i++)
    {
        string s = words[i];//c_str();
        //cout << s << endl;
        string ss = "";
        for(int j = 0; j < s.size(); j++)
        {
            //cout << moscode[s[j]-'a'] << endl;
            ss = ss + moscode[s[j]-'a'];
        }
        myset.insert(ss);
    }
    return myset.size();
}


int main()
{
    vector<string> sss = {"gin", "zen", "gig", "msg"};
    //cout << moscode[0] << endl;
    //cout << sss[0] << endl;
    cout << fun(sss) << endl;

    return 0;
}
