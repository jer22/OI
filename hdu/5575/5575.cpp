#include <bits/stdc++.h>
#include <ext/pb_ds/priority_queue.hpp>

using namespace std;

const int MAXN = 100005;
const int INF = 0x3f3f3f3f;

struct Node{
	int y, t;
	Node() {}
	Node(int a, int b) : y(a), t(b) {}
	bool operator < (const Node &n) const {
		return y > n.y;
	}
};

int T, n, m;
__gnu_pbds::priority_queue<Node> q[MAXN];
int h[MAXN];
stack<int> st;
int sum[2][MAXN], dp[MAXN];
int main() {
	freopen("5575.in", "r", stdin);
	scanf("%d", &T);
	for (int cas = 1; cas <= T; cas++) {
		scanf("%d %d", &n, &m);
		for (int i = 1; i < n; i++)
			scanf("%d", &h[i]);
		for (int i = 0; i <= n; i++) {
			sum[0][i] = sum[1][i] = dp[i] = 0;
			while (!q[i].empty()) q[i].pop();
		}
		while (!st.empty()) st.pop();
		st.push(0);
		h[0] = h[n] = INF;
		int a, b, c;
		for (int i = 0; i < m; i++) {
			scanf("%d %d %d", &a, &b, &c);
			q[a].push(Node(b + 1, c));
			sum[0][a] += !c;
		}
		for (int i = 1; i <= n; i++) {
			while (!st.empty() && h[i] >= h[st.top()]) {
				int top = st.top();
				st.pop();
				int cnt0 = 0, cnt1 = 0;
				int ans = 0;
				int last = 0;
				while (!q[i].empty() && q[i].top().y <= h[top]) {
					Node t = q[i].top();
					q[i].pop();
					if (t.y != last) {
						sum[0][i] -= cnt0;
						sum[1][i] += cnt1;
						cnt0 = cnt1 = 0;
						ans = max(ans, sum[0][i] + sum[1][i]);
						dp[i] = max(dp[i], dp[top] + ans);
					}
					cnt0 += !t.t;
					cnt1 += t.t;
					last = t.y;
				}
				sum[0][i] -= cnt0;
				sum[1][i] += cnt1;
				ans = max(ans, sum[0][i] + sum[1][i]);
				dp[i] = max(dp[i], dp[top] + ans);
				sum[0][i] += sum[0][top];
				sum[1][i] += sum[1][top];
				q[i].join(q[top]);
			}
			if (!st.empty()) {
				int top = st.top();
				int cnt0 = 0, cnt1 = 0;
				int ans = 0;
				int last = 0;
				while (!q[i].empty() && q[i].top().y <= h[i]) {
					Node t = q[i].top();
					q[i].pop();
					if (t.y != last) {
						sum[0][i] -= cnt0;
						sum[1][i] += cnt1;
						cnt0 = cnt1 = 0;
						ans = max(ans, sum[0][i] + sum[1][i]);
						dp[i] = max(dp[i], dp[top] + ans);
					}
					cnt0 += !t.t;
					cnt1 += t.t;
					last = t.y;
				}
				sum[0][i] -= cnt0;
				sum[1][i] += cnt1;
				ans = max(ans, sum[0][i] + sum[1][i]);
				dp[i] = max(dp[i], dp[top] + ans);
			}
			st.push(i);
		}
		printf("Case #%d: %d\n", cas, dp[n]);
	}

	return 0;
}
