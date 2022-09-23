#include <iostream>
#include <deque>
#include <vector>
#include <iostream>
using namespace std;

void rotate(deque<int>& conveyor, vector<int>& robots, deque<bool>& visited) {
	conveyor.push_front(conveyor.back());
	conveyor.pop_back();

	visited.push_front(false);
	visited.pop_back();

	for (int i = 0; i < robots.size(); i++) {
		robots[i] = (robots[i] + 1) % conveyor.size();
	}
}

void move_robot(deque<int>& conveyor, vector<int>& robots, deque<bool>& visited) {
	for (int i = 0; i < robots.size(); i++) {
		int nx = robots[i] + 1;
		if (nx == conveyor.size()) continue;
		if (!visited[nx] and conveyor[nx] > 0) {
			visited[nx] = true;
			conveyor[nx]--;
			robots[i] = nx;
			visited[nx - 1] = false;
		}
	}
}

void drop_robot(deque<int>& conveyor, vector<int>& robots, deque<bool>& visited) {
	for (int i = 0; i < robots.size(); i++) {

		if (robots[i] == conveyor.size() / 2 - 1) {
			visited[robots[i]] = false;
			robots.erase(robots.begin() + i);
			return;
		}
	}
}

void place_robot(deque<int>& conveyor, vector<int>& robots, deque<bool>& visited) {
	if (conveyor[0] > 0) {
		conveyor[0] --;
		robots.push_back(0);
		visited[0] = true;
	}
}

int find_durability_0(deque<int>& conveyor) {
	int cnt = 0;
	for (auto d : conveyor) if (d == 0) cnt++;
	return cnt;
}

int main() {
	int n, k;
	cin >> n >> k;
	deque<int> conveyor(2 * n);
	vector<int> robots;
	deque<bool> visited(n, false);

	for (int i = 0; i < 2 * n; i++) cin >> conveyor[i];
	
	int t;
	for(t = 1 ; ; t ++) {
		rotate(conveyor, robots, visited);
		drop_robot(conveyor, robots, visited);

		move_robot(conveyor, robots, visited);
		drop_robot(conveyor, robots, visited);
		
		place_robot(conveyor, robots, visited);

		//for (auto robot : robots) cout << robot << ' ';
		//cout << '\n';
		if (find_durability_0(conveyor) >= k) break;
	}
	cout << t;
	return 0;
}