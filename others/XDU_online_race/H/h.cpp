#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <map>

using namespace std;

int n;
int arr[1005];
map<int, bool> vis;
int main() {
	freopen("h.in", "r", stdin);
	while (~scanf("%d", &n)) {
		vis.clear();
		for (int i = 1; i <= n; i++) {
			scanf("%d", &arr[i]);
			vis[arr[i]] = 1;
		}
		sort(arr + 1, arr + n + 1);
		bool flag = false;
		for (int i = 1; i <= n; i++) {
			if (arr[i] > 0) break;
			for (int j = i + 1; j <= n; j++) {
				int k = -arr[i] - arr[j];
				if (k == arr[i] || k <= arr[j]) continue;
				if (vis[k]) {
					flag = 1;
					printf("%d %d %d\n", arr[i], arr[j], k);
				}
			}
		}
		if (!flag) printf("Ren Chou Jiu Gai Duo Du Shu!\n");
	}


	return 0;
}
