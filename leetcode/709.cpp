#include <iostream>
#include <string>
using namespace std;

string lower(string str) {
    for (int i = 0; i < str.size(); i++)
    {
        if(str[i] >= 'A' && str[i] <= 'Z')
            str[i] = str[i] - 'A' + 'a'; 
    }
    return str;
}
int main()
{
    string CAP = "LOWER";
    cout << lower(CAP) << endl;
    return 0;
}
