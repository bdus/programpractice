#include<iostream>
using namespace std;
int main()
{
    int currval = 0, val = 0;
    if(cin >> currval) {
        int cnt = 1;
        while(cin >> val) {
            if(val == currval)
                cnt++;
            else {
                cout << currval << " occours "  << cnt << " times " << endl; 
                cnt = 1;
                currval = val;
            }

        }

        cout << currval << " occours "  << cnt << " times " << endl; 
    }

    return 0;
}
