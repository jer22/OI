#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

struct Node{
	long long v, a;
	long long s;
};

int n, m;
long long t;
Node arr[105];
int main() {
	freopen("d.in", "r", stdin);
	while (cin >> n >> m >> t) {
		for (int i = 1; i <= n; i++) {
			cin >> arr[i].a;
			arr[i].v = 0;
			arr[i].s = 0;
		}
		for (int cas = 0; cas < m; cas++) {
			int idx = 1;
			long long ans = 0;
			for (int i = 1; i <= n; i++) {
				long long v0 = arr[i].v;
				long long a = arr[i].a;
				arr[i].s += v0 * t * 2ll + (a * t * t);
				if (arr[i].s > ans) {
					ans = arr[i].s;
					idx = i;
				}
				arr[i].v += a * t;
			}
			arr[idx].v = 0;
			cout << idx << " \n"[cas == m - 1];
		}
	}
	return 0;
}
