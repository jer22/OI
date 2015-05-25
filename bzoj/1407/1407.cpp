#include <bits/stdc++.h>

using namespace std;

int n;
int arr[20], len[20], lif[20];

void exgcd(int a, int b, int &d, int &x, int &y) {
	if (!b) d = a, x = 1, y = 0;
	else {
		exgcd(b, a % b, d, y, x);
		y -= x * (a / b);
	}
}

int d, x, y;
bool solve(int m) {
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			int dx = ((arr[j] - arr[i]) % m + m) % m;
			int de = ((len[i] - len[j]) % m + m) % m;
			exgcd(de, m, d, x, y);
			if (dx % d) continue;
			dx /= d;
			int mm = m / d;
			int k = (dx * x % mm + mm) % mm;
			if (k <= lif[i] && k <= lif[j])
				return false;
		}
	}
	return true;
}

int main() {
	freopen("1407.in", "r", stdin);
	scanf("%d", &n);
	int f = 0;
	for (int i = 0; i < n; i++) {
		scanf("%d %d %d", &arr[i], &len[i], &lif[i]);
		arr[i]--;
		f = max(f, arr[i]);
	}
	while (f++)
		if (solve(f)) break;
	printf("%d\n", f);
	return 0;
}
