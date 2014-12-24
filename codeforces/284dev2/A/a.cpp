#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Node{
	int l, r;
	Node(int a, int b) : l(a), r(b) {}
};

int n, x;
int arr[100010];
vector<Node> node;
int main() {
	// freopen("a.in", "r", stdin);
	scanf("%d %d", &n, &x);
	int a, b;
	int ed = 0;
	for (int i = 0; i < n; i++) {
		cin >> a >> b;
		node.push_back(Node(a, b));
	}
	int ans = 0;
	int pos = 1;
	for (int i = 0; i < n; i++) {
		while (pos + x <= node[i].l) pos += x;
		ans += node[i].r - pos + 1;
		pos = node[i].r + 1;
	}
	cout << ans << endl;

	return 0;
}
