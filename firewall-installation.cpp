// url: https://www.codetree.ai/frequent-problems/firewall-installation/description
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#define X first
#define Y second
using namespace std;
typedef pair<int, int> P;
int n, m;
int A[8][8];
int dr[4][2] = { {1, 0}, {0, -1}, {-1, 0}, {0, 1} };
vector<P> cand;
vector<int> idxs;
vector<bool> used;
vector<P> fires;
int bfs() {
	queue<P> q;
	vector<vector<bool>> visited(n, vector<bool>(m, false));
	for (P fire : fires) {
		q.push({ fire.X, fire.Y });
		visited[fire.X][fire.Y] = true;
	}

	while (!q.empty()) {
		P cur = q.front();
		q.pop();
		for (int i = 0; i < 4; i++) {
			int nx = cur.X + dr[i][0];
			int ny = cur.Y + dr[i][1];
			if (nx < 0 or nx >= n or ny < 0 or ny >= m) continue;
			if (visited[nx][ny]) continue;
			if (A[nx][ny] != 0) continue;
			visited[nx][ny] = true;
			q.push({ nx, ny });
		}
	}
	int res = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (!visited[i][j] and A[i][j] == 0) res++;
		}
	}
	return res;
}
int answer = 0;
void f(int k, int start) {
	if (k == 3) {
		for (int i = 0; i < 3; i++) A[cand[idxs[i]].X][cand[idxs[i]].Y] = 1;
		answer = max(answer, bfs());
		for (int i = 0; i < 3; i++) A[cand[idxs[i]].X][cand[idxs[i]].Y] = 0;
		return;

	}

	
	for (int i = start; i < cand.size(); i++) {
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
		for (int j = 0; j < m; j++) {
			cin >> A[i][j];
			if (A[i][j] == 0) {
				cand.push_back({ i, j });
				used.push_back(false);
				idxs.push_back(-1);
			}
			else if (A[i][j] == 2) fires.push_back({ i, j });
		}
	}
	f(0, 0);
	cout << answer;
	return 0;
}