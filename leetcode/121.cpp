#include <iostream>
#include <vector>
using namespace std;
void print(vector<int>& a){
    for(int var:a) {
        cout << var << ' ';
    }
    cout << endl;
}

int maxProfit(vector<int>& line)
{
    if(0 == line.size())
        return 0;
    int max = 0;
    for(int i = 0; i < line.size(); i++)
    {
        for(int j = 0; j < i; j++)
        {
            int tmp = line[i] - line[j];
            if( tmp >  max)
            {
                max = tmp;
            }

        }
    }
    return max;
}

int main()
{
    vector<int> a = {7,1,5,3,6,4};
    vector<int> b = {7,6,4,3,1};
    vector<int> c = {};
    //print(a);
    cout << maxProfit(a) << endl;
    cout << maxProfit(b) << endl;
    cout << maxProfit(c) << endl;

    return 0;
}
