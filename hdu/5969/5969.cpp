#include <bits/stdc++.h>

using namespace std;

int T;
long long l, r;
int main() {
	freopen("5969.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		scanf("%lld %lld", &l, &r);
		bool flag = 0;
		long long ans = 0;
		for (long long i = 62ll; i >= 0ll; i--) {
			if (r & (1ll << i)) {
				ans |= (1ll << i);
				if (!(l & (1ll << i))) flag = 1;
			} else {
				if (flag) ans |= (1ll << i);
			}
		}
		cout << ans << endl;
	}
	return 0;
}
