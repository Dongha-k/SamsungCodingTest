#include <iostream>
#include <string>
#include <queue>
#define X first
#define Y second
#define MAX_LEN 200
using namespace std;
typedef pair<int, int> P;
int dr[4][2] = { {1, 0}, {-1, 0}, {0, -1}, {0, 1} };

int main() {
	int board[MAX_LEN][MAX_LEN];
	bool visited[MAX_LEN][MAX_LEN];
	memset(visited, false, sizeof(visited));
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> board[i][j];
		}
	}

	// do BFS
	queue<P> q;
	q.push({ 0, 0 });
	visited[0][0] = true;
	while (!q.empty()) {
		P cur = q.front();
		cout << cur.X << ',' << cur.Y << ": " << board[cur.X][cur.Y] << '\n';
		q.pop();

		for (int i = 0; i < 4; i++) {
			int nx = cur.X + dr[i][0];
			int ny = cur.Y + dr[i][1];
			if (nx < 0 or nx >= n or ny < 0 or ny >= n) continue;
			if (visited[nx][ny]) continue;
			visited[nx][ny] = true;
			q.push({ nx, ny });
		}
	}
	return 0;
}