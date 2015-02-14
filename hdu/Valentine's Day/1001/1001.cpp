#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <climits>
#include <map>

using namespace std;

int n;
map<long long, int> val;
long long arr[105];
int num[105];
int main() {
	int cas = 1;
	freopen("1001.in", "r", stdin);
	while (~scanf("%d", &n)) {
		if (n == 1) {
			printf("Case #%d: %d\n", cas++, -1);
			return 0;
		}
		val.clear();
		long long x;
		for (int i = 0; i < n; i++) {
			scanf("%lld", &x);
			val[x]++;
		}
		int tot = 0;
		memset(num, 0, sizeof(num));
		memset(arr, 0, sizeof(arr));
		for (map<long long, int>::iterator it = val.begin(); it !=val.end(); it++) {
			arr[tot] = it -> first;
			num[tot++] = it -> second;
		}
		num[tot] = num[0];
		arr[tot++] = arr[0];
		num[tot] = num[1];
		arr[tot] = arr[1];
		int ans = 0;
		for (int i = 1; i < tot; i++) {
			if ((arr[i - 1] + arr[i]) % INT_MAX == arr[i + 1]) ans += num[i];
			// cout << num[i] << endl;
		}
		printf("Case #%d: %d\n", cas++, ans);
	}


	return 0;
}
