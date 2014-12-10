/*
ID:shijiey1
PROG:humble
LANG:C++
*/

/*
已经知道前k个丑数，如何得到第k+1个丑数？
对于每个质数p，找到最小的丑数h，使得h*p比上一个丑数大，所有的h*p中最小的就是下一个丑数。
但这样会很慢，所以需要一个pindex数组记录每个质数乘到了哪一个丑数。
//其实就是官方题解
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
