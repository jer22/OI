#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2005;
const int MAXQ = 1000005;

int n, m, k, q;
long long c[MAXN][MAXN];
long long pos[MAXN][MAXN][3];
int len[MAXN];
char op[MAXQ][8];
int que[MAXQ][4];
vector<int> ask;
long long sum[MAXN][MAXN];

int lowbit(int x) {
	return x & (-x);
}
void add(int x, int y, int val) {
	for (int i = x; i < MAXN; i += lowbit(i))
		for (int j = y; j < MAXN; j += lowbit(j))
			c[i][j] += val;
}
long long getsum(int x, int y) {
	long long ans = 0;
	for (int i = x; i; i -= lowbit(i))
		for (int j = y; j; j -= lowbit(j))
			ans += c[i][j];
	return ans;
}

bool offf[MAXN];
map<int, int> idx;
int main() {
	freopen("e.in", "r", stdin);
	scanf("%d %d %d", &n, &m, &k);
	for (int i = 1; i <= k; i++) {
		scanf("%d", &len[i]);
		for (int j = 1; j <= len[i]; j++) {
			scanf("%lld %lld %lld", &pos[i][j][0], &pos[i][j][1], &pos[i][j][2]);
		}
	}
	scanf("%d", &q);
	for (int i = 1; i <= q; i++) {
		scanf("%s", op[i]);
		if (op[i][0] == 'S') scanf("%d", &que[i][0]);
		else {
			scanf("%d %d %d %d", &que[i][0], &que[i][1], &que[i][2], &que[i][3]);
			ask.push_back(i);
			idx[i] = ask.size() - 1;
		}
	}
	for (int i = 1; i <= k; i++) {
		for (int j = 1; j <= len[i]; j++)
			add(pos[i][j][0], pos[i][j][1], pos[i][j][2]);
		for (int j = 0; j < ask.size(); j++) {
			sum[i][j] = getsum(que[ask[j]][2], que[ask[j]][3])
				- getsum(que[ask[j]][2], que[ask[j]][1] - 1)
				- getsum(que[ask[j]][0] - 1, que[ask[j]][3])
				+ getsum(que[ask[j]][0] - 1, que[ask[j]][1] - 1);
		}
		for (int j = 1; j <= len[i]; j++)
			add(pos[i][j][0], pos[i][j][1], -pos[i][j][2]);
	}
	for (int i = 1; i <= q; i++) {
		if (op[i][0] == 'S')
			offf[que[i][0]] ^= 1;
		else {
			long long ans = 0;
			for (int j = 1; j <= k; j++) {
				if (offf[j]) continue;
				ans += sum[j][idx[i]];
			}
			cout << ans << endl;
		}
	}


	return 0;
}
