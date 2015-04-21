#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int n, m, d, l;
vector<int> cars;
int hei[50005];
int main() {
	freopen("1623.in", "r", stdin);
	scanf("%d %d %d %d", &n, &m, &d, &l);
	int t;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &t);
		t -= l;
		if (t >= 0) {
			t /= d;
			cars.push_back(t);
		}
	}
	sort(cars.begin(), cars.end());
	int ans = 0;
	for (int i = 0; i < cars.size(); i++) {
		int t = cars[i];
		for (int j = 0; j < m; j++) {
			if (hei[j] <= t) {
				hei[j]++;
				ans++;
				break;
			}
		}
	}
	printf("%d\n", ans);

	return 0;
}
