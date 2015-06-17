#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int T, n, a, b;
int arr[1000005], brr[1000005];
int nex[1000005];

void getnex(int *a) {
	memset(nex, 0, sizeof(nex));
	nex[0] = -1;
	int i = 0, j = -1;
	while (i < n) {
		if (j == -1 || a[i] == a[j])
			nex[++i] = ++j;
		else j = nex[j];
	}
}

int main() {
	freopen("a.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d %d", &n, &a, &b);
		for (int i = 0; i < n; i++) {
			scanf("%d", &arr[i]);
			brr[i] = arr[i] % b;
			arr[i] %= a;
			// cout << arr[i] << ' ';
		}
		getnex(arr);
		int ans = 0;
		if (!(n % (n - nex[n]))) ans = max(ans, n / (n - nex[n]));
		getnex(brr);
		if (!(n % (n - nex[n]))) ans = max(ans, n / (n - nex[n]));
		if (ans == 1) ans = 0;
		printf("%d\n", ans);
	}


	return 0;
}
