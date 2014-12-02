/*
ID:shijiey1
PROG:humble
LANG:C++
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

int n, m;
int arr[110];
long long ans[100010];
int pindex[110];
int cnt = 0;
int main() {
	freopen("humble.in", "r", stdin);
	freopen("humble.out", "w", stdout);
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}
	ans[0] = 1;
	// known i'th hum, to get (i + 1)'th hum
	for (int i = 1; i <= m; i++) {
		long long minnum = (1 << 31) - 1;
		// for every prime p, find the min hum h that h * p is more than the last hum
		// get the minnum of every h * p
		for (int j = 0; j < n; j++) {
			int p = arr[j];
			for (int k = pindex[j]; k < i; k++) {
				long long h = ans[k];
				long long t = h * p;
				if (t > ans[i - 1]) {
					pindex[j] = k;
					minnum = min(minnum, t);
					break;
				}
			}
		}
		// printf("%d\n", minnum);
		ans[i] = minnum;
	}
	printf("%lld\n", ans[m]);
	return 0;
}
