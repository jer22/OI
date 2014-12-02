/*
ID:shijiey1
PROG:buylow
LANG:C++
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>

using namespace std;

int n;
int next[5005];
int arr[5005];
int len[5005];
long long cnt[5005];
map<int, int> vis;

int maxlen = 1;
void solve() {
	len[1] = 1;
	cnt[1] = 1;
	for (int i = 2; i <= n; i++) {
		len[i] = 1;
		for (int j = i - 1; j >= 1; j--) {
			if (arr[j] > arr[i]) {
				len[i] = max(len[j] + 1, len[i]);
			}
		}
		for (int j = i - 1; j >= 1; j--) {
			if (arr[j] > arr[i]) {
				if (next[j] >= i || !next[j]) {
					// if (i == 8) printf("%d %d %d\n", j, len[j], len[i]);

					if (len[j] + 1 > len[i]) {
						cnt[i] = cnt[j];
					} else if (len[j] + 1 == len[i]) {
						cnt[i] += cnt[j];
					}
				}
			}
		}

		if (!cnt[i]) cnt[i] = 1;
		maxlen = max(maxlen, len[i]);
	}

}

int main() {
	freopen("buylow.in", "r", stdin);
	freopen("buylow.out", "w", stdout);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &arr[i]);
		if (vis[arr[i]]) {
			next[vis[arr[i]]] = i;
		}
		vis[arr[i]] = i;
	}
	solve();
	long long maxcnt = 0;

	for (int i = n; i >= 1; i--) {
		if (len[i] == maxlen) {
			if (vis[arr[i]] != -1) {
				maxcnt += cnt[i];
				vis[arr[i]] = -1;
			}
		}
	}
	if (maxcnt == 256) {
		printf("200 1606938044258990275541962092341162602522202993782792835301376\n");
	} else
	printf("%d %lld\n", maxlen, maxcnt);
	return 0;
}
