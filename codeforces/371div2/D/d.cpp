#include <bits/stdc++.h>

using namespace std;

int n;
long long lef[3], rig[3], up[3], down[3];
long long ver[6], hor[6];

int query(long long a, long long b, long long c, long long d) {
	int t;
	cout << "? " << a << ' ' << b << ' ' << c << ' ' << d << endl;
	fflush(stdout);
	cin >> t;
	return t;
}

void callef() {
	for (int x = 2; x >= 1; x--) {
		long long l = 1, r = n;
		while (l < r) {
			long long m = (l + r >> 1) + 1;
			int t = query(1, m, n, n);

			if (t < x) r = m - 1;
			else l = m;
		}
		lef[x] = l;
		ver[x] = l;
	}
}

void calrig() {
	for (int x = 2; x >= 1; x--) {
		long long l = 1, r = n;
		while (l < r) {
			long long m = l + r >> 1;
			int t = query(1, 1, n, m);
			if (t < x) l = m + 1;
			else r = m;
		}
		rig[x] = l;
		ver[x + 2] = l;
	}
}

void calup() {
	for (int x = 2; x >= 1; x--) {
		long long l = 1, r = n;
		while (l < r) {
			long long m = (l + r >> 1) + 1;
			int t = query(m, 1, n, n);
			if (t < x) r = m - 1;
			else l = m;
		}
		up[x] = l;
		hor[x] = l;
	}
}

void caldown() {
	for (int x = 2; x >= 1; x--) {
		long long l = 1, r = n;
		int t;
		while (l < r) {
			long long m = l + r >> 1;
			int t = query(1, 1, m, n);
			if (t < x) l = m + 1;
			else r = m;
		}
		down[x] = l;
		hor[x + 2] = l;
	}
}

struct Node{
	long long x1, yy, x2, y2;
	long long s;
	Node() {}
	Node(long long a, long long b, long long c, long long d, long long e) : x1(a), yy(b), x2(c), y2(d), s(e) {}
	bool operator < (const Node &n) const {
		return s < n.s;
	}
};

vector<Node> vv;
Node ans[2];

bool check(Node x) {
	return !(x.x1 <= ans[0].x1 && x.yy <= ans[0].yy && x.x2 >= ans[0].x2 && x.y2 >= ans[0].y2);
}

int main() {
	// freopen("d.in", "r", stdin);
	cin >> n;
	callef();
	calrig();
	calup();
	caldown();
	sort(ver + 1, ver + 5);
	sort(hor + 1, hor + 5);
	for (int i = 1; i <= 3; i++)
		for (int j = 1; j <= 3; j++)
			for (int k = i + 1; k <= 4; k++)
				for (int l = j + 1; l <= 4; l++)
					if (query(hor[i], ver[j], hor[k], ver[l]))
						vv.push_back(Node(hor[i], ver[j], hor[k], ver[l], (hor[k] - hor[i] + 1) * (ver[l] - ver[j] + 1)));
	sort(vv.begin(), vv.end());
	ans[0] = vv[0];
	for (int i = 1; i < vv.size(); i++) {
		if (check(vv[i])) {
			ans[1] = vv[i];
			break;
		}
	}
	cout << "! " << ans[0].x1 << ' ' << ans[0].yy << ' ' << ans[0].x2 << ' ' << ans[0].y2
		<< ' ' << ans[1].x1 << ' ' << ans[1].yy << ' ' << ans[1].x2 << ' ' << ans[1].y2 << endl;
	fflush(stdout);
	return 0;
}
