//url: https://www.codetree.ai/frequent-problems/artistry/description
#include <iostream>
#include <queue>
#define DEBUG 0
#define X first
#define Y second
using namespace std;
typedef pair<int, int> P;
int n;
int A[30][30];
int label[30][30];
int adj[1000][1000];
int g = 0;
int dr[4][2] = { {1, 0}, {-1, 0}, {0, -1}, {0, 1} };
vector<P> heads;
vector<int> areas;
int bfs(int x, int y, int g) {
	queue<P> q;
	int res = 0;
	q.push({ x, y });
	label[x][y] = g;
	while (!q.empty()) {
		P cur = q.front();
		res++;
		q.pop();
		for (int i = 0; i < 4; i++) {
			int nx = cur.X + dr[i][0];
			int ny = cur.Y + dr[i][1];
			if (nx < 0 or nx >= n or ny < 0 or ny >= n) continue;
			if (A[nx][ny] != A[x][y]) continue;
			if (label[nx][ny] != -1) continue;
			label[nx][ny] = g;
			q.push({ nx, ny });
		}
	}
	return res;
}

int score() {
	for (int i = 0; i < g; i++) {
		for (int j = 0; j < g; j++) {
			adj[i][j] = 0;
		}
	}

	for (int i = 0; i < heads.size(); i++) {
		P head = heads[i];
		bool checked[30][30] = { false, };
		queue<P> q;
		q.push(head);
		checked[head.X][head.Y] = true;
		while (!q.empty()) {
			P cur = q.front();
			q.pop();
			for (int j = 0; j < 4; j++) {
				int nx = cur.X + dr[j][0];
				int ny = cur.Y + dr[j][1];
				if (nx < 0 or nx >= n or ny < 0 or ny >= n) continue;
				if (checked[nx][ny]) continue;
				if (label[nx][ny] != i) adj[i][label[nx][ny]] ++;
				else {
					checked[nx][ny] = true;
					q.push({ nx, ny });
				}
			}
		}
	}
	
	int res = 0;
	for (int i = 0; i < g; i++) {
		for (int j = i + 1; j < g; j++) {
			int temp = (areas[i] + areas[j]) * A[heads[i].X][heads[i].Y] * A[heads[j].X][heads[j].Y] * adj[i][j];
			res += temp;
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			label[i][j] = -1;
		}
	}
	return res;
}

void RotateSquare(int sx, int sy, int square_n, int next_arr[][30], int arr[][30]) {
	for (int x = sx; x < sx + square_n; x++) {
		for (int y = sy; y < sy + square_n; y++) {
			int ox = x - sx, oy = y - sy;
			int rx = oy, ry = square_n - ox - 1;
			next_arr[rx + sx][ry + sy] = arr[x][y];
		}
	}
}

void rotate() {
	int temp[30][30];

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			temp[i][j] = A[i][j];
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (j == n / 2) temp[j][i] = A[i][j];
			else if (i == n / 2) temp[n - j - 1][i] = A[i][j];
		}
	}


	int sqaure_n = n / 2;

	RotateSquare(0, 0, sqaure_n, temp, A);
	RotateSquare(0, sqaure_n + 1, sqaure_n, temp, A);
	RotateSquare(sqaure_n + 1, 0, sqaure_n, temp, A);
	RotateSquare(sqaure_n + 1, sqaure_n + 1, sqaure_n, temp, A);


	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			A[i][j] = temp[i][j];
		}
	}
}


int main() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> A[i][j];
			label[i][j] = -1;
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (label[i][j] == -1) {
				areas.push_back(bfs(i, j, g++));
				heads.push_back({ i, j });
			}
		}
	}


	int res = score();
	//cout << res << '\n';

	for (int i = 0; i < 3; i++) {
		areas.clear();
		heads.clear();
		g = 0;
		rotate();


#if DEBUG
		cout << '\n';
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cout << A[i][j] << ' ';
			}
			cout << '\n';
		}
		cout << '\n';
#endif


		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (label[i][j] == -1) {
					areas.push_back(bfs(i, j, g++));
					heads.push_back({ i, j });
				}
			}
		}
		res += score();
	}

	cout << res;

	return 0;
}