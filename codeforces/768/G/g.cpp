#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

int n;
int root;
vector<int> edges[MAXN];
multiset<int> parent, children, outer;
int siz[MAXN], maxson[MAXN];
bool big[MAXN];
int ans[MAXN];

void prefuck(int x) {
	siz[x] = 1;
	ans[x] = n - 1;
	for (auto nex : edges[x]) {
		prefuck(nex);
		siz[x] += siz[nex];
		if (siz[nex] > siz[maxson[x]])
			maxson[x] = nex;
	}
	outer.insert(siz[x]);
}

void fuck(int x) {
	children.insert(siz[x]);
	outer.erase(outer.find(siz[x]));
	for (auto nex : edges[x])
		if (!big[nex]) fuck(nex);
}

void cao(int x) {
	outer.insert(siz[x]);
	children.erase(children.find(siz[x]));
	for (auto nex : edges[x])
		if (!big[nex]) cao(nex);
}

void gggg(multiset<int> &st, int l, int r, int mi, int x, int offset) {
	if (mi == n - 1) return;
	int mx = r;
	while(r - l > 1){
        int mid = (r + l) / 2;
        auto it = st.lower_bound(mx - mid + offset);
        if(it == st.end()) 
            l = mid;
        else if(mi + *it <= mid + offset) 
            r = mid;
        else 
            l = mid;
    }
    ans[x] = min(ans[x], r);
}

void dfs(int x, bool keep) {
	parent.insert(siz[x]);
	outer.erase(outer.find(siz[x]));
	int mx = -1, se = -1, mi = n - 1;
	for (auto nex : edges[x]) {
		if (siz[nex] > mx) se = mx, mx = siz[nex];
		else se = max(se, siz[nex]);
		mi = min(mi, siz[nex]);
	}
	if (x != root) mi = min(mi, n - siz[x]);
	for (auto nex : edges[x])
		if (nex != maxson[x]) dfs(nex, 0);
	if (maxson[x]) dfs(maxson[x], 1), big[maxson[x]] = 1;
	if (mx >= n - siz[x]) {
		se = max(se, n - siz[x]);
		gggg(children, se - 1, mx, mi, x, 0);
	}
	outer.insert(siz[x]);
	fuck(x);
	parent.erase(parent.find(siz[x]));
	if (n - siz[x] > mx) {
		se = mx;
		gggg(outer, se - 1, n - siz[x], mi, x, 0);
		gggg(parent, se - 1, n - siz[x], mi, x, siz[x]);
	}
	if (maxson[x]) big[maxson[x]] = 0;
	if (!keep) cao(x);
}

int main() {
	freopen("g.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 1, a, b; i <= n; i++) {
		scanf("%d %d", &a, &b);
		if (a) edges[a].push_back(b);
		else root = b;
	}
	prefuck(root);
	dfs(root, 0);
	for (int i = 1; i <= n; i++)
		printf("%d\n", ans[i]);


	return 0;
}
