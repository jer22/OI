#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <hash_map>
#include <cmath>

using namespace std;

int v[100000];
long long getSum(int range) {
	hash_map<int, long> m;
	int r = sqrt(range);
	int p = range / r;
	memset(v, 0, sizeof(v));
	int k = r + 1;
	for (int i = 1; i < k; i++)
		v[i - 1] = range / i;
	int cnt = 1;
	int len = r + p - 1;
	for (int i = r + p - 2; i >= r; i--)
		v[i] = cnt++;
	for (int i = 0; i < len; i++)
		m[v[i]] = (long long)v[i] * (v[i] + 1) / 2 - 1;
	for (p = 2; p < r + 1; p++) {
		if (m[p] > m[p - 1]) {
			int sp = m[p - 1];
			int p2 = (long long)p * p;
			for (int i = 0; i < len; i++) {
				if (v[i] < p2) break;
				long long t = m[v[i]];
				m[v[i]] = t - p * (m[v[i] / p]) - sp;
			}

		}
	}
	return m[range];
}

int main() {
	cout << getSum(1000000000);

	return 0;
}
