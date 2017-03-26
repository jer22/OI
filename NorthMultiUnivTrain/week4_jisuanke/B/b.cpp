#include <bits/stdc++.h>

using namespace std;

int T, n, m;
int arr[1000005], brr[1000005];
int main() {
	freopen("b.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &n, &m);
		bool f = 1;
		for (int i = 1; i <= n ; i++) {
			for (int j = 1; j <= m; j++) {
				scanf("%d", &arr[j]);
			}
			if (!f) continue;
			if (i != 1) {
				bool flag = (arr[1] != brr[1]);

				for (int j = 2; j <= m; j++) {
					if (arr[j] ^ flag != brr[j]) {
						f = 0;
						break;
					}
				}
				
			}
			for (int j = 1; j <= m; j++)
				brr[j] = arr[j];
		}
		if (f) printf("YES\n");
		else printf("NO\n");
	}

	return 0;
}
