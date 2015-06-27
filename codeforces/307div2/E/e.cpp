#include <bits/stdc++.h>

#define pli pair<long long, int>
#define mp(i, j) make_pair(i, j)

using namespace std;

const int MAXN = 500005;

int n, q;
long long arr[MAXN];
int blocks;
long long tag[MAXN];

vector<pli > mi[770], mx[770];

void rebuild(int id) {
	mi[id].clear();
	mx[id].clear();
	for (int i = id * blocks; i < (id + 1) * blocks && i < n; i++) {
		arr[i] += tag[id];
		mi[id].push_back(mp(arr[i], i));
		mx[id].push_back(mp(arr[i], -i));
	}
	sort(mi[id].begin(), mi[id].end());
	sort(mx[id].begin(), mx[id].end());
	tag[id] = 0;
}

int getmin(long long v) {
	for (int i = 0; i < blocks; i++) {
		long long t = v - tag[i];
		vector<pli >::iterator it = lower_bound(mi[i].begin(), mi[i].end(), mp(t, 0));
		if (it != mi[i].end() && (it -> first == t)) return it -> second;
	}
	return -1;
}

int getmax(long long v) {
	for (int i = blocks - 1; i >= 0; i--) {
		long long t = v - tag[i];
		vector<pli >::iterator it = lower_bound(mx[i].begin(), mx[i].end(), mp(t, -10000000));
		if (it != mx[i].end() && (it -> first == t)) return -it -> second;
	}
	return -1;
}

int main() {
	cin >> n >> q;
	blocks = sqrt(n) + 2;
	for (int i = 0; i < n; i++)
		cin >> arr[i];
	for (int i = 0; i < blocks; i++)
		rebuild(i);
	int op, l, r;
	long long v;
	for (int i = 0; i < q; i++) {
		cin >> op;
		if (op == 1) {
			cin >> l >> r >> v;
			l--, r--;
			if (l / blocks == r / blocks) {
				for (int j = l; j <= r; j++)
					arr[j] += v;
				rebuild(l / blocks);
			} else {
				int id = l / blocks + 1;
				while (l / blocks != id) {
					arr[l++] += v;
				}
				rebuild(l / blocks - 1);
				while (l + blocks < r) {
					tag[l / blocks] += v, l += blocks;
				}
				while (l <= r) arr[l++] += v;
				rebuild(r / blocks);
			}
		} else {
			cin >> v;
			l = getmin(v);
			r = getmax(v);
			if (l < 0) cout << -1 << endl;
			else cout << r - l << endl;
		}
	}
	return 0;
}
