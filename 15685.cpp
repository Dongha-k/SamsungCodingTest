#include <iostream>
#include <vector>
#include <string>
using namespace std;
int dr[4][2] = { {1, 0}, {0, -1}, {-1, 0}, {0, 1} };
bool board[101][101] = { false, };

int main() {
	int n;
	vector<int> dirs;
	
	cin >> n;
	for (int t = 0; t < n; t++) {
		int x, y, d, g;
		dirs.clear();
		cin >> x >> y >> d >> g;
		

		// compose dir list
		dirs.push_back(d);
		board[x][y] = true;
		for (int i = 0; i < g; i++) {
			for (int j = dirs.size() - 1; j >= 0; j--) {
				dirs.push_back((dirs[j] + 1) % 4);
			}
		}

		for (auto dir : dirs) {
			int nx = x + dr[dir][0];
			int ny = y + dr[dir][1];
			x = nx;
			y = ny;
			board[x][y] = true;
		}
	}
	int res = 0;
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			if (board[i][j] and board[i + 1][j + 1] and board[i][j + 1] and board[i + 1][j]) res++;
		}
	}
	cout << res;
	return 0;
}