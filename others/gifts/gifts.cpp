#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int x[105], y[105], sm[105], sv[105], pm[105], pv[105];
int n, m;

bool work(int i) {
	int qian = 0;
	for (int j = 1; j <= n; j++) {
		int pre = y[j];
		int num = x[j] * i;
		if (y[j] != 0) {
			int t = min(num, pre);
			num -= t;
			pre -= t;
		}
		if (num != 0) {
			int zuixiao = 99999999;
			for (int p = 0; p <= 1000000; p++) {
				int temp = num;
				int lef = num - p * sm[j];
				int q = 0;
				if (lef > 0) {
					q = lef / sv[j];
					if (lef % sv[j] != 0) q++;
				}
				zuixiao = min(zuixiao, p * pm[j] + q * pv[j]);
				if (p * sm[j] >= num) break;
			}
			qian += zuixiao;
		}
	}
	return qian > m;
}

int main() {
	freopen("gifts.in", "r", stdin);
	freopen("gifts.out", "w", stdout);
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		cin >> x[i] >> y[i] >> sm[i] >> pm[i] >> sv[i] >> pv[i];
	int i;
	int l = 1, r = 100000;
	while (l < r) {
		int mid = (l + r) >> 1;
		if (work(mid)) {
			r = mid;
		} else {
			l = mid + 1;
		}
	}

	cout << l - 1 << endl;
}
