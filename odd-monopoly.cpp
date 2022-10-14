// url: https://www.codetree.ai/frequent-problems/odd-monopoly/description

#include <iostream>
#define X first
#define Y second
#define own first
#define life second
using namespace std;
typedef pair<int, int> P;
int n, m, k;
int player_dir[401];
bool dead[401] = {false, };
P player_pos[401];
int dir_priority[401][4][4];
P grid[21][21];
int dr[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
void count_down() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (grid[i][j].life > 0) {
				grid[i][j].life--;
				if (grid[i][j].life == 0) {
					grid[i][j].own = 0;
				}
			}
		}
	}
}

void move() {
	for (int i = 1; i <= m; i++) {
		if (dead[i]) continue;
		int dir = player_dir[i];
		int x = player_pos[i].X;
		int y = player_pos[i].Y;
		bool moved = false;
		for (int j = 0; j < 4; j++) {
			int p = dir_priority[i][dir][j];
			int nx = x + dr[p][0];
			int ny = y + dr[p][1];
			if (nx < 0 or nx >= n or ny < 0 or ny >= n) continue;
			if (grid[nx][ny].own == 0) {
				moved = true;
				player_pos[i] = { nx, ny };
				player_dir[i] = p;
				break;
			}
		}
		if (!moved) {
			for (int j = 0; j < 4; j++) {
				int p = dir_priority[i][dir][j];
				int nx = x + dr[p][0];
				int ny = y + dr[p][1];
				if (nx < 0 or nx >= n or ny < 0 or ny >= n) continue;
				if (grid[nx][ny].own == i) {
					moved = true;
					player_pos[i] = { nx, ny };
					player_dir[i] = p;
					break;
				}
			}
		}
	}
}


void fight() {
	for (int i = 1; i <= m; i++) {
		if (dead[i]) continue;
		int x = player_pos[i].X;
		int y = player_pos[i].Y;
		if (grid[x][y].own == 0 or grid[x][y].own == i) grid[x][y].own = i;
		else if (grid[x][y].own < i) {
			dead[i] = true;
			//cout << "player " << i << " was dead.\n";
		}
		else { 
			dead[grid[x][y].own] = true;
			//cout << "player " << grid[x][y].own << " was dead.\n";
			grid[x][y].own = i;
		}
		grid[x][y].life = k;
	}
}

bool check() {
	for (int i = 2; i <= m; i++) if (!dead[i]) return false;
	return true;
}

void show() {
	int tmp[20][20] = { 0, };
	for (int i = 0; i < m; i++) if (!dead[i]) tmp[player_pos[i].X][player_pos[i].Y] = i;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << grid[i][j].own << "/" << grid[i][j].life << '\t';
		}
		cout << '\t';
		for (int j = 0; j < n; j++) {
			cout << tmp[i][j] << "  " << '\t';
		}
		cout << '\n';
	}
	cout << '\n';
}
int main() {
	cin >> n >> m >> k;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> grid[i][j].own;
			if (grid[i][j].own == 0) grid[i][j] = { 0, 0 };
			else {
				grid[i][j].life = k;
				player_pos[grid[i][j].own] = { i, j };
			}
		}
	}
	for (int i = 1; i <= m; i++) {
		dead[i] = false;
		int d;
		cin >> d;
		player_dir[i] = d - 1;
	}

	for (int i = 1; i <= m; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				int d;
				cin >> d;
				dir_priority[i][j][k] = d - 1;
			}
		}
	}

	int t = 1000;
	for(int i = 1; i <= t ; i ++) {
		move(); 
		count_down();
		fight();
		if (check()) {
			cout << i;
			return 0;
		}
	}

	cout << -1;
	return 0;
}
