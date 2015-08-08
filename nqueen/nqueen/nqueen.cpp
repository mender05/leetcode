// nqueen.cpp : �������̨Ӧ�ó������ڵ㡣
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
		/*Ѱ�ұ���Ŀ���ֵ*/
		for (size_t c = 0; c < N; ++c) {
			if (board[r][c]) {
				/*�п��еĿռ�*/
				queen.push_back(c);
				/*��c�У��Լ�c�ĶԽ����ϵ�λ����Ϊ����������*/
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
				/*������һ�㴦��*/
				find_all_solution(r + 1);
				/*c�е������������ϣ���ԭ*/
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
					/*���һ�㣬������*/
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