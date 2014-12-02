#include <cstdio>
#include <cstring>
#include <algorithm>

#define MAXN 1010
#define MAXM 10010

using namespace std;

struct Edge{
	int passenger;
	int index;
};

bool compare(Edge a, Edge b) {
	return a.passenger > b.passenger;
}

int n, m, k;
int dist[MAXN];		// dist[i]表示从第i站到第i+1站的距离
int getOff[MAXN];
int totalGetOff[MAXN];
int from[MAXM];
int to[MAXM];
int wait[MAXM];
int get[MAXN];
int last[MAXN];
int modify[MAXN];
int times;
int main( void ) {
	int total = 0;
	freopen("1315.in", "r", stdin);
	/*freopen("1315.out", "w", stdout);*/
	scanf("%d %d %d", &n, &m, &k);
	int i, j;
	for (i = 1; i < n; i++) {
		scanf("%d", &dist[i]);
	}
	for (i = 1; i <= m; i++) {
		scanf("%d %d %d", &wait[i], &from[i], &to[i]);
		total += wait[i];
		getOff[to[i]]++;
		last[from[i]] = max(last[from[i]], wait[i]);
		for (j = to[i]; j <= n; j++) {
			totalGetOff[j]++;
		}
	}

	while(k--) {
		// 更新到站时间
		for (i = 2; i <= n; i++) {
			get[i] = max(last[i - 1], get[i - 1]) + dist[i - 1];
		}
		modify[n] = 0;
		for (i = n - 1; i; i--) {
			if (get[i + 1] > last[i + 1]) {
				modify[i] = modify[i + 1] + 1;
			} else {
				modify[i] = 1;
			}
		}
		int maxval = -1, idx = 0;
		for (i = 1; i < n; i++) {
			if (dist[i] && modify[i]
				&& totalGetOff[modify[i] + i] - totalGetOff[i] > maxval) {
				maxval = totalGetOff[modify[i] + i] - totalGetOff[i];
				idx = i;
			}
		}
		if (idx) dist[idx]--;
	}
	for (i = 2; i <= n; i++) {
		get[i] = max(last[i - 1], get[i - 1]) + dist[i - 1];
	}

	for (i = 1; i <= m; i++) {
		times += get[to[i]];
	}
	printf("%d\n", times - total);
	return 0;
}
