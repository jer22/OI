#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

const int MAXN = 100005;

struct Element{
	int value, count;
	bool operator < (const Element &e) const {
		return value < e.value;
	}
};

int T, n, m;
Element a[MAXN], b[MAXN];
int main() {
	freopen("1123.in", "r", stdin);
	cin >> T;
	while (T--) {
		cin >> n >> m;
		for (int i = 0; i < n; i++)
			cin >> a[i].value >> a[i].count;
		for (int i = 0; i < m; i++)
			cin >> b[i].value >> b[i].count;
		sort(a, a + n);
		sort(b, b + m);
		int i = 0, j = 0;
		long long ans = 0, t = 0;
		while (i < n) {
			while (j < m && b[j].value < a[i].value)
				t += b[j++].count;
			ans += t * a[i++].count;
		}
		cout << ans << endl;
	}
	return 0;
}
