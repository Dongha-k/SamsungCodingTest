#include <iostream>
#include <vector>
using namespace std;
int n, m;
int x, y;
int k;
int board[20][20];
int dice[6][2] = { 0, };
int dr[5][2] = { {}, {0, 1}, {0, -1}, {-1, 0}, {1, 0} };
int main() {
	cin >> n >> m >> x >> y >> k;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> board[i][j];
		}
	}
	
	for (int i = 0; i < k; i++) {
		int cmd;
		cin >> cmd;
		int nx = x + dr[cmd][0];
		int ny = y + dr[cmd][1];
		if (nx < 0 or nx >= n or ny < 0 or ny >= m) continue;
		x = nx;
		y = ny;
		for (int i = 0; i < 6; i++) dice[i][1] = dice[i][0]; // 1에 대입할 값 저장

		if (cmd == 1) { // east
			dice[0][0] = dice[2][1];// v
			dice[1][0] = dice[4][1];// v
			dice[2][0] = dice[1][1];// v
			dice[3][0] = dice[3][1];// v
			dice[4][0] = dice[0][1];// v
			dice[5][0] = dice[5][1];// v
		}
		else if (cmd == 2) { // west
			dice[0][0] = dice[4][1];// v
			dice[1][0] = dice[2][1];// v
			dice[2][0] = dice[0][1];// v
			dice[3][0] = dice[3][1];// v
			dice[4][0] = dice[1][1];// v
			dice[5][0] = dice[5][1];// v
		}
		else if (cmd == 3) { // north
			dice[0][0] = dice[3][1];// v
			dice[1][0] = dice[5][1];// v 
			dice[2][0] = dice[2][1];// v
			dice[3][0] = dice[1][1];// v
			dice[4][0] = dice[4][1];// v
			dice[5][0] = dice[0][1];// v
		}
		else { // south
			dice[0][0] = dice[5][1];// v
			dice[1][0] = dice[3][1];// v
			dice[2][0] = dice[2][1];// v
			dice[3][0] = dice[0][1];// v
			dice[4][0] = dice[4][1];// v
			dice[5][0] = dice[1][1];// v
		}
		if (board[x][y] == 0) board[x][y] = dice[1][0];
		else{
			dice[1][0] = board[x][y];
			board[x][y] = 0;
		}
		cout << dice[0][0] << '\n';
	}


	return 0;
}