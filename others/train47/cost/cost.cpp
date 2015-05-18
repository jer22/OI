#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int n, k;
int t[35];
int fa[35];

queue<int> q;
bool solve(int day) {
	while (!q.empty()) q.pop();
	for (int i = 1; i <= n; i++)
		if (!fa[i]) q.push(i);


}

int main() {
	freopen("cost.in", "r", stdin);
	scanf("%d %d", &n, &k);
	for (int i = 1; i <= n; i++)
		scanf("%d", &t[i]);
	int x, y;
	while (~scanf("%d %d", &x, &y))
		fa[y] = x;

	for (int i = 1; i <= n; i++)
		cout << solve(i) << endl;


	return 0;
}
