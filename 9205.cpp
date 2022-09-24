#include <iostream>
#include <queue>
#define ABS(x) ((x) > 0 ? (x) : -(x))
#define X first
#define Y second

using namespace std;
typedef pair<int, int> P;

int dist(int x1, int y1, int x2, int y2) {
	return ABS(x1 - x2) + ABS(y1 - y2);
}
bool flag = false;
void dfs(int x, int y, const int fx, const int fy, vector<P>& conv, vector<bool>& visited) {
	if (flag) return;
	if (dist(x, y, fx, fy) <= 1000) {
		flag = true;
		return;
	}
	for (int i = 0; i < conv.size(); i++) {
		if (visited[i]) continue;
		if (dist(conv[i].X, conv[i].Y, x, y) > 1000) continue;
		visited[i] = true;
		dfs(conv[i].X, conv[i].Y, fx, fy, conv, visited);
	}
}
int main() {
	int t;
	cin >> t;
	for (int i = 0; i < t; i++) {
		int n;
		flag = false;
		vector<P> conv;
		cin >> n;
		int sx, sy, fx, fy;
		cin >> sx >> sy;
		for (int j = 0; j < n; j++) {
			int x, y;
			cin >> x >> y;
			conv.push_back({ x, y });
		}
		cin >> fx >> fy;
		vector<bool> visited(n, false);
		dfs(sx, sy, fx, fy, conv, visited);
		if (flag) cout << "happy\n";
		else cout << "sad\n";
	}
	return 0;
}