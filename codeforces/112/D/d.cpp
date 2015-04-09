#include <bits/stdc++.h>

using namespace std;

int n;
int f[100005];
int main() {
	// freopen("d.in", "r", stdin);
	for (int i = 0; i <= n; i++)
		f[i] = -100000000;
	cin >> n;
	int x, y;
	for (int i = 1; i <= n; i++) {
		cin >> x >> y;
		int cnt = 0;
		for (int k = 1; k <= (int)sqrt(x); k++) {
			if (!(x % k)) {
				int a = k, b = x / k;
				if (f[a] < i - y) cnt++;
				f[a] = i;
				if (a != b) {
					if (f[b] < i - y) cnt++;
					f[b] = i;
				}
			}
		}
		cout << cnt << endl;
	}


	return 0;
}
