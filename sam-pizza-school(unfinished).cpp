//url : https://www.codetree.ai/frequent-problems/sam-pizza-school/description
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> A(100, vector<int>(100, 0));
vector<vector<int>> tmp(100, vector<int>(100, 0));

int n, k;
void add_powder() {
	int _min = *min_element(A[0].begin(), A[0].end());
	for (int i = 0; i < n; i++) if (A[99][i] == _min) A[99][i] ++;
}
void rotate90deg(int sx, int sy, int n, int m) {
	// +90deg·Î È¸Àü
	for (int x = sx; x < sx + n; x++){
		for (int y = sy; y < sy + m; y++) {
			int ox = x - sx, oy = y - sy;
			int rx = oy, ry = n - ox - 1;
			tmp[rx][ry] = A[x][y];
		}
	}
}

void roll() {
	int n = 1, m = 1;
	for (int i = 1; ; i *= 2) {

	}
}

void place2top(int sx, int sy, ) {
}
int main() {
	cin >> n >> k;
	for (int i = 0; i < n; i++) cin >> A[99][i];
	
	return 0;
}