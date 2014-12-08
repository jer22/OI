/*
ID:shijiey1
PROG:wormhole
LANG:C++
*/

/*
先用dfs枚举每一种配对，在判断是否有环。
next：每个点右边的第一个点是谁。如果右边没有点则为自己
pair:与每个点配对的点
如何判断有环：
对于每一种配对，枚举每一个第一次进入的点，然后递归处理，下一次递归的点是当前点配对的点的右边的点.
如果一个点进入了两次，则说明有环。如果某个点配对的点的next就是它配对的点则说明无环。
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

struct Node {
	int x, y, pair, next;
	bool operator < (const Node &n) const {
		return x < n.x;
	}
};

int n;
Node nodes[15];
int vis[15];
int cnt = 0;

int done[15];
bool isLoop(int cur) {
	if (nodes[nodes[cur].pair].next == nodes[cur].pair) {
		return false;
	}
	if (done[cur])
		return true;
	done[cur] = 1;
	return isLoop(nodes[nodes[cur].pair].next);
}

void makePair(int last) {
	// 配对完成，判断是否有环
	if (!last) {
		for (int i = 0; i < n; i++) {
			memset(done, 0, sizeof(done));
			if (isLoop(i)) {
				cnt++;
				break;
			}
		}
		return;
	}
	// 配对的第一个点
	int t;
	for (int i = 0; i < n; i++) {
		if (!vis[i]) {
			vis[i] = 1;
			t = i;
			break;
		}
	}
	// 配对的第二个点
	for (int i = t + 1; i < n; i++) {
		if (!vis[i]) {
			vis[i] = 1;
			nodes[i].pair = t;
			nodes[t].pair = i;
			makePair(last - 1);
			vis[i] = 0;
		}
	}
	vis[t] = 0;
}

int main() {
	freopen("wormhole.in", "r", stdin);
	freopen("wormhole.out", "w", stdout);
	scanf("%d", &n);
	int x, y;
	for (int i = 0; i < n; i++) {
		scanf("%d %d", &nodes[i].x, &nodes[i].y);
	}
	sort(nodes, nodes + n);
	for (int i = 0; i < n; i++) {
		nodes[i].pair = i;
		nodes[i].next = i;
	}
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (nodes[j].y == nodes[i].y) {
				nodes[i].next = j;
				break;
			}
		}
	}
	makePair(n >> 1);
	printf("%d\n", cnt);

	return 0;
}
