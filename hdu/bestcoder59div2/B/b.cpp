#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

int T;
int n;
int arr[25];
int main() {
	freopen("b.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) {
			scanf("%d", &arr[i]);
		}
		int ans = 0;
		for (int x = n - 1; x >= 1; x--) {
			int mx = 0;
			for (int i = 1; i <= n; i++) {
				if (arr[i] != x) {
					mx = max(mx, arr[i]);
					continue;
				}
				if (mx < x) break;
				ans++;
				for (int j = i; j > 1; j--)
					arr[j] = arr[j - 1];
				arr[1] = x;
			}
		}
		printf("%d\n", ans);
	}


	return 0;
}
