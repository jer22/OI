#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <climits>
#include <vector>

using namespace std;

const int MAXN = 100005;
const int MAXM = 128;

int n;
char s[MAXN];
int sa[MAXN], rank[MAXN], height[MAXN], tmp[MAXN];
int ST[MAXN][20];
struct Node{
	int id, c[2];
} Count[MAXN], Count_b[MAXN];

void getSA() {
	memset(tmp, 0, sizeof(tmp));
	for (int i = 0; i < n; i++) tmp[s[i]]++;
	for (int i = 1; i < MAXM; i++) tmp[i] += tmp[i - 1];
	for (int i = 0; i < n; i++) rank[i] = tmp[s[i] - 1];
	int j = 0;
	while ((1 << j) < n) {
		for (int i = 0; i < n; i++) {
			Count[i].id = i;
			Count[i].c[0] = rank[i];
			Count[i].c[1] = ((i + (1 << j)) >= n) ? -1 : rank[i + (1 << j)];
		}
		for (int i = 1; i >= 0; i--) {
			memset(tmp, 0, sizeof(tmp));
			for (int j = 0; j < n; j++) tmp[Count[j].c[i] + 1]++;
			for (int j = 1; j < MAXN; j++) tmp[j] += tmp[j - 1];
			for (int j = n - 1; j >= 0; j--) Count_b[--tmp[Count[j].c[i] + 1]] = Count[j];
			for (int j = 0; j < n; j++) Count[j] = Count_b[j];
		}
		rank[Count[0].id] = 0;
		for (int i = 1; i < n; i++) {
			rank[Count[i].id] = rank[Count[i - 1].id];
			if (Count[i].c[0] != Count[i - 1].c[0] || Count[i].c[1] != Count[i - 1].c[1])
				rank[Count[i].id]++;
		}
		j++;
	}
	for (int i = 0; i < n; i++) sa[rank[i]] = i;
}

void getHeight() {
	int k = 0, j;
	for (int i = 0; i < n; height[rank[i++]] = k) {
		if (!rank[i]) k = 0;
		else {
			for (k ? k-- : 0, j = sa[rank[i] - 1]; s[i + k] == s[j + k]; k++)
				if (i + k == n - 1 || j + k == n - 1) {
					k++;
					break;
				}
		}
	}
}

void RMQ() {
	for (int i = 0; i < n; i++)
		ST[i][0] = height[i];
	for (int j = 1; (1 << j) <= n; j++) {
		for (int i = 0; i + (1 << j) - 1 < n; i++)
			ST[i][j] = min(ST[i][j - 1], ST[i + (1 << j - 1)][j - 1]);
	}
}

int LCP(int a, int b) {
	int x = rank[a], y = rank[b];
	if (x > y) swap(x, y);
	x++;
	int k = log(y - x + 1) / log(2);
	return min(ST[x][k], ST[y - (1 << k) + 1][k]);
}

int f[MAXN];
struct node{
	int idx, len;
	node() {}
	node(int a, int b) : idx(a), len(b) {}
};
vector<node> v;
int main() {
	freopen("3693.in", "r", stdin);
	while (~scanf("%s", s)) {
		if (s[0] == '#') break;
		n = strlen(s);
		getSA();
		getHeight();
		RMQ();
		int ans = 0;
		memset(f, 0, sizeof(f));
		v.clear();
		for (int l = 1; l <= n / 2; l++) {
			for (int j = 0; j < (n - 1) / l; j++) {
				int x = j * l, y = (j + 1) * l;
				int z = LCP(x, y);
				if (ans < z / l + 1) {
					ans = z / l + 1;
					v.clear();
					v.push_back(node(x, z));
				} else if (ans == z / l + 1) v.push_back(node(x, z));

				if (z % l) {
					z = LCP(x - (l - z % l), y - (l - z % l));
					if (ans < z / l + 1) {
						ans = z / l + 1;
						cout << x << ' ' << y << ' ' << z << '|' << endl;
						// cout << z << endl;

						v.clear();
						v.push_back(node(x - (l - z % l), z));
					} else if (ans == z / l + 1) v.push_back(node(x - (l - z % l), z));
				}
			}
		}
		// cout << ans << endl;
		// for (int l = 1; l < n / 2; l++)
		// 	ans = max(ans, f[l]);
		// for (int l = 1; l < n / 2; l++) {
		// 	if (f[l] == ans) {
		// 		cout << l << endl;
		// 	}
		// }
		int siz = v.size();
		int idx;
		int rk = 0x3f3f3f3f;
		for (int i = 0; i < siz; i++) {
			cout << v[i].idx << ' ' << v[i].len << endl;
			if (rank[v[i].idx] < rk) {
				rk = rank[v[i].idx];
				idx = i;
			}
		}
		int len = v[idx].len;
		idx = v[idx].idx;
		for (int i = idx; i < idx + len; i++)
			cout << s[i];
		cout << endl;
	}

	return 0;
}
