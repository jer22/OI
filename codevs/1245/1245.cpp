#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>
#include <map>

using namespace std;

int n;
int arr[100005];
int brr[100005];

struct Node{
	int x, y, sum;
	Node() {}
	Node(int a, int b, int c) : x(a), y(b), sum(c) {}
	bool operator < (const Node &n) const {
		return sum > n.sum;
	}
};

map<int, bool> vis[100005];
int main() {
	freopen("1245.in", "r", stdin);
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> arr[i];
	for (int i = 1; i <= n; i++)
		cin >> brr[i];
	sort(arr + 1, arr + n + 1);
	sort(brr + 1, brr + n + 1);
	priority_queue<Node> q;
	q.push(Node(1, 1, arr[1] + brr[1]));
	int k = n;
	while (k--) {
		Node cur = q.top();
		q.pop();
		cout << cur.sum << " \n"[!k];
		if (cur.x + 1 <= n) {
			if (!vis[cur.x + 1][cur.y]) {
				vis[cur.x + 1][cur.y] = 1;
				q.push(Node(cur.x + 1, cur.y, arr[cur.x + 1] + brr[cur.y]));
			}
		}
		if (cur.y + 1 <= n) {
			if (!vis[cur.x][cur.y + 1]) {
				vis[cur.x][cur.y + 1] = 1;
				q.push(Node(cur.x, cur.y + 1, arr[cur.x] + brr[cur.y + 1]));
			}
		}
	}
	return 0;
}
