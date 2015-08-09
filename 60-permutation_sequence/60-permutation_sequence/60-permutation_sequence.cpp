#include "stdafx.h"

#include <string>
#include <vector>
#include <sstream>
#include <set>
using std::string;
using std::vector;
using std::set;
using std::stringstream;

class Solution {
public:
    string getPermutation(int n, int k) {
        /* 保存第k个排列 */
        vector<int> result;
        /* 保存待确定的数字 */
        set<int> digitals;;
        /* 保存阶乘结果 */
        vector<int> factorials;
        for (int i = 0; i < n; ++i) {
            digitals.insert(i + 1);
        }
        find_min_digital(k, factorials);
        /* 要得到第k个排列，也许不需要n位数 */
        for (int i = 0; i < n - factorials.size(); ++i) {
            result.push_back(i + 1);
            digitals.erase(i + 1);
        }
        /* 在n个数的排列中寻找第k大的排列，转化为了，*
         * 在digtals.size()个数的排列中寻找第k大的排列 */
        /* 后面将确定digitals里数字的位置 */
        while (!digitals.empty()) {
            int fac = factorials[digitals.size() - 1];
            int mod = k % fac;
            int pos = k / fac + (mod ? 1 : 0);
            auto iter_pos = find_the_digital(digitals, pos);
            result.emplace_back(std::move(*iter_pos));
            digitals.erase(iter_pos);
            k = mod ? mod : fac;
        }
        return result_to_string(result);
    }
private:
    /* 找到x，使x! >= k。同时保存中间计算的各个阶乘结果 */
    void find_min_digital(const int k, vector<int> &factorials) {
        /* 0!==1 */
        factorials.push_back(1);
        int x = 1, a = 1;
        while (a < k) {
            factorials.push_back(a);
            ++x;
            a *= x;
        }
        /* 最后一个阶乘结果不放进factorials中，因为添加了0! *
         * 所以，factorials.size()就是得到第k大排列数需要的数字个数 *
         * factorals[i] == i! */
    }
    /* 寻找digtials里的第pos个数字 */
    set<int>::iterator find_the_digital(const set<int> &digitals, int pos) {
        auto iter = digitals.cbegin();
        while (--pos) {
            ++iter;
        }
        return iter;
    }
    string result_to_string(const vector<int> &result) {
        stringstream ss;
        for (const auto &i : result) {
            ss << i;
        }
        return ss.str();
    }
};

int main()
{
    Solution s;
    string i = s.getPermutation(6, 16);
    return 0;
}

