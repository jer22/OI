#include <cstdio>
#include <iostream>
#include <map>

using namespace std;

const int MAXN = 50005;

map<long long, bool> vis;
int main() {
	freopen("2761.in", "r", stdin);
	int T, n;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		bool f = false;
		vis.clear();
		long long a;
		for (int i = 0; i < n; i++) {
			scanf("%lld", &a);
			if (!vis[a]) {
			if (f) printf(" ");
				vis[a] = 1;
				printf("%lld", a);
				f = true;
			}
		}
		printf("\n");
		
	}

	return 0;
}
