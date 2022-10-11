#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int operand[11];
int op[3];

signed int _min = 0x7fffffff;
signed int _max = _min + 1;


void f(int k, int n, int cur) {
	if (k == n) {
		_min = min(_min, cur);
		_max = max(_max, cur);
		return;
	}
	for (int i = 0; i < 3; i++) {
		if (op[i] > 0) {
			op[i] --;
			if (i == 0) f(k + 1, n, cur + operand[k]);
			else if (i == 1) f(k + 1, n, cur - operand[k]);
			else f(k + 1, n, cur * operand[k]);
			op[i] ++;
		}
	}
}
int main() {
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) cin >> operand[i];
	for (int i = 0; i < 3; i++) cin >> op[i];
	f(1, n, operand[0]);
	cout << _min << ' ' << _max;
	return 0;
}