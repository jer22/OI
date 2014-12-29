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

int n, m;
char str[1005][1005];
int up[1005][1005][3];
int lef[1005], rig[1005];
void init() {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (str[i][j] == 'a' || str[i][j] == 'w' || str[i][j] == 'y' || str[i][j] == 'z')
				up[i][j][0] = up[i - 1][j][0] + 1;
			else up[i][j][0] = 0;
			if (str[i][j] == 'b' || str[i][j] == 'w' || str[i][j] == 'x' || str[i][j] == 'z')
				up[i][j][1] = up[i - 1][j][1] + 1;
			else up[i][j][1] = 0;
			if (str[i][j] == 'c' || str[i][j] == 'x' || str[i][j] == 'y' || str[i][j] == 'z')
				up[i][j][2] = up[i - 1][j][2] + 1;
			else up[i][j][2] = 0;
		}
	}
}

int getAns(int x) {
	int ans = 0;
	stack<Node> sr, sl;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			Node cur = Node(j, up[i][j][x]);
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
			Node cur = Node(j, up[i][j][x]);
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
			ans = max(ans, up[i][j][x] * (lef[j] + rig[j] - 1));
		}
	}
	return ans;
}

int main() {
	freopen("2870.in", "r", stdin);
	while (~scanf("%d %d", &n, &m)) {
		for (int i = 1; i <= n; i++)
			scanf("%s", str[i] + 1);
		init();
		cout << max(getAns(0), max(getAns(1), getAns(2))) << endl;
	}
	return 0;
}
