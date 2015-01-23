/*
ID:shijiey1
LANG:C++
PROG:rectbarn
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <stack>

using namespace std;

struct Node{
	int height, idx;
	Node() {}
	Node(int a, int b) : height(a), idx(b) {}
};

int n, m, k;
bool arr[3002][3002];
int up[3002];
int lef[3002];
int rig[3002];
int main() {
	freopen("rectbarn.in", "r", stdin);
	freopen("rectbarn.out", "w", stdout);
	scanf("%d %d %d", &n, &m, &k);
	int a, b;
	for (int i = 0; i < k; i++) {
		scanf("%d %d", &a, &b);
		arr[a][b] = 1;
	}
	stack<Node> s;
	int ans = 0;
	Node cur, t;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (arr[i][j]) up[j] = 0;
			else up[j]++;
		}
		for (int j = 1; j <= m; j++) {
			cur = Node(up[j], j);
			while (!s.empty() && s.top().height > cur.height) {
				t = s.top();
				s.pop();
				rig[t.idx] = cur.idx - t.idx;
			}
			s.push(cur);
		}
		while (!s.empty()) {
			t = s.top();
			s.pop();
			rig[t.idx] = m - t.idx + 1;
		}
		for (int j = m; j >= 1; j--) {
			cur = Node(up[j], j);
			while (!s.empty() && s.top().height > cur.height) {
				t = s.top();
				s.pop();
				lef[t.idx] = t.idx - cur.idx;
			}
			s.push(cur);
		}
		while (!s.empty()) {
			t = s.top();
			s.pop();
			lef[t.idx] = t.idx;
		}
		for (int j = 1; j <= m; j++)
			ans = max(ans, up[j] * (lef[j] + rig[j] - 1));
	}
	printf("%d\n", ans);

	return 0;
}
