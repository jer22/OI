#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <set>

using namespace std;

int T, n, k, sum;
int arr[2005];

multiset<int> s;
bool solve(int ans) {
	s.clear();
	for (int i = 0; i < n; i++) {
		s.insert(arr[i]);
	}
	for (int i = 0; i < k; i++) {
		if (s.empty()) break;
		int now = ans;
		while (!s.empty() && now >= *(s.begin())) {
			multiset<int>::iterator it = s.lower_bound(now + 1);
			it--;
			now -= *it;
			s.erase(it);
		}
	}
	return s.empty();
}

int main() {
	freopen("c.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		sum = 0;
		scanf("%d %d", &n, &k);
		for (int i = 0; i < n; i++) {
			scanf("%d", &arr[i]);
			sum += arr[i];
		}
		int ans = sum / k;
		while (!solve(ans)) {
			// cout << ans << endl;
			ans++;
		}
		// cout << solve(32) << endl;
		printf("%d\n", ans);
	}

	return 0;
}
