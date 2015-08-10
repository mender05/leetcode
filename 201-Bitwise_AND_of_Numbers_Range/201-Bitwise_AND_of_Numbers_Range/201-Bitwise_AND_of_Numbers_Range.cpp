#include "stdafx.h"

#include <bitset>
using std::bitset;
class Solution {
public:
    int rangeBitwiseAnd(int m, int n) {
        bitset<sizeof(int) * 8> result(m);
        const int mask = 1;
        size_t i = 0;
        while (n) {
            if (mask & m) {
                if (m + 1 <= n && m + 1 > m) {
                    result.set(i, false);
                }
            }
            n = n >> 1;
            m = m >> 1;
            ++i;
        }
        return static_cast<int>(result.to_ulong());
    }
};

int main()
{
    Solution s;
    int a = s.rangeBitwiseAnd(6, 12);
    return 0;
}

