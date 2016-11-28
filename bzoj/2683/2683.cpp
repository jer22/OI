#include <bits/stdc++.h>

#define lowbit(x) ((x) & (-(x)))

using namespace std;

const int MAXN = 500005;
const int MAXM = 200005;

struct Node{
	int x, y, v, type;
	Node() {}
	Node(int a, int b, int c, int d) : x(a), y(b), v(c), type(d) {}
	bool operator < (const Node &n) const {
		return x < n.x;
	}
};

int n, tot = 0;
Node querys[MAXM << 2];
vector<int> q;
int ans[MAXM << 2];
int c[MAXN];
void insert(int pos, int x) {
	for (int i = pos; i < MAXN; i += lowbit(i))
		c[i] += x;
}
int getans(int pos) {
	int ans = 0;
	for (int i = pos; i; i -= lowbit(i))
		ans += c[i];
	return ans;
}

vector<int> his;
void solve(int l, int r) {
	if (l == r) return;
	int mid = l + r >> 1;
	solve(l, mid);
	solve(mid + 1, r);
	sort(querys + l, querys + mid + 1);
	sort(querys + mid + 1, querys + r + 1);
	int i = l, j = mid + 1;
	his.clear();
	while (j <= r) {
		while (i <= mid && querys[i].type == 2) i++;
		while (j <= r && querys[j].type == 1) j++;
		if (i <= mid && querys[i].x <= querys[j].x) {
			insert(querys[i].y, querys[i].v);
			his.push_back(i++);
		} else if (j <= r) {
			ans[querys[j].v] += getans(querys[j].y);
			j++;
		}
	}
	for (i = 0; i < his.size(); i++)
		insert(querys[his[i]].y, -querys[his[i]].v);
}

int main() {
	freopen("2683.in", "r", stdin);
	scanf("%d", &n);
	int op, a, b, c, d;
	while (~scanf("%d", &op)) {
		if (op == 3) break;
		if (op == 1) {
			scanf("%d %d %d", &a, &b, &c);
			querys[++tot] = Node(a, b, c, 1);
		} else {
			scanf("%d %d %d %d", &a, &b, &c, &d);
			q.push_back(tot + 1);
			querys[++tot] = Node(c, d, tot, 2);
			querys[++tot] = Node(a - 1, b - 1, tot, 2);
			querys[++tot] = Node(c, b - 1, tot, 2);
			querys[++tot] = Node(a - 1, d, tot, 2);
		}
	}
	solve(1, tot);
	for (int i = 0; i < q.size(); i++) {
		// cout << ans[q[i] + 3] << endl;
		printf("%d\n", ans[q[i]] + ans[q[i] + 1] - ans[q[i] + 2] - ans[q[i] + 3]);
	}

	return 0;
}
