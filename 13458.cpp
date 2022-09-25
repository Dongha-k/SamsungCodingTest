#include <iostream>
using namespace std;
int A[1000000];
int main() {
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> A[i];
	}
	int B, C;
	cin >> B >> C;
	long long res = 0;
	for (int i = 0; i < n; i++) {
		int temp = 0;
		A[i] -= B;
		temp++;
		if (A[i] > 0) temp += A[i] / C;
		if (A[i] > 0 and A[i] % C != 0) temp++;
		res += temp;
	}
	
	cout << res;
	return 0;
}