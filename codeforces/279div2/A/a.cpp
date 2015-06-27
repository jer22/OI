#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int n;
int a[5010], b[5010], c[5010];
int n1, n2, n3;
int main() {
	cin >> n;
	int t;
	for (int i = 1; i <= n; i++) {
		cin >> t;
		if (t == 1) a[n1++] = i;
		if (t == 2) b[n2++] = i;
		if (t == 3) c[n3++] = i;
	}
	int ans = min(n1, min(n2, n3));
	cout << ans << endl;
	for (int i = 0; i < ans; i++) {
		cout << a[i] << ' ' << b[i] << ' ' << c[i] << endl;
	}

	return 0;
}
