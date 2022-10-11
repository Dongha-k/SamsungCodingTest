#include <iostream>
#include <queue>
#include <vector>
using namespace std;
typedef pair<int, int> P;
int dr[4][2] = { {0, -1}, {-1, 0} , {0, 1}, {1, 0} };
int n, m, k;
int office[20][20];
typedef struct {
	int X;
	int Y;
	int D;
} Node;
vector<Node> aircon;
int wall_dir[20][20] = { -1, };
int val[20][20] = { 0, };

void blow(){
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			val[i][j] = 0;
		}
	}
	for (Node elem : aircon) {
		int tmp[20][20] = { 0, };
		int nx = elem.X;
		int ny = elem.Y;
		int dir = elem.D;
		nx += dr[dir][0];
		ny += dr[dir][1];
		if (nx < 0 or nx >= n or ny < 0 or ny >= n) continue;
		tmp[nx][ny] = 5;
		for (int i = 0; i <= 5; i++) {
			


			
			nx += dr[dir][0];
			ny += dr[dir][1];
			if (nx < 0 or nx >= n or ny < 0 or ny >= n) break;
		}
	}
}

int main() {
	cin >> n >> m >> k;
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> office[i][j];
			if (office[i][j] >= 2) aircon.push_back({ i, j , office[i][j] - 2});
		}
	}
	for (int i = 0; i < m; i++) {
		int x, y, s;
		cin >> x >> y >> s;
		if (s == 0) wall_dir[x][y] = 3;
		else wall_dir[x][y] = 2;
	}
	
	return 0;
}