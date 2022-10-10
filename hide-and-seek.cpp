//url : https://www.codetree.ai/frequent-problems/hide-and-seek/description
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#define X first
#define Y second
#define ABS(x) (((x)>0)? (x) : -(x))
#define DEBUG 0
using namespace std;
typedef pair<int, int> P;
int n, m, h, k;
int score = 0;
int taggerX, taggerY, taggerDir;
int dr[4][2] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };
bool isTree[100][100] = { false, };
bool visited[100][100] = { false };
vector<int> fleerMap[100][100];
vector<P> fleers;
vector<int> fleersDir;
vector<int> dirList;
vector<int> runner;
vector<bool> found;
int get_dist(const P& p1, const P& p2) {
	return ABS(p1.X - p2.X) + ABS(p1.Y - p2.Y);
}

void tagger_move() {
#if DEBUG
	cout << "tagger is move " << taggerX << ", " << taggerY << " to ";
#endif
	static int cur = 0;
	taggerX += dr[taggerDir][0];
	taggerY += dr[taggerDir][1];
	taggerDir = dirList[++cur % dirList.size()];
#if DEBUG
	cout << taggerX << ", " << taggerY << "\n";
#endif
}

void run() {
	for (auto idx : runner) {
		if (found[idx]) continue;
#if DEBUG
		cout << "runner " << idx << ": " << fleers[idx].X << ", " << fleers[idx].Y << " to ";
#endif
		int d = fleersDir[idx];
		const int x = fleers[idx].X;
		const int y = fleers[idx].Y;

		int nx = x + dr[d][0];
		int ny = y + dr[d][1];
		if (nx < 0 or nx >= n or ny < 0 or ny >= n) {
			fleersDir[idx] = (d + 2) % 4;
			nx = x + dr[fleersDir[idx]][0];
			ny = y + dr[fleersDir[idx]][1];
			if (nx == taggerX and ny == taggerY) continue;
			fleers[idx] = { nx, ny };
			auto it = find(fleerMap[x][y].begin(), fleerMap[x][y].end(), idx);
			fleerMap[x][y].erase(it);
			fleerMap[nx][ny].push_back(idx);
		}
		else {
			if (nx == taggerX and ny == taggerY) continue;
			fleers[idx] = { nx, ny };
			auto it = find(fleerMap[x][y].begin(), fleerMap[x][y].end(), idx);
			fleerMap[x][y].erase(it);
			fleerMap[nx][ny].push_back(idx);
		}
#if DEBUG
		cout << fleers[idx].X << ", " << fleers[idx].Y << '\n';
#endif
	}
	
}

void find_fleers(int i) {
	int nx = taggerX;
	int ny = taggerY;

#if DEBUG
	cout << "tagger is at " << nx << ", " << ny << " and dir is " << taggerDir << " ";
#endif
	int cnt = 0;
	for (int i = 0; i < 3; i++) {
		if (nx < 0 or nx >= n or ny < 0 or ny >= n) break;
		if (isTree[nx][ny]) {
			nx += dr[taggerDir][0];
			ny += dr[taggerDir][1];
			continue;
		}
		for (auto fleer : fleerMap[nx][ny]) {
			if (!found[fleer]) {
				cnt++;
				found[fleer] = true;
			}
		}
		nx += dr[taggerDir][0];
		ny += dr[taggerDir][1];
	}

#if DEBUG
	cout << "found " << cnt << " fleers" << '\n';
#endif
	score += i * cnt;
}
void find_runner() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			visited[i][j] = false;
		}
	}
	queue<P> q;
	q.push({ taggerX, taggerY });
	visited[taggerX][taggerY] = true;
	while (!q.empty()) {
		P cur = q.front(); q.pop();
		if (!fleerMap[cur.X][cur.Y].empty()) {
			for (int fleer : fleerMap[cur.X][cur.Y]) {
				if (!found[fleer]) runner.push_back(fleer);
			}
		}
		for (int i = 0; i < 4; i++) {
			int nx = cur.X + dr[i][0];
			int ny = cur.Y + dr[i][1];
			if (nx < 0 or nx >= n or ny < 0 or ny >= n) continue;
			if (get_dist({ taggerX, taggerY }, { nx, ny }) > 3) continue;
			if (visited[nx][ny]) continue;
			visited[nx][ny] = true;
			q.push({ nx, ny });
		}
	}

#if DEBUG
	cout << "runner : ";
	for (auto x : runner) if (!found[x]) cout << x << ' ';
	cout << '\n';
#endif
}
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin >> n >> m >> h >> k;
	taggerX = n / 2;
	taggerY = n / 2;
	taggerDir = 0;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			fleerMap[i][j] = vector<int>();
		}
	}
	for (int i = 0; i < m; i++) {
		int x, y, d;
		cin >> x >> y >> d;
		fleers.push_back({ x - 1, y - 1 });
		found.push_back(false);
		fleersDir.push_back(d);
		fleerMap[x - 1][y - 1].push_back(i);
	}
	for (int i = 0; i < h; i++) {
		int x, y;
		cin >> x >> y;
		isTree[x - 1][y - 1] = true;
	}


	int dir = taggerDir;
	int cnt = 1;

	while (dirList.size() <= n * n) {
		for (int i = 0; i < cnt; i++) dirList.push_back(dir);
		dir++; dir %= 4;
		if (dirList.size() == n * n) break;
		for (int i = 0; i < cnt; i++) dirList.push_back(dir);
		dir++; dir %= 4;
		cnt++;
	}
	dirList.pop_back();

	int dir_size = dirList.size();
	for (int i = 0; i < dir_size; i++) {
		dirList.push_back((dirList[dir_size - 1 - i] + 2) % 4);
	}
	for (int i = 1; i <= k; i++) {
#if DEBUG
		cout << "\nround " << i << "\n";
#endif
		runner.clear();
		find_runner();
		run();
		tagger_move();
		find_fleers(i);

	}
	cout << score;
	return 0;
}