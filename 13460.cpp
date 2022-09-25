#include <iostream>
#include <queue>
#include <algorithm>

#define X first
#define Y second
#define DEBUG 1

using namespace std;

typedef pair<int, int> P;
int n, m;
int dr[4][2] = { {1, 0}, {-1, 0}, {0, -1}, {0, 1 } };
char board[10][10];
P R, B, O;
int answer = 987654321;

int bfs() {

}

int main() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> board[i][j];
			if (board[i][j] == 'R') {
				R = { i, j };
				board[i][j] = '.';
			}
			else if (board[i][j] == 'B') {
				B = { i, j };
				board[i][j] = '.';
			}
			else if (board[i][j] == 'O') O = { i, j };
		}
	}
	


	return 0;
}