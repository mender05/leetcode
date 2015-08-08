#include "stdafx.h"

#include <bitset>
using std::bitset;

class Solution {
public:
    bool isPowerOfTwo(int n) {
        bitset<sizeof(long long) * 8> i(n);
        return i.count() == 1 ? true : false;
    }
};


int main()
{   
    Solution s;
    bool r = s.isPowerOfTwo(0);
    return 0;
}

