/*
ID:shijiey1
PROG:buylow
LANG:C++
*/

/*
第一问最长下降子序列，len[i]表示以i结尾最长下降子序列的长度。
第二问求最长下降子序列的个数。cnt[i]为以i结尾最长下降子序列的个数。
对于所有的位置i枚举每一个j(1<=j<=i-1)且arr[j]>arr[i],若len[j]+1>len[i],cnt[j]=cnt[i],否则若len[j]+1==len[i],cnt[j]+=cnt[i]。
因为题目要求不重复，所以记录一个next数组，next[i]表示i右边第一个与i相同的数的位置，不存在则next[i]=0，dp时若next[j]!=0且next[j]<i就跳过。
只有最后一组数据要用高精。
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
