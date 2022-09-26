// url: https://www.codetree.ai/frequent-problems/tree-kill-all/description
#include <iostream>
#include <algorithm>
#define X first
#define Y second
#define DEBUG 0
using namespace std;
typedef pair<int, int> P;
int n, m, k, c;
int res = 0;
int A[20][20][2] = { 0, };
int dr[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
int dia[4][2] = { {1, 1}, {-1, 1}, {1, -1}, {-1, -1} };
int disable[20][20] = { 0,};
void treeClear() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			disable[i][j] = max(0, disable[i][j] - 1);
		}
	}
}
void growUp() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			A[i][j][1] = 0;
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (A[i][j][0] <= 0) continue;
			for (int k = 0; k < 4; k++) {
				int nx = i + dr[k][0];
				int ny = j + dr[k][1];
				if (nx < 0 or nx >= n or ny < 0 or ny >= n) continue;
				if (A[nx][ny][0] <= 0) continue;
				A[i][j][1]++;
			}	
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			A[i][j][0] += A[i][j][1];
		}
	}
}

void spread() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			A[i][j][1] = 0;
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (A[i][j][0] <= 0) continue;
			int cnt = 0;
			for (int k = 0; k < 4; k++) {
				int nx = i + dr[k][0];
				int ny = j + dr[k][1];
				if (nx < 0 or nx >= n or ny < 0 or ny >= n) continue;
				if (disable[nx][ny]) continue;
				if (A[nx][ny][0] == 0) cnt ++;
			}
			if (cnt == 0) continue;
			for (int k = 0; k < 4; k++) {
				int nx = i + dr[k][0];
				int ny = j + dr[k][1];
				if (disable[nx][ny]) continue;
				if (nx < 0 or nx >= n or ny < 0 or ny >= n) continue;
				if (disable[nx][ny]) continue;
				if (A[nx][ny][0] == 0) A[nx][ny][1] += A[i][j][0] / cnt;
			}
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			A[i][j][0] += A[i][j][1];
		}
	}
}

void getMax() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			A[i][j][1] = max(0, A[i][j][0]);
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (A[i][j][0] <= 0) continue;
			for (int k1 = 0; k1 < 4; k1++) {
				int nx = i;
				int ny = j;
				for (int k2 = 0; k2 < k; k2++) {
					nx += dia[k1][0];
					ny += dia[k1][1];
					if (nx < 0 or nx >= n or ny < 0 or ny >= n) break;
					if (A[nx][ny][0] <= 0) break;
					A[i][j][1] += A[nx][ny][0];
				}
			}
		}
	}
	int maxVal = 0;
	P maxPos = { 0, 0};
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (maxVal < A[i][j][1]) {
				maxVal = A[i][j][1];
				maxPos = { i, j };
			}
		}
	}
	res += maxVal;
	treeClear();
	for (int k1 = 0; k1 < 4; k1++) {
		int nx = maxPos.X;
		int ny = maxPos.Y;
		disable[nx][ny] = c;
		A[nx][ny][0] = 0;
		for (int k2 = 0; k2 < k; k2++) {
			nx += dia[k1][0];
			ny += dia[k1][1];
			if (nx < 0 or nx >= n or ny < 0 or ny >= n) break;
			if (A[nx][ny][0] <= 0) {
				disable[nx][ny] = c;
				break;
			}
			disable[nx][ny] = c;
			A[nx][ny][0] = 0;
		}
	}
}
int main() {
	cin >> n >> m >> k >> c;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> A[i][j][0];
		}
	}
	for (int i = 0; i < m; i++) {
		growUp();
#if DEBUG
		cout << '\n';
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cout << A[i][j][0] << '\t';
			}
			cout << '\n';
		}
#endif
		spread();

#if DEBUG
		cout << '\n';
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cout << A[i][j][0] << '\t';
			}
			cout << '\n';
		}
#endif

		getMax();

#if DEBUG
		cout << '\n';
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cout << A[i][j][0] << '\t';
			}
			cout << '\n';
		}
#endif
		
	}
	cout << res;
	return 0;
}