// url: https://www.codetree.ai/frequent-problems/rotating-glacier/description
#include <iostream>
#include <algorithm>
#include <queue>
#define X first
#define Y second
using namespace std;
typedef pair<int, int> P;
int n, q, len;
int ice[64][64];
bool visited[64][64] = { false, };
int temp[64][64];
int dr[4][2] = { {1, 0}, {-1, 0}, {0, -1}, {0, 1} };

void copyAtoB(int A[][64], int ax, int ay, int B[][64], int bx, int by, int n) {
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			B[x + bx][y + by] = A[x + ax][y + ay];
		}
	}
}
void rotate(int level) {
	int sqaure_n = (1 << level);
	for (int i = 0; i < len; i += sqaure_n) {
		for (int j = 0; j < len; j += sqaure_n) {
			copyAtoB(ice,	i,					j,					temp,	i,					j + sqaure_n / 2,	sqaure_n / 2);
			copyAtoB(ice,	i + sqaure_n / 2,	j,					temp,	i,					j,					sqaure_n / 2);
			copyAtoB(ice,	i,					j + sqaure_n / 2,	temp,	i + sqaure_n / 2,	j + sqaure_n / 2,	sqaure_n / 2);
			copyAtoB(ice,	i + sqaure_n / 2,	j + sqaure_n / 2,	temp,	i + sqaure_n / 2,	j,					sqaure_n / 2);
		}
	}

	for (int i = 0; i < len; i++) {
		for (int j = 0; j < len; j++) {
			ice[i][j] = temp[i][j];
		}
	}
}

void melting() {
	for (int i = 0; i < len; i++) {
		for (int j = 0; j < len; j++) {
			int x = i;
			int y = j;
			int cnt = 0;
			for (int k = 0; k < 4; k++) {
				int nx = x + dr[k][0];
				int ny = y + dr[k][1];
				if (nx < 0 or nx >= len or ny < 0 or ny >= len) continue;
				if (ice[nx][ny] > 0) cnt++;
			}
			if (cnt < 3) temp[x][y] = -1;
			else temp[x][y] = 0;
		}
	}
	for (int i = 0; i < len; i++) {
		for (int j = 0; j < len; j++) {
			ice[i][j] = max(ice[i][j] + temp[i][j], 0);
		}
	}
}

int bfs(int x, int y) {
	int res = 0;
	queue<P> q;
	q.push({ x, y });
	visited[x][y] = true;
	
	while (!q.empty()) {
		P cur = q.front();
		res++;
		q.pop();
		for (int i = 0; i < 4; i++) {
			int nx = cur.X + dr[i][0];
			int ny = cur.Y + dr[i][1];
			if (nx < 0 or nx >= len or ny < 0 or ny >= len) continue;
			if (ice[nx][ny] == 0) continue;
			if (visited[nx][ny]) continue;
			visited[nx][ny] = true;
			q.push({ nx, ny });
		}
	}
	return res;
}

void show() {
	for (int i = 0; i < len; i++) {
		for (int j = 0; j < len; j++) {
			cout << ice[i][j] << '\t';
		}
		cout << '\n';
	}
	cout << '\n';

}
int main() {
	cin >> n >> q;
	len = (1 << n);
	for (int i = 0; i < len; i++) {
		for (int j = 0; j < len; j++) {
			cin >> ice[i][j];
		}
	}

	while (q--) {
		int level;
		cin >> level;
		if(level) rotate(level);
		melting();
	}
	int cnt = 0, breadth = 0;
	for (int i = 0; i < len; i++) {
		for (int j = 0; j < len; j++) {
			if (ice[i][j] > 0) {
				cnt+= ice[i][j];
				if (!visited[i][j]) {
					breadth = max(breadth, bfs(i, j));
				}
			}
		}
	}
	cout << cnt << '\n' << breadth;
	return 0;
}