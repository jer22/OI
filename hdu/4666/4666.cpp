#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <set>

using namespace std;

int n, m;
multiset<int> s[1 << 5];
int arr[60005][10];
int main() {
	freopen("4666.in", "r", stdin);
	while (~scanf("%d %d", &n, &m)) {
		for (int i = 0; i < 1 << 5; i++)
			s[i].clear();
		int t, x;
		for (int i = 1; i <= n; i++) {
			scanf("%d", &t);
			if (!t) {
				for (int j = 0; j < m; j++)
					scanf("%d", &arr[i][j]);
				for (int j = 0; j < (1 << m); j++) {
					int sum = 0;
					for (int k = 0; k < m; k++) {
						if (j & (1 << k))
							sum += arr[i][k];
						else sum -= arr[i][k];
					}
					s[j].insert(sum);
				}
			} else {
				scanf("%d", &x);
				for (int j = 0; j < (1 << m); j++) {
					int sum = 0;
					for (int k = 0; k < m; k++) {
						if (j & (1 << k))
							sum += arr[x][k];
						else sum -= arr[x][k];
					}
					s[j].erase(s[j].find(sum));
				}
			}
			int ans = 0;
			for (int j = 0; j < (1 << m); j++) {
				multiset<int>::iterator ss = s[j].begin();
				multiset<int>::iterator ee = s[j].end();
				ee--;
				ans = max(ans, *ee - *ss);
			}
			printf("%d\n", ans);
		}

	}


	return 0;
}
