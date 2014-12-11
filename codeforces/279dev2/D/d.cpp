#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

struct Factor{
	int t1, t2, m;
	Factor() {
		t1 = t2 = m = 0;
	}
};

Factor fact(int n) {
	Factor factor = Factor();
	while (!(n % 3)) {
		factor.t2++;
		n /= 3;
		n <<= 1;
	}
	while (!(n % 2)) {
		factor.t1++;
		n >>= 1;
	}
	factor.m = n;
	return factor;
}

int getres(Factor f) {
	int n = f.m;
	while (f.t1--) {
		n <<= 1;
	}
	while (f.t2--) {
		n *= 3;
		n >>= 1;
	}
	return n;
}

int a, b, c, d;
int main() {
	cin >> a >> b >> c >> d;
	Factor fa = fact(a);
	Factor fb = fact(b);
	Factor fc = fact(c);
	Factor fd = fact(d);
	if (fa.m * fb.m != fc.m * fd.m) {
		cout << -1 << endl;
		return 0;
	}
	int ans1 = min(fa.t1 + fb.t1, fc.t1 + fd.t1);
	int res1 = max(fa.t1 + fb.t1, fc.t1 + fd.t1);
	int ans2 = min(fa.t2 + fb.t2, fc.t2 + fd.t2);
	int res2 = max(fa.t2 + fb.t2, fc.t2 + fd.t2);
	int cnt1 = res1 - ans1;
	int cnt2 = res2 - ans2;
	cout << cnt1 + cnt2 << endl;
	if (res2 == fa.t2 + fb.t2) {
		while (cnt2 && fa.t2) {
			cnt2--;
			fa.t2--;
		}
		while (cnt2 && fb.t2) {
			cnt2--;
			fb.t2--;
		}
	} else {
		while (cnt2 && fc.t2) {
			cnt2--;
			fc.t2--;
		}
		while (cnt2 && fd.t2) {
			cnt2--;
			fd.t2--;
		}
	}
	if (res1 == fa.t1 + fb.t1) {
		while (cnt1 && fa.t1) {
			cnt1--;
			fa.t1--;
		}
		while (cnt1 && fb.t1) {
			cnt1--;
			fb.t1--;
		}
	} else {
		while (cnt1 && fc.t1) {
			cnt1--;
			fc.t1--;
		}
		while (cnt1 && fd.t1) {
			cnt1--;
			fd.t1--;
		}
	}
	while (fa.t1 < fa.t2) {
		fa.t1++;
		fb.t1--;
	}
	while (fb.t1 < fb.t2) {
		fb.t1++;
		fa.t1--;
	}
	while (fc.t1 < fc.t2) {
		fc.t1++;
		fd.t1--;
	}
	while (fd.t1 < fd.t2) {
		fd.t1++;
		fc.t1--;
	}
	a = getres(fa);
	b = getres(fb);
	c = getres(fc);
	d = getres(fd);
	cout << a << ' ' << b << endl;
	cout << c << ' ' << d << endl;
	return 0;
}
