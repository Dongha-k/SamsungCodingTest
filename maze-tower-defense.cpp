// url : https://www.codetree.ai/frequent-problems/maze-tower-defense/description
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
vector<int> arr;
int n, m;
int init[25][25];
int score = 0;
vector<int> dirLst;
int dr[4][2] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };

void make_dirLst() {
	int cnt = 1;
	int dir = 0;
	while (cnt < n) {
		for (int j = 0; j < cnt; j++) dirLst.push_back(dir);
		dir = (dir + 1) % 4;
		for (int j = 0; j < cnt; j++) dirLst.push_back(dir);
		dir = (dir + 1) % 4;
		cnt++;
	}
	for (int j = 0; j < cnt - 1; j++) dirLst.push_back(dir);
}
void make_arr() {
	int dr[4][2] = { {0, -1}, {1, 0}, {0, 1}, {-1, 0} };
	int x = n / 2, y = n / 2;
	arr.push_back(-1);
	for (int i = 0; i < dirLst.size(); i++) {
		x += dr[dirLst[i]][0];
		y += dr[dirLst[i]][1];
		if (init[x][y] == 0) return;
		arr.push_back(init[x][y]);
	}
}
void attack(int d, int p) {
	int tmp_score = 0;
	int ad;
	if (d == 0) ad = 5;
	else if (d == 1) ad = 3;
	else if (d == 2) ad = 1;
	else ad = 7;
	int cur = 0;
	while (p--) {
		if (cur + ad >= arr.size()) break;
		tmp_score += arr[cur + ad];
		cur += ad;
		arr.erase(arr.begin() + cur--);
		
		ad += 8;
	}
	score += tmp_score;
}

void remove() {
	while (true) {
		// check if there are more 4-consecutive monsters.
		vector<int> erase_start;
		int cnt = 1;
		for (int i = 0; i < arr.size(); i++) {
			if (i != arr.size() - 1 and arr[i] == arr[i + 1]) cnt++;
			else cnt = 1;
			if (cnt == 4) erase_start.push_back(i - 2);
		}
		if (erase_start.empty()) break;
		
		int erase_cnt = 0;
		int erase_val = 0;
		for (auto e_idx : erase_start) {
			int idx = e_idx - erase_cnt;
			int val = arr[idx];
			while (idx < arr.size() and arr[idx] == val) {
				arr.erase(arr.begin() + idx);
				erase_cnt++;
				erase_val += val;
			}
		}
		score += erase_val;
	}
}
void regen() {
	vector<int> new_gen(1, -1);
	int len = arr.size();
	for (int i = 1; i < len;) {
		int cnt = 1;
		int val = arr[i];
		for (int j = i + 1; j < len; j++) {
			if (val == arr[j]) cnt++;
			else break;
		}
		i += cnt;
		new_gen.push_back(cnt);
		if (new_gen.size() >= n * n) break;
		new_gen.push_back(val);
		if (new_gen.size() >= n * n) break;
	}
	arr.clear();
	for (auto x : new_gen) arr.push_back(x);
}


int main() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> init[i][j];
		}
	}
	
	make_dirLst();
	make_arr();
	for (int i = 0; i < m; i++) {
		int d, p;
		cin >> d >> p;
		attack(d, p);
		remove();
		regen();
	}


	cout << score; 
	return 0;
}