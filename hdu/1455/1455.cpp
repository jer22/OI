#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int n;
int arr[66], sum;
int tot, length;
bool vis[66];

bool dfs(int pos, int cnt, int len) {
	// cout << cnt << endl;
	if (cnt == tot) return true;


	for (int i = pos; i >= 1; i--) {
		if (vis[i]) continue;
		if (len + arr[i] < length) {
			vis[i] = 1;
			if (dfs(pos - 1, cnt, len + arr[i])) return true;
			vis[i] = 0;
			if (!len) return false;
			while (arr[i - 1] == arr[pos]) i--;
		} else if (len + arr[i] == length) {
			vis[i] = 1;
			if (dfs(n, cnt + 1, 0)) return true;
			vis[i] = 0;
			return false;
		}
		
	}
	return false;
}

int main() {
	freopen("1455.in", "r", stdin);
	while (~scanf("%d", &n)) {
		if (!n) break;
		sum = 0;
		for (int i = 1; i <= n; i++) {
			scanf("%d", &arr[i]);
			sum += arr[i];
		}
		
		sort(arr + 1, arr + n + 1);
		for (int i = arr[n]; i <= sum; i++) {
			if (sum % i) continue;
			length = i;
			tot = sum / i;
			memset(vis, 0, sizeof(vis));
			if (dfs(n, 0, 0)) {
				printf("%d\n", i);
				break;
			}
		}

	}


	return 0;
}
