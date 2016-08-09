#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>
#include <set>

#define pii pair<int, int>
#define mp(i, j) make_pair(i, j)

using namespace std;

struct Node{
	set<pii, bool> m;
};

int n, m;
set<pii > start;

bool check(set<pii > cur) {
	for (set<pii >::iterator it = cur.begin(); it != cur.end(); it++) {
		if ((cur.find(mp(it -> first - 1, it -> second)) != cur.end())
			&& (cur.find(mp(it -> first, it -> second - 1)) != cur.end())
			&& (cur.find(mp(it -> first - 1, it -> second - 1)) != cur.end()))
			return false;
	}
	return true;
}

bool solve(set<pii > cur) {
	if (check(cur))
		return false;
	for (set<pii >::iterator it = cur.begin(); it != cur.end(); it++) {
		// cout << it -> first << ' ' << it -> second << endl;
		if ((cur.find(mp(it -> first - 1, it -> second)) != cur.end())
			&& (cur.find(mp(it -> first, it -> second - 1)) != cur.end())
			&& (cur.find(mp(it -> first - 1, it -> second - 1)) != cur.end())) {
			set<pii > nex = cur;
			nex.erase(mp(it -> first, it -> second));
			nex.erase(mp(it -> first - 1, it -> second));
			nex.erase(mp(it -> first, it -> second - 1));
			nex.erase(mp(it -> first - 1, it -> second - 1));
			if (!solve(nex)) return true;
		}
	}
	return false;
}

int main() {
	// freopen("g.in", "r", stdin);
	while (~scanf("%d %d", &n, &m)) {
		char str[55];
		start.clear();
		for (int i = 0; i < n; i++) {
			scanf("%s", str);
			for (int j = 0; j < m; j++) {
				if (str[j] == '0') {
					start.insert(mp(i, j));
					// cout << i << ' ' << j << endl;
				}
			}
		}
		bool ans = solve(start);
		if (ans) printf("Yes\n");
		else printf("No\n");
	}


	return 0;
}
