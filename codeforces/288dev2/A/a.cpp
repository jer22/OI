#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int n, m, k;
int arr[1005][1005];
bool vis[1005][1005];
int main() {
	// freopen("a.in", "r", stdin);
	cin >> n >> m >> k;
	int a, b;
	bool flag = false;
	for (int i = 1; i <= k; i++) {
		cin >> a >> b;
		if (vis[a][b]) continue;
		vis[a][b] = 1;
		arr[a][b]++;
		arr[a - 1][b - 1]++;
		arr[a][b - 1]++;
		arr[a - 1][b]++;
		if (arr[a][b] == 4 || arr[a - 1][b] == 4 || arr[a][b - 1] == 4 || arr[a - 1][b - 1] == 4) {
			cout << i << endl;
			flag = true;
			break;
		}
	}
	if (!flag) cout << 0 << endl;
	return 0;
}
