// url: https://www.codetree.ai/frequent-problems/go-on-the-rides/description
#include <iostream>
#include <vector>
#include <queue>
#define X first
#define Y second
using namespace std;
int n;
int dr[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1 } };
vector<vector<bool>> friends;
vector<vector<int>> grid;
typedef pair<int, int> P;
vector<int> order;
int main() {
	cin >> n;
	friends = vector<vector<bool>>(n * n + 1, vector<bool>(n * n + 1, false));
	grid = vector<vector<int>>(n, vector<int>(n, -1));
	int me, x1, x2, x3, x4;
	for (int i = 0; i < n * n; i++) {
		cin >> me >> x1 >> x2 >> x3 >> x4;
		friends[me][x1] = true;
		friends[me][x2] = true;
		friends[me][x3] = true;
		friends[me][x4] = true;
		order.push_back(me);
	}

	for (auto me : order) {
		int max_cnt = -1;
		int max_blank = -1;
		P idx = {-1 , -1};
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (grid[i][j] != -1) continue;
				int cnt = 0;
				int blank = 0;
				for (int k = 0; k < 4; k++) {
					int nx = i + dr[k][0];
					int ny = j + dr[k][1];
					if (nx < 0 or nx >= n or ny < 0 or ny >= n) continue;
					if (grid[nx][ny] == -1) blank++;
					else if (grid[nx][ny] != -1 and friends[me][grid[nx][ny]]) cnt++;
				}
				if (max_cnt < cnt) {
					max_cnt = cnt;
					max_blank = blank;
					idx = { i, j };
				}
				else if (max_cnt == cnt and max_blank < blank) {
					max_cnt = cnt;
					max_blank = blank;
					idx = { i, j };
				}
			}
		}
		grid[idx.X][idx.Y] = me;
	}
	int res = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int score = 1000;
			for (int k = 0; k < 4; k++) {
				int nx = i + dr[k][0];
				int ny = j + dr[k][1];
				if (nx < 0 or nx >= n or ny < 0 or ny >= n) {
					score /= 10;
					continue;
				}
				if (!friends[grid[i][j]][grid[nx][ny]]) score /= 10;
			}
			res += score;
		}
	}
	cout << res;
	return 0;
}