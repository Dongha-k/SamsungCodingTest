//url: https://www.codetree.ai/frequent-problems/min-of-hospital-distance/description

#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#define ABS(x) (((x)>0)? (x):-(x))
#define X first
#define Y second

using namespace std;
int n, m;
typedef pair<int, int> P;
typedef struct {
	P pos;
	int V;
} H;
int map[50][50];
vector<H> score;
vector<P> people;

bool comp(const H& h1, const H& h2) {
	return h1.V < h2.V;
}
int getDist(P p1, P p2) {
	return ABS(p1.X - p2.X) + ABS(p1.Y - p2.Y);
}
bool used[13] = { false, };
int idxs[13];
int answer = 0x7fffffff;
void f(int k, int n, int start) {
	if (k == n) {
		int res = 0;
		for (auto p : people) {
			int tmp = 0x7fffffff;
			for (int i = 0; i < n; i++) {
				H h = score[idxs[i]];
				tmp = min(tmp, getDist(p, h.pos));
			}
			res += tmp;
		}
		answer = min(answer, res);
		return;
	}

	for (int i = 0; i < score.size(); i++) {
		if (!used[i]) {
			used[i] = true;
			idxs[k] = i;
			f(k + 1, n, i + 1);
			used[i] = false;
		}
	}
	
}
int main() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> map[i][j];
			if (map[i][j] == 1) people.push_back({ i, j });
			else if (map[i][j] == 2) score.push_back({ {i, j}, 0 });
		}
	}
	f(0, m, 0);
	cout << answer;
	return 0;
}