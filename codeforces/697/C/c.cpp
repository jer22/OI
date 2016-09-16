#include <bits/stdc++.h>

using namespace std;

int q;
map<long long, long long> val;
int main() {
	freopen("c.in", "r", stdin);
	cin >> q;
	while (q--) {
		int op;
		long long a, b, c;
		scanf("%d %lld %lld", &op, &a, &b);
		if (op == 1) {
			scanf("%lld", &c);
			while (a != b) {
				if (a < b) swap(a, b);
				val[a] += c;
				// cout << a << endl;
				a >>= 1;
			}
		} else {
			long long ans = 0;
			while (a != b) {
				if (a < b) swap(a, b);
				ans += val[a];
				a >>= 1;
			}
			cout << ans << endl;
		}
	}


	return 0;
}
