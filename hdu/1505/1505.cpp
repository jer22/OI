#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <stack>

using namespace std;

struct Node{
	int idx, height;
	Node(int a, int b) : idx(a), height(b) {}
};

int T;
int n, m;
int up[1005][1005];
int lef[1005], rig[1005];
int main() {
	freopen("1505.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &n, &m);
		char c;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				cin >> c;
				up[i][j] = c == 'F' ? up[i - 1][j] + 1 : 0;
			}
		}
		int ans = 0;
		stack<Node> sr, sl;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				Node cur = Node(j, up[i][j]);
				while (!sr.empty() && sr.top().height > cur.height) {
					Node t = sr.top();
					sr.pop();
					rig[t.idx] = cur.idx - t.idx;
				}
				sr.push(cur);
			}
			while (!sr.empty()) {
				Node t = sr.top();
				sr.pop();
				rig[t.idx] = m - t.idx + 1;
			}
			for (int j = m; j >= 1; j--) {
				Node cur = Node(j, up[i][j]);
				while (!sl.empty() && sl.top().height > cur.height) {
					Node t = sl.top();
					sl.pop();
					lef[t.idx] = t.idx - cur.idx;
				}
				sl.push(cur);
			}
			while (!sl.empty()) {
				Node t = sl.top();
				sl.pop();
				lef[t.idx] = t.idx;
			}
			for (int j = 1; j <= m; j++) {
				ans = max(ans, up[i][j] * (lef[j] + rig[j] - 1));
			}
		}
		cout << ans * 3 << endl;
	}
	return 0;
}
