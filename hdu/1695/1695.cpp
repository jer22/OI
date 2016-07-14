#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

const int MAXN = 100005;

//f(1)
//F(x) = b/x * d/x

int T, a, b, c, d, k;
long long mob[MAXN];
void getMob() {
	for (int i = 1; i <= 100000; i++) {
		int target = (i == 1 ? 1 : 0);
		int delta = target - mob[i];
		mob[i] = delta;
		for (int j = i + i; j <= 100000; j += i)
			mob[j] += delta;
	}
}

int main() {
	freopen("1695.in", "r", stdin);
	scanf("%d", &T);
	int cas = 0;
	getMob();
	while (cas++ < T) {
		scanf("%d %d %d %d %d", &a, &b, &c, &d, &k);
		if (!k) {
			cout << "Case " << cas << ": 0" << endl;
			continue;
		}
		b /= k;
		d /= k;
		if (b > d) swap(b, d);
		long long ans = 0;
		for (int i = 1; i <= b; i++) {
			ans += mob[i] * (b / i) * (d / i);
		}
		long long t = 0;
		for (int i = 1; i <= b; i++) {
			t += mob[i] * (b / i) * (b / i);
		}
		cout << "Case " << cas << ": "<< ans - t / 2 << endl;
	}


	return 0;
}
