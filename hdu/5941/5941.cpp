#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2005;
const double INF = INFINITY;
const double eps = 1e-7;

struct Seg{
	double l, r;	//(l, r)
	double u, v, w;	//u*x+v/x+w
	bool mi;		//if contain the global extremum
	double pos;		//global extremum's x coordinate(if mi == true)
	Seg() {}
	Seg(double a, double b, double c, double d, double e, bool f = false)
		: l(a), r(b), u(c), v(d), w(e), mi(f) {}
	void judgemi() {
		double p = sqrt(v / u);
		if (l - eps <= p && p - eps <= r) {
			pos = p;
			mi = true;
		}
	}
	double getval() {
		return u * pos + v / pos + w;
	}
};

int T, n;
double a[MAXN];
vector<Seg> segs[MAXN];

Seg getseg(Seg pre, double now) {
	Seg s = Seg(now / pre.r, now / pre.l, pre.v / now + 1, now * pre.u, pre.w);
	s.judgemi();
	return s;
}

void solve() {
	Seg nex;
	for (int i = 3; i <= n; i++) {
		segs[i].clear();
		for (int j = (int)segs[i - 1].size() - 1; j >= 0; j--) {
			Seg cur = segs[i - 1][j];
			if (cur.mi) {
				Seg tmp = cur;
				tmp.l = cur.pos;
				tmp.mi = false;
				segs[i].push_back(getseg(tmp, a[i]));

				tmp.l = 0;
				tmp.r = cur.pos;
				tmp.u = tmp.v = 0;
				tmp.w = cur.getval();
				segs[i].push_back(getseg(tmp, a[i]));
				break;
			} else {
				segs[i].push_back(getseg(cur, a[i]));
			}
		}
	}
	for (int i = 0; i < segs[n].size(); i++) {
		if (segs[n][i].mi) {
			printf("%.5lf\n", segs[n][i].getval());
			break;
		}
	}
}

int main() {
	// freopen("5941.in", "r", stdin);
	scanf("%d", &T);
	for (int cas = 1; cas <= T; cas++) {
		scanf("%d", &n);
		printf("Case #%d: ", cas);
		if (n == 1) printf("0.00000\n");
		else {
			for (int i = 2; i <= n; i++)
				scanf("%lf", &a[i]);
			segs[2].clear();
			segs[2].push_back(Seg(0, INF, 1, a[2], 0, 1));	//b2=x+a2/x
			segs[2][0].judgemi();
			// cout << segs[3].size();
			solve();
		}
	}
	return 0;
}
