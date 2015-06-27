#include <bits/stdc++.h>

using namespace std;

struct Node{
	int idx, deg, sum;
	Node() {}
	Node(int a, int b, int c) : idx(a), deg(b), sum(c) {}
	bool operator < (const Node &n) const {
		return deg < n.deg;
	}
};

int n;
Node nodes[65550];
int rec[65550];
vector<pair<int, int> > ans;

void hehe(int i) {
	ans.push_back(make_pair(nodes[i].idx, nodes[i].sum));
	nodes[i].deg--;
	nodes[rec[nodes[i].sum]].deg--;
	nodes[rec[nodes[i].sum]].sum ^= nodes[i].idx;
	if (nodes[rec[nodes[i].sum]].deg == 1) hehe(rec[nodes[i].sum]);
}

int main() {
	// freopen("a.in", "r", stdin);
	scanf("%d", &n);
	int deg, s;
	for (int i = 0; i < n; i++) {
		scanf("%d %d", &deg, &s);
		nodes[i] = Node(i, deg, s);
	}
	sort(nodes, nodes + n);
	for (int i = 0; i < n; i++)
		rec[nodes[i].idx] = i;
	for (int i = 0; i < n; i++) {
		if (nodes[i].deg == 1) {
			hehe(i);
		}
		
	}
	int siz = ans.size();
	printf("%d\n", siz);
	for (int i = 0; i < siz; i++) {
		printf("%d %d\n", ans[i].first, ans[i].second);
	}
	return 0;
}
