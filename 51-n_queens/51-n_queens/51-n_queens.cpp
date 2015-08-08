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
            // ��ֹ�޷��������������
            if (c >= i) {
                board[r + i][c - i] += offset;
            }
            if (c + i >= c && c + i >= i && c + i < N) {
                board[r + i][c + i] += offset;
            }
            board[r + i][c] += offset;
        }
    }

    /*���̴�С*/
    size_t N;
    /*���̿�����0��ʾ���У�����������*/
    vector<vector<int>> board;
};

vector<vector<string>> Solution::solveNQueens (int n) {
    N = n;
    board = std::move(vector<vector<int>>(N, vector<int>(N, 0)));
    /*ά�������̵Ŀ����򣬸ÿ�������ѡ����queen�ﱣ��������Ժ�Ŀ�����*/
    /*���queen��ʱ��Ҫ�޸Ŀ����򣬼���queen��ʱ��Ҫ�ָ�������*/
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
            /*��̽�׶�*/
            /*��һ��ĵ㻹û������ */
            stack.pop_back();
            queen.push_back(pos);
            /*�޸Ŀ����򣬲�����һ����е���ջ*/
            change_feasible_set(pos, 1);
            for (size_t c = 0; pos.row + 1 < N && c < N; ++c) {
                if (board[pos.row + 1][c] == 0) {
                    stack.push_back(Pos(pos.row + 1, c));
                }
            }
            /*��������һ��ĵ㣬�򱣴���*/
            if (pos.row == N - 1) {
                vector<string> result(N, string(N, '.'));
                for (auto &p : queen) {
                    result[p.row][p.col] = 'Q';
                }
                solutions.push_back(std::move(result));
            }
        }/*if*/
        else {
            /*���ݽ׶�*/
            /*��һ��ĵ��Ѿ������꣬����Ϊ�������һ����ϲ�ĵ�*/
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