#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

struct Node{
	int a, b, id;
	Node() {}
	Node(int x, int y, int z) : a(x), b(y), id(z) {}
	bool operator < (const Node &n) const {
		if (a - b != n.a - n.b) return a - b > n.a - n.b;
		if (b != n.b) return b < n.b;
		return id < n.id;
	}
};

int n;
Node arr[105];
int main() {
	freopen("1001.in", "r", stdin);
	while (~scanf("%d", &n)) {
		int a, b;
		for (int i = 0; i < n; i++) {
			scanf("%d %d", &a, &b);
			arr[i] = Node(a, b, i);
		}
		sort(arr, arr + n);
		for (int i = 0; i < n; i++) {
			cout << arr[i].id << " \n"[i == n - 1];
		}
	}


	return 0;
}
