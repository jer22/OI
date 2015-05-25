#include <bits/stdc++.h>

using namespace std;

int n, m;
int k[2005];
vector<int> edges[2005];
int deg[2005], temp[2005], ans[2005];

struct Node{
	int a;
	Node() {}
	Node(int b) : a(b) {}
	bool operator < (const Node &n) const {
		return k[a] < k[n.a];
	}
};

int work(int x) {
	memcpy(temp, deg, sizeof(temp));
	priority_queue<Node> q;
	for (int i = 1; i <= n; i++)
		if (i != x && !temp[i]) q.push(Node(i));
	for (int i = n; i >= 1; i--) {
		if (q.empty()) return n - i;
		int t = q.top().a;
		q.pop();
		if (k[t] < i) return n - i;
		ans[i] = t;
		for (int j = 0; j < edges[t].size(); j++) {
			if (!--temp[edges[t][j]] && edges[t][j] != x) q.push(Node(edges[t][j]));
		}
	}
	return n;
}

int main() {
	freopen("2535.in", "r", stdin);
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%d", &k[i]);
	int a, b;
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &a, &b);
		edges[b].push_back(a);
		deg[a]++;
	}
	work(0);
	for (int i = 1; i <= n; i++) {
		printf("%d", ans[i]);
		if (i != n) printf(" ");
		else printf("\n");
	}
	for (int i = 1; i <= n; i++) {
		printf("%d", n - work(i));
		if (i != n) printf(" ");
		else printf("\n");
	}

	return 0;
}
