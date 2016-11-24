#include <bits/stdc++.h>

using namespace std;

int n, m;
long long arr[105], s[105];
int main() {
	// freopen("b.in", "r", stdin);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		cin >> arr[i];
		s[i] = s[i - 1] + arr[i];
	}
	int a, b;
	long long sum = 0;
	for (int i = 1; i <= m; i++) {
		cin >> a >> b;
		long long t = s[b] - s[a - 1];
		if (t > 0) sum += t;
	}
	cout << sum << endl;

	return 0;
}
