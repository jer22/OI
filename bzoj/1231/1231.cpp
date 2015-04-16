#include <bits/stdc++.h>

using namespace std;

struct Node{
	int last, stat;
	long long cnt;
	Node() {}
	Node(int a, int b) : last(a), stat(b) {}
};

int n, K;
int num[20];
long long dp[20][135550];
bool vis[20][135550];

int main() {
	freopen("1231.in", "r", stdin);
	scanf("%d %d", &n, &K);
	queue<Node> q;
	for (int i = 0; i < n; i++) {
		scanf("%d", &num[i]);
		q.push(Node(i, 1 << i));
		dp[i][1 << i] = 1;
		vis[i][1 << i] = 1;
	}
	while (!q.empty()) {
		Node cur = q.front();
		q.pop();
		vis[cur.last][cur.stat] = 0;

		for (int i = 0; i < n; i++) {
			if ((1 << i) & cur.stat) continue;
			if (abs(num[i] - num[cur.last]) <= K) continue;
			int nex = cur.stat | (1 << i);
			dp[i][nex] += dp[cur.last][cur.stat];

			if (!vis[i][nex]) {
				vis[i][nex] = 1;
				cout << i << ' ' << nex << endl;
				q.push(Node(i, nex));
			}
		}
	}
	long long ans = 0;
	for (int i = 0; i < n; i++)
		ans += dp[i][(1 << n) - 1];
	printf("%lld\n", ans);

	return 0;
}
