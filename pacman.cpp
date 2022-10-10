// url: https://www.codetree.ai/frequent-problems/pacman/description
#include <iostream>
#include <queue>
#include <stack>
#include <deque>
#include <vector>
#include <algorithm>

#define DEBUG 0
#define X first
#define Y second
using namespace std;
typedef pair<int, int> P;
int dr[8][2] = { {-1, 0}, {-1, -1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1} };
int m, t, r, c, d;
int pacX, pacY;
int monster[26][4][4][8] = { 0, };
bool tomb[26][4][4] = {false, };

void monster_move(int t) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 8; k++) {
				int x = i;
				int y = j;
				int d = k;
				bool flag = false;
				for (int l = 0; l < 8; l++) {
					int nx = x + dr[(d + l) % 8][0];
					int ny = y + dr[(d + l) % 8][1];
					if (0 <= nx and nx < 4 and 0 <= ny and ny < 4 and !(nx == pacX and ny == pacY)
						and (t < 2 or !tomb[t-2][nx][ny]) and (t < 1 or !tomb[t-1][nx][ny])) {
						monster[t][nx][ny][(d + l) % 8] += monster[t - 1][x][y][d];
						flag = true;
						break;
					}
				}
				if(!flag) monster[t][x][y][d] += monster[t - 1][x][y][d];
			}
		}
	}
}
int idxs[3];
int answer = -1;
int ansList[3];
void f(int k, int t) {
	if (k == 3) {
		int nx = pacX;
		int ny = pacY;
		
		bool check[4][4] = { false, };

		int res = 0;
		for (int i : idxs) {
			nx += dr[i][0];
			ny += dr[i][1];
			if (nx < 0 or nx >= 4 or ny < 0 or ny >= 4) return;
			if (check[nx][ny]) continue;
			check[nx][ny] = true;
			for (int j = 0; j < 8; j++) res += monster[t][nx][ny][j];
		}

		if (res > answer) {
			answer = res;
			for (int i = 0; i < 3; i++) {
				ansList[i] = idxs[i];
			}
		}
		return;
	}

	for (int i = 0; i < 8; i += 2) {
		idxs[k] = i;
		f(k + 1, t);
	}
}
void packman_move(int t) {
	answer = -1;
	f(0, t);
	bool visited[4][4] = { false, };
	for (auto i : ansList) {
		pacX += dr[i][0];
		pacY += dr[i][1];
		if (visited[pacX][pacY]) continue;
		visited[pacX][pacY] = true;
		for (int j = 0; j < 8; j++) {
			if (monster[t][pacX][pacY][j] > 0) {
				tomb[t][pacX][pacY] = true;
				monster[t][pacX][pacY][j] = 0;
			}
		}
	}
}

void hatch(int t) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 8; k++) {
				monster[t][i][j][k] += monster[t - 1][i][j][k];
			}
		}
	}
}


int rating(int t) {
	int res = 0;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 8; k++) {
				res += monster[t][i][j][k];
			}
		}
	}
	return res;
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin >> m >> t;
	cin >> r >> c;
	pacX = r - 1;
	pacY = c - 1;
	for (int i = 0; i < m; i++) {
		cin >> r >> c >> d;
		r--; c--; d--;
		monster[0][r][c][d] ++;
	}
	
	for (int i = 1; i <= t; i++) {
		monster_move(i);
		packman_move(i);
		hatch(i);
	}
	cout << rating(t);
	return 0;
}