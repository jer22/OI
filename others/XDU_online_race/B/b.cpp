#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

#define MOD 1000000007

using namespace std;

int T, n;
int arr[1000005];
int main() {
	freopen("b.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; i++)
			scanf("%d", &arr[i]);
		int ans = 0;
		for (int num = 0; num <= 9; num++) {
			int sum = 0;
			for (int i = 1; i <= n; i++) {
				if (arr[i] == num) {
					ans += sum;
					ans %= MOD;
				}
				if (arr[i] > num) sum++;
			}
		}
		printf("%d\n", ans);
	}


	return 0;
}
