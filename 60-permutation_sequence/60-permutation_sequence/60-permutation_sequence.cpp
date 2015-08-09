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
        /* �����k������ */
        vector<int> result;
        /* �����ȷ�������� */
        set<int> digitals;;
        /* ����׳˽�� */
        vector<int> factorials;
        for (int i = 0; i < n; ++i) {
            digitals.insert(i + 1);
        }
        find_min_digital(k, factorials);
        /* Ҫ�õ���k�����У�Ҳ����Ҫnλ�� */
        for (int i = 0; i < n - factorials.size(); ++i) {
            result.push_back(i + 1);
            digitals.erase(i + 1);
        }
        /* ��n������������Ѱ�ҵ�k������У�ת��Ϊ�ˣ�*
         * ��digtals.size()������������Ѱ�ҵ�k������� */
        /* ���潫ȷ��digitals�����ֵ�λ�� */
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
    /* �ҵ�x��ʹx! >= k��ͬʱ�����м����ĸ����׳˽�� */
    void find_min_digital(const int k, vector<int> &factorials) {
        /* 0!==1 */
        factorials.push_back(1);
        int x = 1, a = 1;
        while (a < k) {
            factorials.push_back(a);
            ++x;
            a *= x;
        }
        /* ���һ���׳˽�����Ž�factorials�У���Ϊ�����0! *
         * ���ԣ�factorials.size()���ǵõ���k����������Ҫ�����ָ��� *
         * factorals[i] == i! */
    }
    /* Ѱ��digtials��ĵ�pos������ */
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

