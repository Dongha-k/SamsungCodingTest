// url: https://www.codetree.ai/frequent-problems/cleaning-is-joyful/description

#include <iostream>
#include <vector>
#define X first
#define Y second
using namespace std;
typedef pair<int, int> P;
int dust[500][500];
int dr[4][2] = {{0, -1}, {1, 0}, {0, 1}, {-1, 0} };
int n;
vector<int> dirList;

bool boundCheck(P pos) {
	int x = pos.X;
	int y = pos.Y;
	if (x < 0 or x >= n or y < 0 or y >= n) return false;
	
	else return true;	
}

int main() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> dust[i][j];
		}
	}
	int cnt = 1;
	int dir = 0;

	// make dirList
	while (dirList.size() < n * n) {
		for (int i = 0; i < cnt; i++) dirList.push_back(dir);
		dir += 1;
		dir %= 4;
		if (dirList.size() >= n * n) break;
		for (int i = 0; i < cnt; i++) dirList.push_back(dir);
		dir += 1;
		dir %= 4;
		cnt++;
	}
	dirList.pop_back();

	int answer = 0;
	P prev = { n / 2, n / 2 };
	for (int d : dirList) {
		P curr = { prev.X + dr[d][0] , prev.Y + dr[d][1] };
		int val = dust[curr.X][curr.Y];
		int rest = val;
		int front = d;
		int left = (d + 1) % 4;
		int back = (d + 2) % 4;
		int right = (d + 3) % 4;

		P ff = { curr.X + 2 * dr[front][0], curr.Y + 2 * dr[front][1] };
		if (boundCheck(ff)) dust[ff.X][ff.Y] += val * 5 / 100;
		
		else answer += val * 5 / 100;
		rest -= (val * 5) / 100;

		P fr = {curr.X + dr[front][0] + dr[right][0], curr.Y + dr[front][1] + dr[right][1]};
		if (boundCheck(fr)) dust[fr.X][fr.Y] += val * 10 / 100;
		else answer += val * 10 / 100;
		rest -= val * 10 / 100;
		P fl = { curr.X + dr[front][0] + dr[left][0], curr.Y + dr[front][1] + dr[left][1] };
		if (boundCheck(fl)) dust[fl.X][fl.Y] += val * 10 / 100;
		else answer += val * 10 / 100;
		rest -= val * 10 / 100;


		P rr = { curr.X + 2 *dr[right][0] , curr.Y + 2 * dr[right][1]};
		if (boundCheck(rr)) dust[rr.X][rr.Y] += val * 2 / 100;		
		else answer += val * 2 / 100;
		rest -= val * 2 / 100;

		P ll = { curr.X + 2 * dr[left][0], curr.Y + 2 * dr[left][1] };
		if (boundCheck(ll)) dust[ll.X][ll.Y] += val * 2 / 100;
		else answer += val * 2 / 100;
		rest -= val * 2 / 100;

		P r = { curr.X + dr[right][0], curr.Y  + dr[right][1] };
		if (boundCheck(r)) dust[r.X][r.Y] += val * 7 / 100;
		else answer += val * 7 / 100;
		rest -= val * 7 / 100;

		P l = { curr.X + dr[left][0], curr.Y + dr[left][1] };
		if (boundCheck(l)) {
			dust[l.X][l.Y] += val * 7 / 100;
		}
		else answer += val * 7 / 100;
		rest -= val * 7 / 100;

		P rb = { curr.X + dr[right][0] + dr[back][0], curr.Y + dr[right][1] + dr[back][1]};
		if (boundCheck(rb)) dust[rb.X][rb.Y] += val * 1 / 100;
		else answer += val * 1 / 100;
		rest -= val * 1 / 100;

		P lb = { curr.X + dr[left][0] + dr[back][0], curr.Y + dr[left][1] + dr[back][1] };
		if (boundCheck(lb)) dust[lb.X][lb.Y] += val * 1 / 100;
		else answer += val * 1 / 100;
		rest -= val * 1 / 100;

		P f = {curr.X + dr[front][0], curr.Y + dr[front][1]};
		if (boundCheck(f)) dust[f.X][f.Y] += rest;
		else answer += rest;

		dust[curr.X][curr.Y] = 0;
		prev = curr;
	}
	
	cout << answer;

	return 0;
}