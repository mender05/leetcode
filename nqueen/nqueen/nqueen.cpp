// nqueen.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <vector>
#include <string>
#include <bitset>
using std::vector;
using std::string;
using std::bitset;
class Solution {
public:
	vector<vector<string>> solveNQueens(int n) {
		N = n;
		board = std::move(vector<vector<bool>>(N, vector<bool>(N, true)));
		find_all_solution(0);
		return solutions;
	}
	vector<vector<string>> solutions;
private:
	void find_all_solution(const size_t r);
	size_t N;
	vector<size_t> queen;
	vector<vector<bool>> board;
};

void Solution::find_all_solution (const size_t r) {
	if (r < N) {
		/*寻找本层的可能值*/
		for (size_t c = 0; c < N; ++c) {
			if (board[r][c]) {
				/*有可行的空间*/
				queen.push_back(c);
				/*把c列，以及c的对角线上的位置设为不可行区域*/
				board[r][c] = false;
				for (size_t i = 1; r + i < N; ++i)
				{
					if (c >= i) {
						board[r + i][c - i] = false;
					}
					if (c + i >= c && c + i >= i && c + i < N) {
						board[r + i][c + i] = false;
					}
					board[r + i][c] = false;
				}
				/*交给下一层处理*/
				find_all_solution(r + 1);
				/*c列的情况已收索完毕，还原*/
				board[r][c] = true;
				for (size_t i = 1; r + i < N; ++i)
				{
					if (c >= i) {
						board[r + i][c - i] = true;
					}
					if (c + i >= c && c + i >= i && c + i < N) {
						board[r + i][c + i] = true;
					}
					board[r + i][c] = true;
				}
				if (r == N - 1) {
					/*最后一层，输出结果*/
					vector<string> result(N, string(N, '.'));
					for (size_t i = 0; i < N; ++i) {
						result[i][queen[i]] = 'Q';
					}
					solutions.push_back(std::move(result));
				}
				queen.pop_back();
			} // if board
		} // for c
	} // if r<N
}


int main()
{
	Solution s;
	int n = 8;
	s.solveNQueens(n);
	return 0;
}