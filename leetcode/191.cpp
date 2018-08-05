#include <iostream>
using namespace std;
class Solution {
public:
    int hammingDistance(int x, int y) {
        int z = x ^ y;
        int cnt = 0;
        /*for(int i = 1; i <= z; i = i << 1) {
            if(z & i)
                cnt++;
        }*/
        for(cnt = 0; z > 0; z = z >> 1)
            cnt += z & 1;

        return cnt;
    }
    int hammingWeight(uint32_t n) {
        int cnt = 0;
        for(int i = 0; i < 32; i++) {
            if( ((n >> i )& 1 ) != 0)
                cnt++;
        }
        return cnt;
    }
};

int main()
{
    Solution ss;
    //cout << ss.hammingDistance(1,4) <<endl;
    //cout << ss.hammingDistance(1,3) <<endl;

    //cout << ss.hammingDistance(680142203,1111953568) <<endl;
    cout << ss.hammingWeight(11) << endl;
    cout << ss.hammingWeight(128) << endl;
    cout << ss.hammingWeight(1024) << endl;
}
