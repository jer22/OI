#include <bits/stdc++.h>

using namespace std;

int T;
int main() {
	freopen("a.in", "r", stdin);
	long long l, r;
	scanf("%d", &T);
	while (T--) {
		cin >> l >> r;
		long long ans = 0;
		for (int i = 62; i >= 0; i--) {
			if ((r >> i) != (l >> i)) {

				long long t = (1ll << i) - 1ll;
				ans |= t;
				if ((ans | (1ll << i)) <= r) ans |= (1ll << i);
				break;
			} else ans |= ((r >> i) << i);
		}
		cout << ans << endl;
	}


	return 0;
}
