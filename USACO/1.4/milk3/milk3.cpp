/*
ID:shijiey1
PROG:milk3
LANG:C++
*/

/*
dfs水题
用三维的vis数组记录当前状态是否枚举过。
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

int a, b, c;
int vis[25][25][25];
priority_queue<int, vector<int>, greater<int> > q;
void dfs(int x, int y, int z) {
	if (vis[x][y][z]) return;
	vis[x][y][z] = 1;
	if (!x) {
		q.push(z);
	}
	// a倒入b
	if (x + y <= b) dfs(0, x + y, z);
	else dfs(x + y - b , b, z);
	// a倒入c
	if (x + z <= c) dfs(0, y, x + z);
	else dfs(x + z - c , y, c);
	// b倒入a
	if (x + y <= a) dfs(x + y, 0, z);
	else dfs(a, x + y - a, z);
	// b倒入c
	if (y + z <= c) dfs(x, 0, y + z);
	else dfs(x, y + z - c, c);
	// c倒入a
	if (x + z <= a) dfs(x + z, y, 0);
	else dfs(a, y, x + z - a);
	// c倒入b
	if (y + z <= b) dfs(x, y + z, 0);
	else dfs(x, b, y + z - b);
}

int main() {
	freopen("milk3.in", "r", stdin);
	freopen("milk3.out", "w", stdout);
	scanf("%d %d %d", &a, &b, &c);
	dfs(0, 0, c);
	bool flag = false;
	while (!q.empty()) {
		if (flag) printf(" ");
		else flag = true;
		printf("%d", q.top());
		q.pop();
	}
	printf("\n");
	return 0;
}
