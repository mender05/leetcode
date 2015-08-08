#include "stdafx.h"

#include <vector>
#include <string>
using std::vector;
using std::string;

class Solution {
public:
    struct Pos {
        Pos(size_t r, size_t c) : row(r), col(c) {}
        size_t row;
        size_t col;
    };
    vector<vector<string>> solveNQueens(int n);
private:
    void change_feasible_set(const Pos &pos, const int offset) {
        size_t r = pos.row, c = pos.col;
        board[r][c] += offset;
        for (size_t i = 1; r + i < N; ++i)
        {
            // 防止无符号整数运算溢出
            if (c >= i) {
                board[r + i][c - i] += offset;
            }
            if (c + i >= c && c + i >= i && c + i < N) {
                board[r + i][c + i] += offset;
            }
            board[r + i][c] += offset;
        }
    }

    /*棋盘大小*/
    size_t N;
    /*棋盘可行域，0表示可行，其他不可行*/
    vector<vector<int>> board;
};

vector<vector<string>> Solution::solveNQueens (int n) {
    N = n;
    board = std::move(vector<vector<int>>(N, vector<int>(N, 0)));
    /*维护的棋盘的可行域，该可行域是选择了queen里保存的序列以后的可行域*/
    /*添加queen的时候要修改可行域，减少queen的时候要恢复可行域*/
    vector<Pos> queen;
    vector<vector<string>> solutions;
    vector<Pos> stack;
    for (size_t i = 0; i < N; ++i) {
        stack.push_back(Pos(0, i));
    }
    while (!stack.empty()) {
        Pos pos = stack.back();
        //stack.pop_back();
        if (queen.empty() || pos.row > queen.back().row) {
            /*下探阶段*/
            /*下一层的点还没遍历完 */
            stack.pop_back();
            queen.push_back(pos);
            /*修改可行域，并将下一层可行点入栈*/
            change_feasible_set(pos, 1);
            for (size_t c = 0; pos.row + 1 < N && c < N; ++c) {
                if (board[pos.row + 1][c] == 0) {
                    stack.push_back(Pos(pos.row + 1, c));
                }
            }
            /*如果是最后一层的点，则保存结果*/
            if (pos.row == N - 1) {
                vector<string> result(N, string(N, '.'));
                for (auto &p : queen) {
                    result[p.row][p.col] = 'Q';
                }
                solutions.push_back(std::move(result));
            }
        }/*if*/
        else {
            /*回溯阶段*/
            /*下一层的点已经遍历完，更换为本层的另一点或上层的点*/
            if (!queen.empty() && pos.row <= queen.back().row) {
                change_feasible_set(queen.back(), -1);
                queen.pop_back();
            }
        }/*else*/
    }/*while*/
    return solutions;
}


int main()
{
    Solution s;
    int n = 9;
    s.solveNQueens(n);
    return 0;
}