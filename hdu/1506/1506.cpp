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

int n;
int height[100005];
int lef[100005];
int rig[100005];
int main() {
	while (~scanf("%d", &n) && n) {
		for (int i = 1; i <= n; i++)
			scanf("%d", &height[i]);
		stack<Node> sl;
		stack<Node> sr;
		for (int i = 1; i <= n; i++) {
			Node cur = Node(i, height[i]);
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
			rig[t.idx] = n - t.idx + 1;
		}
		for (int i = n; i >= 1; i--) {
			Node cur = Node(i, height[i]);
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
		long long ans = 0;
		for (int i = 1; i <= n; i++)
			ans = max(ans, (long long)(rig[i] + lef[i] - 1) * height[i]);
		cout << ans << endl;
	}
	return 0;
}
