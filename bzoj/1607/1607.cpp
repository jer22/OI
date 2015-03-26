#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

const int MAX = 1000000;

int n;
int cnt[1000005];
int arr[1000005];
int ans[1000005];
int main() {
	freopen("1607.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
		cnt[arr[i]]++;
	}

	for (int i = 0; i < n; i++) {
		int t = sqrt(arr[i]);
		for (int j = 1; j <= t; j++) {
			if (!(arr[i] % j)) {
				if (arr[i] != 1) ans[i] += cnt[j];
				else ans[i] += cnt[j] - 1;
				if (j != arr[i] / j) {
					if (j != 1) ans[i] += cnt[arr[i] / j];
					else ans[i] += cnt[arr[i] / j] - 1;
				}
			}
		}
	}
	for (int i = 0; i < n; i++)
		printf("%d\n", ans[i]);
	return 0;
}
