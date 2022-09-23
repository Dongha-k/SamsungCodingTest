#include <iostream>
#include <queue>
#include <string>
#include <vector>
#define X first
#define Y second

using namespace std;
typedef pair<int, int> P;

int dr[4][2] = { {1, 0}, {-1, 0}, {0, -1}, {0, 1} };
int n, m;
int zc = 0;
int lab[50][50];
vector<P> virusLst;
bool used[10] = { false, };
int idxs[10];
int answer = -1;

int bfs() {
	int days = 0;
	queue<P> q[2];
	vector<vector<int>> visited(n, vector<int>(n, false));
	for (int i = 0; i < m; i++) {
		q[0].push({ virusLst[idxs[i]].X, virusLst[idxs[i]].Y });
		visited[virusLst[idxs[i]].X][virusLst[idxs[i]].Y] = true;
	}
	int cnt = 0;
	while (!q[0].empty() or !q[1].empty()) {
		if (zc <= cnt) return days;
		while (!q[0].empty()) {
			P cur = q[0].front();
			q[0].pop();
			for (int i = 0; i < 4; i++) {
				int nx = cur.X + dr[i][0];
				int ny = cur.Y + dr[i][1];
				if (nx < 0 or ny < 0 or nx >= n or ny >= n) continue;
				if (visited[nx][ny]) continue;
				if (lab[nx][ny] == 1) continue;
				
				if (lab[nx][ny] == 0) cnt++;
				visited[nx][ny] = true;
				q[1].push({ nx, ny });
			}
		}
		while (!q[1].empty()) {
			q[0].push(q[1].front());
			q[1].pop();
		}
		days++;
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (lab[i][j] == 0 and !visited[i][j]) return -1;
		}
	}
	
	
	return days - 1;
}

void f(int k, int start) {
	if (k == m) {
		int cur = bfs();
		if (cur == -1) return;
		if (answer == -1) answer = cur;
		else if (answer > cur) answer = cur;
		//for (int i = 0; i < m; i++) {
		//	cout << "(" << virusLst[idxs[i]].X << ", " << virusLst[idxs[i]].Y << ") ";
		//}
		//cout << cur << '\n';
		
		return;
	}
	for (int i = start; i < virusLst.size(); i++) {
		if (!used[i]) {
			used[i] = true;
			idxs[k] = i;
			f(k + 1, i + 1);
			used[i] = false;
		}
	}
}

int main() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> lab[i][j];
			if (lab[i][j] == 0) zc++;
			if (lab[i][j] == 2) virusLst.push_back({ i, j });
		}
	}
	f(0, 0);
	cout << answer;
	return 0;
}