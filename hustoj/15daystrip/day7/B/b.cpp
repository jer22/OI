#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

const int MAXN = 200005;

int n;
long long arr[MAXN];
int main() {
	freopen("b.in", "r", stdin);
	while (~scanf("%d", &n)) {
		if (!n) break;
		long long sum = 0;
		for (int i = 0; i < n; i++) {
			scanf("%lld", &arr[i]);
			sum ^= arr[i];
		}
		if (!sum) {
			printf("No\n");
			continue;
		}
		printf("Yes\n");
		for (int i = 0; i < n; i++) {
			long long t = sum ^ arr[i];
			if (t < arr[i]) {
				printf("%lld %lld\n", arr[i], t);
			}
		}
	}


	return 0;
}
