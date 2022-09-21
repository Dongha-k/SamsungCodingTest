#include <iostream>
#include <vector>
#include <deque>
#include <string>

using namespace std;

void rotate(int dir, deque<char>& cog) {
	if (dir == 1) {
		cog.push_front(cog.back());
		cog.pop_back();
	}
	else {
		cog.push_back(cog.front());
		cog.pop_front();
	}
}
void recursiveRight(int start, vector<deque<char>>& cogs, int dir) {
	if (start == 3) return;
	if (cogs[start][2] != cogs[start + 1][6]) {
		//cout << start + 2 << ' ' << dir << '\n';
		recursiveRight(start + 1, cogs, -dir);
		rotate(dir, cogs[start + 1]);

	}
}

void recursiveLeft(int start, vector<deque<char>>& cogs, int dir) {
	if (start == 0) return;
	if (cogs[start][6] != cogs[start - 1][2]) {
		//cout << start << ' ' << dir << '\n';
		recursiveLeft(start - 1, cogs, -dir);
		rotate(dir, cogs[start - 1]);

	}
}

int main() {
	vector<deque<char>> cogs(4, deque<char>());

	for (int i = 0; i < 4; i++) {
		string str;
		cin >> str;
		for (char ch : str) {
			cogs[i].push_back(ch);
		}
	}

	int n;
	cin >> n;

	for (int i = 0; i < n; i++) {
		int num, dir;
		cin >> num >> dir;
		num--;
		recursiveRight(num, cogs, -dir);
		recursiveLeft(num, cogs, -dir);
		rotate(dir, cogs[num]);

	}
	
	int answer = 0;
	if (cogs[0][0] == '1') answer += 1;
	if (cogs[1][0] == '1') answer += 2;
	if (cogs[2][0] == '1') answer += 4;
	if (cogs[3][0] == '1') answer += 8;
	cout << answer;

	return 0;
}