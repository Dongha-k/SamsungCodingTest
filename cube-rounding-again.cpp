//url: https://www.codetree.ai/frequent-problems/cube-rounding-again/description
#include <iostream>
#include <queue>
#define X first
#define Y second
using namespace std;
typedef pair<int, int> P;
int dr[4][2] = { {0, 1}, {-1, 0}, {0, -1}, {1, 0} };
int grid[20][20];
bool visited[20][20];
int n, m;
int bfs(int x, int y) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			visited[i][j] = false;
		}
	}
	int num = grid[x][y];
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
			if (nx < 0 or nx >= n or ny < 0 or ny >= n) continue;
			if (grid[nx][ny] != num) continue;
			if (visited[nx][ny]) continue;
			visited[nx][ny] = true;
			q.push({ nx, ny });
		}
	}
	return res * num;
}
int main() {
	
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j ++) {
			cin >> grid[i][j];
		}
	}
	int x = 0;
	int y = 0;
	int dir = 0;
	int score = 0;
	int dice[6] = {6, 4, 2, 3, 5, 1};
	int after[6];
	while (m--) {
		switch (dir){
		case 0:
			after[0] = dice[3];
			after[1] = dice[0];
			after[2] = dice[2];
			after[3] = dice[5];
			after[4] = dice[4];
			after[5] = dice[1];
			break;
		case 1:
			after[0] = dice[4];
			after[1] = dice[1];
			after[2] = dice[0];
			after[3] = dice[3];
			after[4] = dice[5];
			after[5] = dice[2];
			break;
		case 2:
			after[0] = dice[1];
			after[1] = dice[5];
			after[2] = dice[2];
			after[3] = dice[0];
			after[4] = dice[4];
			after[5] = dice[3];
			break;
		case 3:
			after[0] = dice[2];
			after[1] = dice[1];
			after[2] = dice[5];
			after[3] = dice[3];
			after[4] = dice[0];
			after[5] = dice[4];
			break;
		}

		for (int i = 0; i < 6; i++) dice[i] = after[i];
		
		x += dr[dir][0];
		y += dr[dir][1];
		score += bfs(x, y);
		// change dir
		if (dice[0] > grid[x][y]) dir = (dir + 3) % 4;
		else if (dice[0] < grid[x][y]) dir = (dir + 1) % 4;
		int nx = x + dr[dir][0];
		int ny = y + dr[dir][1];
		if (nx < 0 or nx >= n or ny < 0 or ny >= n) dir = (dir + 2) % 4;
	}
	cout << score;
	return 0;
}
