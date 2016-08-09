#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>

#define pii pair<int, int>
#define mp(i, j) make_pair(i, j)

using namespace std;

const int MAXN = 1000005;

vector<pii > m;
bool vis[MAXN];
// map<pii, bool> ok;
int nex[MAXN], pre[MAXN];
pii sam[MAXN];
void init() {
	m.push_back(mp(0, 0));
	// ok.insert(mp(mp(0, 0), 1));
	vis[0] = 1;
	int now = 1;
	sam[0] = mp(0, 0);
	for (int i = 1; i <= 1000000; i++) {
		while (vis[now]) now++;
		if (now + i > 1000000) break;
		m.push_back(mp(now, now + i));
		// ok.insert(mp(mp(now, now + i), 1));
		vis[now] = 1;
		vis[now + i] = 1;
		nex[now] = now + i;
		pre[now + i] = now;
		sam[i] = mp(now, now + i);
	}
}

int main() {
	freopen("c.in", "r", stdin);
	init();
	int a, b;
	while (~scanf("%d %d", &a, &b)) {
		if (!a && !b) break;
		if (pre[b] && pre[b] == a) printf("0\n");
		else {
			printf("1\n");
			if (!a) printf("0 0\n");
			pii t = sam[b - a];
			if (t.first <= a && t.second <= b)
				printf("%d %d\n", t.first, t.second);
			if (nex[a] && nex[a] <= b) printf("%d %d\n", a, nex[a]);
			if (pre[a]) printf("%d %d\n", pre[a], a);
			if (a != b && pre[b] && pre[b] <= a) printf("%d %d\n", pre[b], b);
		}
	}



	return 0;
}
