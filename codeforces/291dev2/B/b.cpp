#include <bits/stdc++.h>

using namespace std;

struct Node{
	long long a, b;
	Node() {}
	Node(long long x, long long y) : a(x), b(y) {}
};

long long n, sx, sy;
Node arr[1005];
int parent[1005];
bool vis[1005];
int find(int p) {
	if (p == parent[p]) return p;
	return parent[p] = find(parent[p]);
}

void un(int p, int q) {
	parent[find(p)] = find(q);
}

bool equals(Node a, Node b) {
	return a.a * b.b == a.b * b.a;
}

int main() {
	// freopen("b.in", "r", stdin);
	cin >> n >> sx >> sy;
	long long x, y;
	for (int i = 0; i < n; i++) {
		cin >> x >> y;
		arr[i] = Node(x - sx, y - sy);
	}
	int ans = 0;
	for (int i = 0; i <= n; i++) parent[i] = i;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < i; j++) {
			if (equals(arr[i], arr[j])) un(i, j);
		}
	}
	int t = -1;
	for (int i = 0; i < n; i++) {
		if (!vis[parent[i]]) {
			ans++;
			vis[parent[i]] = 1;
		}
	}
	cout << ans << endl;
	return 0;
}
