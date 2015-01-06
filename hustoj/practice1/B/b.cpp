#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <map>

using namespace std;

int arr[100004];
int q, x;

int gcd(int a, int b) {
	while (b ^= a ^= b ^= a %= b);
	return a;
}

int main() {
	freopen("b.in", "r", stdin);
	int n;
	scanf("%d", &n);
	map<int, int> pre;
	map<int, long long> ans;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &arr[i]);
		map<int, int> nex;
		nex[arr[i]] = 1;
		ans[arr[i]]++;
		for (map<int, int>::iterator it = pre.begin(); it != pre.end(); it++) {
			int first = it -> first;
			int second = it -> second;
			nex[gcd(first, arr[i])] += second;
			ans[gcd(first, arr[i])] += second;
		}
		pre = nex;
	}
	scanf("%d", &q);
	for (int i = 1; i <= q; i++) {
		scanf("%d", &x);
		printf("%I64d\n", ans[x]);
	}

	return 0;
}
