/*
ID:shijiey1
PROG:ariprog
LANG:C++
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>

using namespace std;

struct Node{
	int a, b;
	bool operator < (const Node &n) const {
		if (b != n.b) return b < n.b;
		return a < n.a;
	}
};

int n, m;
int len = 0;
int arr[70000];
Node ans[10010];
int cnt = 0;
map<int, int> vis;
int done[200000];
int main() {
	freopen("ariprog.in", "r", stdin);
	freopen("ariprog.out", "w", stdout);
	scanf("%d %d", &n, &m);
	for (int i = 0; i <= m; i++) {
		for (int j = 0; j <= m; j++) {
			int t = i * i + j * j;
			// if (!vis[t]) {
			// 	vis[t] = 1;
			// 	arr[len++] = t;
			// }
			if (!done[t]) {
				done[t] = 1;
				arr[len++] = t;
			}
		}
	}
	sort(arr, arr + len);
	int now = 0;
	// 枚举首项
	for (int i = 0; i + n <= len; i++) {
		// 枚举第二项
		for (int j = i + 1; j + n - 1 <= len; j++) {
			if (arr[i] + (arr[j] - arr[i]) * (n - 1) > arr[len - 1]) {
				break;
			}
			int t = arr[j] - arr[i];
			now = 0;
			for (int k = arr[i]; k <= arr[len - 1]; k += t) {
				if (done[k]) {
					now++;
				} else {
					break;
				}
				if (now == n) {
					ans[cnt].a = arr[i];
					ans[cnt].b = t;
					cnt++;
					break;
				}
			}
		}
	}
	if (!cnt) {
		printf("NONE\n");
		return 0;
	}
	sort(ans, ans + cnt);
	for (int i = 0; i < cnt; i++) {
		printf("%d %d\n", ans[i].a, ans[i].b);
	}
	
	return 0;
}
