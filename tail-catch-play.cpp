// url: https://www.codetree.ai/frequent-problems/tail-catch-play/description
#include <iostream>
#include <deque>
#include <vector>
#include <queue>
#define DEBUG 0
#define X first
#define Y second
using namespace std;
typedef pair<int, int> P;
vector<deque<P>> lst(5);
int n, m, k;
int dr[4][2] = { {0, 1}, {-1, 0}, {0, -1}, {1, 0} };
int A[20][20];
int mask[20][20];
bool visited[20][20] = { false, };
vector<P> idxLst[4];
void move() {
	for (int i = 0; i < m; i++) {	
		P to;
		for (int j = 0; j < 4; j++) {
			int nx = lst[i].front().X + dr[j][0];
			int ny = lst[i].front().Y + dr[j][1];
			if (nx < 0 or nx >= n or ny < 0 or ny >= n) continue;
			if (A[nx][ny] == 4 or (A[nx][ny] == 3 and mask[nx][ny] == i)) {
				to = { nx, ny };
				break;
			}
		}
		if (to == lst[i].back()) { // circle
			A[lst[i].front().X][lst[i].front().Y] = 2;
			A[lst[i].back().X][lst[i].back().Y] = 1;
			A[lst[i][lst[i].size() - 2].X][lst[i][lst[i].size() - 2].Y] = 3;
			lst[i].push_front(lst[i].back());
			lst[i].pop_back();
		}
		else {
			A[to.X][to.Y] = 1;
			mask[to.X][to.Y] = i;
			mask[lst[i].back().X][lst[i].back().Y] = -1;

			A[lst[i].front().X][lst[i].front().Y] = 2;
			A[lst[i].back().X][lst[i].back().Y] = 4;

			lst[i].pop_back();
			lst[i].push_front(to);
			A[lst[i].back().X][lst[i].back().Y] = 3;
		}

	}
}

void change_head_tail(int idx) {
	deque<P> temp;
	int temp0 = A[lst[idx].front().X][lst[idx].front().Y];
	A[lst[idx].front().X][lst[idx].front().Y] = A[lst[idx].back().X][lst[idx].back().Y];
	A[lst[idx].back().X][lst[idx].back().Y] = temp0;

	while (!lst[idx].empty()) {
		temp.push_back(lst[idx].back());
		lst[idx].pop_back();
	}
	while (!temp.empty()) {
		lst[idx].push_back(temp.front());
		temp.pop_front();
	}
	
}
int findOrder(int idx, P target) {
	for (int i = 0; i < lst[idx].size(); i++) {
		if (lst[idx][i] == target) return i + 1;
	}
}
int shoot(int t) {
	t %= (4 * n);
	int dir = t / n;
	int pos = t % n;
	P cur = idxLst[dir][pos]; // starting point
	bool meet = false;
	int shootedIdx = -1;
	P shootedPos;
	for (int i = 0; i < n; i++) {
		//cout << "(" << cur.X << ',' << cur.Y << ") ";
		if (mask[cur.X][cur.Y] != -1) {
			meet = true;
			shootedIdx = mask[cur.X][cur.Y];
			shootedPos = { cur.X, cur.Y };
			break;
		}
		cur.X += dr[dir][0];
		cur.Y += dr[dir][1];
	}
	if (!meet) return 0;
	else {
		int findedOrder = findOrder(shootedIdx, shootedPos);
		change_head_tail(shootedIdx);
		return findedOrder * findedOrder;
	}
}



int main() {
	cin >> n >> m >> k;
	int idx = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> A[i][j];
			mask[i][j] = -1;
			if (A[i][j] == 1) lst[idx++].push_back({ i, j });
		}
	}
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < n; j++) {
			if (i == 0) idxLst[i].push_back({ j, 0 });
			else if (i == 1) idxLst[i].push_back({ n - 1, j });
			else if (i == 2)idxLst[i].push_back({ n - 1 - j, n - 1 });
			else idxLst[i].push_back({ 0, n - 1 - j });
		}
	}
	for (int i = 0; i < m; i++) {
		P start = lst[i].front();
		lst[i].pop_front();
		queue<P> q;
		q.push(start);
		visited[start.X][start.Y] = true;
		while (!q.empty()) {
			P cur = q.front();
			lst[i].push_back(cur);
			mask[cur.X][cur.Y] = i;
			q.pop();
			for (int i = 0; i < 4; i++) {
				int nx = cur.X + dr[i][0];
				int ny = cur.Y + dr[i][1];
				if (nx < 0 or nx >= n or ny < 0 or ny >= n) continue;
				if (visited[nx][ny]) continue;
				if (A[nx][ny] == 4 or A[nx][ny] == 0) continue;
				if (A[nx][ny] == 3) continue;
				q.push({ nx, ny });
				visited[nx][ny] = true;
				break;
			}
		}
		for (int j = 0; j < 4; j++) {
			int nx = lst[i].back().X + dr[j][0];
			int ny = lst[i].back().Y + dr[j][1];
			if (nx < 0 or nx >= n or ny < 0 or ny >= n) continue;
			if (visited[nx][ny]) continue;
			if (A[nx][ny] == 3) {
				lst[i].push_back({ nx, ny });
				mask[nx][ny] = i;
				break;
			}
		}
	}

	int score = 0;

	for (int i = 0; i < k; i++) {
		move();
		
		score += shoot(i);
	}
	cout << score;


	return 0;
}