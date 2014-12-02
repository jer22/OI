#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int T;
int main() {
	freopen("1001.in", "r", stdin);
	scanf("%d", &T);
	int n;
	int arr[110];
	
	while (T--) {
		memset(arr, 0, sizeof(arr));
		scanf("%d", &n);
		int t;
		for (int i = 0; i < n; i++) {
			scanf("%d", &t);
			arr[t]++;
		}
		int maxx = -1;
		int idx = 1;
		for (int i = 1; i <= n; i++) {
			if (arr[i] > maxx) {
				maxx = arr[i];
				idx = i;
			}
		}
		printf("%d\n", idx);
	}


	return 0;
}
