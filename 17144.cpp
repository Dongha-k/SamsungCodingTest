#include <iostream>
#include <vector>
#include <deque>
#define X first
#define Y second
#define MAX_LEN 50
using namespace std;
typedef pair<int, int> P;
int r, c, t;
int room[MAX_LEN][MAX_LEN][2];
int machineTop = -1;
int machineBot = -1;
int dr[4][2] = { {1, 0}, {-1, 0}, {0, -1}, {0, 1} };
void spread() {
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			int a = room[i][j][0];
			if (a > 0) {
				int cnt = 0;
				for (int k = 0; k < 4; k++) {
					int nx = i + dr[k][0];
					int ny = j + dr[k][1];
					if (nx < 0 or nx >= r or ny < 0 or ny >= c) continue;
					if (room[nx][ny][0] == -1) continue;
					cnt++;
					room[nx][ny][1] += a / 5;
				}
				room[i][j][1] += a - cnt * (a / 5);
			}
		}
	}
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			room[i][j][0] = room[i][j][1];
			room[i][j][1] = 0;
		}
	}
	room[machineTop][0][0] = -1;
	room[machineBot][0][0] = -1;

}

void rotate() {
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			room[i][j][1] = room[i][j][0];
		}
	}
	// Top
	room[machineTop][0][0] = 0;
	for (int j = 1; j < c; j++) room[machineTop][j][1] = room[machineTop][j - 1][0];
	for (int i = machineTop - 1; i >= 0; i--) room[i][c - 1][1] = room[i + 1][c - 1][0];
	for (int j = c - 2; j >= 0; j--) room[0][j][1] = room[0][j + 1][0];
	for (int i = machineTop; i >= 1; i--) room[i][0][1] = room[i - 1][0][0];
	room[machineTop][0][1] = -1;

	// Bottom
	room[machineBot][0][0] = 0;
	for (int j = 1; j < c; j++) room[machineBot][j][1] = room[machineBot][j - 1][0];
	for (int i = machineBot + 1 ; i < r ; i ++) room[i][c - 1][1] = room[i - 1][c - 1][0];
	for (int j = c - 2; j >= 0; j--) room[r - 1][j][1] = room[r - 1][j + 1][0];
	for (int i = r - 2; i >= machineBot; i--) room[i][0][1] = room[i + 1][0][0];
	room[machineBot][0][1] = -1;

	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			room[i][j][0] = room[i][j][1];
			room[i][j][1] = 0;
		}
	}
}

int main() {
	cin >> r >> c >> t;
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			cin >> room[i][j][0];
			if (room[i][j][0] == -1) {
				if (machineTop == -1) machineTop = i;
				else machineBot = i;
			}
		}
	}

	while (t--) {
		spread(); // 미세먼지 확산
		rotate(); // 회전
	}
	int answer = 0;

	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			answer += room[i][j][0];
		}
	}
	cout << answer + 2;
	return 0;
}