#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#define ABS(x) (((x) > 0)? (x) : -(x))
using namespace std;
typedef pair<int, int> P;
int dr[4][2] = { {0, -1}, {-1, 0} , {0, 1}, {1, 0} };
int n, m, k;
int office[20][20];
int A[20][20][2] = { 0, };
typedef struct {
	int X;
	int Y;
	int D;
} Node;
vector<Node> aircon;
int wall_dir[20][20][4] = { false, };
bool boundCheck(Node p) {
	int x = p.X;
	int y = p.Y;
	if (x < 0 or x >= n or y < 0 or y >= n) return false;
	else return true;
}

void blow(){
	
	for (Node elem : aircon) {
		int tmp[20][20] = { 0, };
		int nx = elem.X;
		int ny = elem.Y;
		int dir = elem.D;
		nx += dr[dir][0];
		ny += dr[dir][1];
		tmp[nx][ny] = 5;
		vector<Node> lst2(1, {nx, ny, 5});
		for (int i = 4; i > 0; i--) {
			vector<Node> lst;
			for (auto p : lst2) {
				if (p.D != i + 1) continue;
				const int x = p.X;
				const int y = p.Y;
				Node f = { x + dr[dir][0], y + dr[dir][1] , i };
				if (boundCheck(f) and !wall_dir[x][y][dir]) {
					lst.push_back(f);
					tmp[f.X][f.Y] = i;
				}

				Node l = { x + dr[(dir + 3) % 4][0], y + dr[(dir + 3) % 4][1] , i};
				if (boundCheck(l) and !wall_dir[x][y][(dir + 3) % 4]) {
					
					Node lf = { l.X + dr[dir][0], l.Y + dr[dir][1] , i };
					if (boundCheck(lf) and !wall_dir[l.X][l.Y][dir]) {
						lst.push_back(lf);
						tmp[lf.X][lf.Y] = i;
					}

				}

				Node r = { x + dr[(dir + 1) % 4][0], y + dr[(dir + 1) % 4][1] , i};
				if (boundCheck(r) and !wall_dir[x][y][(dir + 1) % 4]) {
					
					Node rf = { r.X + dr[dir][0], r.Y + dr[dir][1] , i };
					if (boundCheck(rf) and !wall_dir[r.X][r.Y][dir]) {
						lst.push_back(rf);
						tmp[rf.X][rf.Y] = i;
					}
				}
			}
			lst2.clear();
			lst2.insert(lst2.end(), lst.begin(), lst.end());
			lst.clear();
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				A[i][j][0] += tmp[i][j];
				A[i][j][1] = 0;
			}
		}
	}
}

void mix(){
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int x = i;
			int y = j;
			for (int k = 2; k < 4; k++) {
				int nx = x + dr[k][0];
				int ny = y + dr[k][1];
				if (nx < 0 or nx >= n or ny < 0 or ny >= n) continue;
				if (wall_dir[x][y][k]) continue;
				const int carry = (ABS(A[x][y][0] - A[nx][ny][0])) / 4;
				if (A[x][y][0] > A[nx][ny][0]) {
					A[x][y][1] -= carry;
					A[nx][ny][1] += carry;
				}
				else {
					A[x][y][1] += carry;
					A[nx][ny][1] -= carry;
				}
			}
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			A[i][j][0] += A[i][j][1];
			A[i][j][1] = 0;
		}
	}
}

void down() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == 0 or i == n - 1 or j == 0 or j == n - 1) A[i][j][0] = max(0, A[i][j][0] - 1);
		}
	}
}

bool check() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (office[i][j] == 1 and A[i][j][0] < k) return false;
		}
	}
	return true;
}
int main() {
	cin >> n >> m >> k;
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> office[i][j];
			if (office[i][j] >= 2) aircon.push_back({ i, j , office[i][j] - 2});
		}
	}
	for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) for (int k = 0; k < 4; k++) wall_dir[i][j][k] = false;
	for (int i = 0; i < m; i++) {
		int x, y, s;
		cin >> x >> y >> s;
		if (s == 0) {
			wall_dir[x - 1][y - 1][1] = true; // up
			int nx = x - 1 + dr[1][0];
			int ny = y - 1 + dr[1][1];
			if (nx < 0 or nx >= n or ny < 0 or ny >= n) continue;
			wall_dir[nx][ny][3] = true;
		}
		else {
			wall_dir[x - 1][y - 1][0] = true; // left
			int nx = x - 1 + dr[0][0];
			int ny = y - 1 + dr[0][1];
			if (nx < 0 or nx >= n or ny < 0 or ny >= n) continue;
			wall_dir[nx][ny][2] = true;
		}
	}
	for (int i = 1; i <= 100; i ++) {
		blow();
		mix();
		down();
		if (check()) {
			cout << i;
			return 0;
		}
	}
	cout << -1;
	return 0;
}