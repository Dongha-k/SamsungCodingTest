#include <iostream>
#include <queue>
#include <algorithm>
#define X first
#define Y second
#define DEBUG 0
using namespace std;
typedef pair<int, int> P;
int n, m;
int dr[4][2] = { {1, 0}, {-1, 0}, {0, -1}, {0, 1} };
int ice[300][300];

void melt() {
	vector<vector<int>> temp(n, vector<int>(m, 0));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (ice[i][j] == 0) continue;
			
			for (int k = 0; k < 4; k++) {
				int nx = i + dr[k][0];
				int ny = j + dr[k][1];
				if (nx < 0 or nx >= n or ny < 0 or ny >= m) continue;
				if(ice[nx][ny] == 0) temp[i][j] ++;
			}
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			ice[i][j] = max(0, ice[i][j] - temp[i][j]);
		}
	}
}

void bfs(int x, int y, vector<vector<bool>>& visited) {
	queue<P> q;
	q.push({ x, y });
	visited[x][y] = true;

	while (!q.empty()) {
		P cur = q.front();
		q.pop();
		for (int i = 0; i < 4; i++) {
			int nx = cur.X + dr[i][0];
			int ny = cur.Y + dr[i][1];
			if (nx < 0 or nx >= n or ny < 0 or ny >= m) continue;
			if (ice[nx][ny] == 0) continue;
			if (visited[nx][ny]) continue;
			visited[nx][ny] = true;
			q.push({ nx, ny });			
		}
	}
}

int check() {
	vector<vector<bool>> visited(n, vector<bool>(m, false));
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (ice[i][j] != 0 and !visited[i][j]) {
				bfs(i, j, visited);
				cnt++;
			}
		}
	}
	return cnt;
}

int main() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> ice[i][j];
		}
	}
	int y = 0;
	while (true) {
		if (check() >= 2) break;
		else if (check() == 0) {
			y = 0;
			break;
		}
		melt();
#if DEBUG
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				cout << ice[i][j] << ' ';
			}
			cout << '\n';
		}
#endif
		y++;
	}
	cout << y;
	return 0;
}