#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

struct point {
	int pos, stat;
	bool operator < (const point &p) const {
		if (pos != p.pos) return pos < p.pos;
		return stat > p.stat;
	}
};

using namespace std;

int T;
vector<point> pp;
int main() {
	freopen("1002.in", "r", stdin);
	scanf("%d", &T);
	int n;
	while (T--) {
		pp.clear();
		scanf("%d", &n);
		int a, b;
		point t;
		for (int i = 0; i < n; i++) {
			scanf("%d %d", &a, &b);
			t.pos = a;
			t.stat = 1;
			pp.push_back(t);
			t.pos = b;
			t.stat = -1;
			pp.push_back(t);
		}
		sort(pp.begin(), pp.end());
		int len = pp.size();
		int ans = 0;
		int maxans = 0;
		for (int i = 0; i < len; i++) {
			ans += pp[i].stat;
			maxans = max(ans, maxans);
		}
		printf("%d\n", maxans);
	}


	return 0;
}
