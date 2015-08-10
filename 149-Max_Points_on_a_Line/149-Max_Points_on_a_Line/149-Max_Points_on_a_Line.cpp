#include "stdafx.h"

/**
* Definition for a point.
* struct Point {
*     int x;
*     int y;
*     Point() : x(0), y(0) {}
*     Point(int a, int b) : x(a), y(b) {}
* };
*/

#include<vector>
#include <set>
#include <cstdlib>
using std::vector;
using std::multiset;
using std::pair;

struct Point {
    int x;
    int y;
    Point() : x(0), y(0) {}
    Point(int a, int b) : x(a), y(b) {}
};

class Solution {
public:
    int maxPoints(vector<Point> &points) {
        int n = points.size();
        if (points.size() < 3) {
            return  n;
        }
        int mx = 2;
        for (const auto &origin : points) {
            /*与origin重复的点的个数（包括origin），以及与origin组成竖直直线的点的个数（不包括origin）*/
           int duplicate = 0;
           int vertical = 0;
           int horizontal = 0;
           int local_mx = 0;
           multiset<pair<int, int>> mset;
           for (const auto &other : points) {
               if (origin.x == other.x && origin.y == other.y) {
                   /*必然会遇到origin自己*/
                   ++duplicate;
               }
               else if (origin.x == other.x) {
                   ++vertical;
               }
               else if (origin.y == other.y) {
                   ++horizontal;
               }
               else {
                   int a = origin.x - other.x, b = origin.y - other.y;
                   int c = gcd(b, a);
                   mset.insert(pair<int, int>(a/c, b/c));
               }
           } /*for other*/
           local_mx = vertical > local_mx ? vertical : local_mx;
           local_mx = horizontal > local_mx ? horizontal : local_mx;
           for (const auto &k : mset) {
               int count = mset.count(k);
               if (count > local_mx) {
                   local_mx = count;
               }
           }
           local_mx += duplicate;
           if (local_mx > mx) {
               mx = local_mx;
           }
        } /*for origin*/
        return mx;
    }
private:
    int gcd(int a, int b) {
        if (abs(b) > abs(a)) {
            std::swap(a, b);
        }
        int c = a % b;
        while (c) {
            a = b;
            b = c;
            c = a % b;
        }
        return b;
    }
};

int main()
{
    Solution s;
    //vector<Point> vec = { Point(1,2), Point(0,0), Point(9,18), Point(-1, 4), Point(0,9), Point(0,0) };
    vector<Point> vec = { Point(0,0), Point(1,1), Point(1,-1)};
    int m = s.maxPoints(vec);
    return 0;
}

