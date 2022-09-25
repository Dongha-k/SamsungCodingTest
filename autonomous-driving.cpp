// url: https://www.codetree.ai/frequent-problems/autonomous-driving/description

#include <iostream>
#include <vector>
#define DEBUG 0
using namespace std;
int n, m;
int x, y, d;
int dr[4][2] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };
int A[50][50];
int area = 0;
bool visited[50][50] = { false, };
bool move_left() {
	d = ((d - 1) + 4) % 4;
	int nx = x + dr[d][0];
	int ny = y + dr[d][1];
	if (nx < 0 or nx >= n or ny < 0 or ny >= m) return false;
	if (A[nx][ny] == 1) return false;
	if (visited[nx][ny]) return false;
	x = nx;
	y = ny;
	visited[x][y] = true;
	area++;
	return true;
}


bool move_back() {
	int nx = x - dr[d][0];
	int ny = y - dr[d][1];
	if (nx < 0 or nx >= n or ny < 0 or ny >= m) return false;
	if (A[nx][ny] == 1) return false;
	x = nx;
	y = ny;
	if (!visited[x][y]) {
		visited[x][y] = true;
		area++;
	}
	return true;
}


int main() {
	cin >> n >> m;
	cin >> x >> y >> d;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> A[i][j];
		}
	}
	visited[x][y] = true;
	area++;
	while (true) {

		bool success = false;
		for (int i = 0; i < 4; i++) {
			if (move_left()) {
				success = true;
				break;
			}
		}
		if (!success) {
			if (move_back()) continue;
			else break;	
		}
	}
#if DEBUG

	cout << '\n';
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << visited[i][j] << ' ';

		}
		cout << '\n';
	}
#endif
	cout << area << '\n';;

	return 0;
}