#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

int n;
int l[MAXN], r[MAXN];
int main() {
	// freopen("b.in", "r", stdin);
	cin >> n;
	int tl = 0, tr = 0;
	for (int i = 1; i <= n; i++) {
		cin >> l[i] >> r[i];
		tl += l[i];
		tr += r[i];
	}
	int idx = 0;
	int beu = abs(tl - tr);
	for (int i = 1; i <= n; i++) {
		int nl = tl - l[i] + r[i];
		int nr = tr - r[i] + l[i];
		int t = abs(nl - nr);
		if (t > beu) {
			beu = t;
			idx = i;
		}
	}
	cout << idx << endl;
	return 0;
}
