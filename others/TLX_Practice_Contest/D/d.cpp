#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int n;
vector<long long> arr[105];
long long sum[105][50005];
int main() {
	// freopen("d.in", "r", stdin);
	scanf("%d", &n);
	long long a, b;
	for (int i = 0; i < n; i++) {
		scanf("%lld %lld", &a, &b);
		arr[a].push_back(b);
	}
	for (int i = 1; i <= 100; i++) {
		sort(arr[i].begin(), arr[i].end());
		for (int j = 0; j < arr[i].size(); j++)
			sum[i][j + 1] = sum[i][j] + arr[i][j];
	}
	long long ans = 0;
	for (int i = 1; i <= 100; i++) {
		if (arr[i].empty()) continue;
		for (int j = i + 1; j <= 100; j++) {
			if (arr[j].empty()) continue;
			int pos = 0;
			for (int e = 0; e < arr[i].size(); e++) {
				long long now = arr[i][e];
				int len = arr[j].size();
				while (arr[j][pos] <= now && pos < len) pos++;
				// cout << i << ' ' << j << ' ' << now << ' ' << pos << endl;
				// cout << now;
				ans += (j - i) * (now * (long long)pos - sum[j][pos]);

				ans += (j - i) * (sum[j][len] - sum[j][pos] - (long long)(len - pos) * now);
			}
		}
	}
	printf("%lld\n", ans);

	return 0;
}
