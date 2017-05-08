#include <bits/stdc++.h>

using namespace std;

long long n;
long long arr[5][8];
long long solve[8];
long long sc[8] = {0, 500, 1000, 1500, 2000, 2500, 3000};
long long orisc[8];

long long rat[8] = {0, 1, 2, 4, 8, 16, 32, 0x3f3f3f3f};

long long cal(long long aa, long long bb, long long cc, long long dd, long long ee, int idx) {
	long long ans = 0;
	ans += (arr[idx][1] == -1) ? 0 : aa - aa / 250 * arr[idx][1];
	ans += (arr[idx][2] == -1) ? 0 : bb - bb / 250 * arr[idx][2];
	ans += (arr[idx][3] == -1) ? 0 : cc - cc / 250 * arr[idx][3];
	ans += (arr[idx][4] == -1) ? 0 : dd - dd / 250 * arr[idx][4];
	ans += (arr[idx][5] == -1) ? 0 : ee - ee / 250 * arr[idx][5];
	return ans;
}
long long getsco(int a, int b) {
	if (a * 32 <= b) return 3000;
	else if (a * 16 <= b) return 2500;
	else if (a * 8 <= b) return 2000;
	else if (a * 4 <= b) return 1500;
	else if (a * 2 <= b) return 1000;
	return 500;
}
int main() {
	freopen("b.in", "r", stdin);
	scanf("%lld", &n);
	long long a, b, c, d, e;
	for (long long i = 1; i <= n; i++) {
		scanf("%lld %lld %lld %lld %lld", &a, &b, &c, &d, &e);
		if (i <= 2) {
			arr[i][1] = a, arr[i][2] = b, arr[i][3] = c, arr[i][4] = d, arr[i][5] = e;
		}
		if (~a) solve[1]++;
		if (~b) solve[2]++;
		if (~c) solve[3]++;
		if (~d) solve[4]++;
		if (~e) solve[5]++;
	}
	for (long long i = 1; i <= 5; i++) {
		if (solve[i] * 32 <= n) orisc[i] = 3000;
		else if (solve[i] * 16 <= n) orisc[i] = 2500;
		else if (solve[i] * 8 <= n) orisc[i] = 2000;
		else if (solve[i] * 4 <= n) orisc[i] = 1500;
		else if (solve[i] * 2 <= n) orisc[i] = 1000;
		else orisc[i] = 500;
	}
	long long ans = 0x3f3f3f3f;
	long long aa, bb, cc, dd, ee;
	for (a = 500; a <= 3000; a += 500) { if (arr[1][1] == -1 && a < orisc[1]) continue;
		if (a == orisc[1]) aa = 0;
		else if (a > orisc[1]) {
			assert(solve[1] * rat[a / 500] >= n);
			aa = solve[1] * rat[a / 500] - n;
		} else {
			assert(solve[1] * rat[a / 500 + 1] <= n);
			aa = n - solve[1] * rat[a / 500 + 1] + 1;
		}
		for (b = 500; b <= 3000; b += 500) { if (arr[1][2] == -1 && b < orisc[2]) continue;
			if (b == orisc[2]) bb = 0;
			else if (b > orisc[2]) {
				assert(solve[2] * rat[b / 500] >= n);
				bb = solve[2] * rat[b / 500] - n;
			} else {
				assert(solve[2] * rat[b / 500 + 1] <= n);
				bb = n - solve[2] * rat[b / 500 + 1] + 1;
			}
			for (c = 500; c <= 3000; c += 500) { if (arr[1][3] == -1 && c < orisc[3]) continue;
				if (c == orisc[3]) cc = 0;
				else if (c > orisc[3]) {
					assert(solve[3] * rat[c / 500] >= n);
					cc = solve[3] * rat[c / 500] - n;
				} else {
					assert(solve[3] * rat[c / 500 + 1] <= n);
					cc = n - solve[3] * rat[c / 500 + 1] + 1;
				}
				for (d = 500; d <= 3000; d += 500) { if (arr[1][4] == -1 && d < orisc[4]) continue;
					if (d == orisc[4]) dd = 0;
					else if (d > orisc[4]) {
						assert(solve[4] * rat[d / 500] >= n);
						dd = solve[4] * rat[d / 500] - n;
					} else {
						assert(solve[4] * rat[d / 500 + 1] <= n);
						dd = n - solve[4] * rat[d / 500 + 1] + 1;
					}
					for (e = 500; e <= 3000; e += 500) { if (arr[1][5] == -1 && e < orisc[5]) continue;
						if (e == orisc[5]) ee = 0;
						else if (e > orisc[5]) {
							assert(solve[5] * rat[e / 500] >= n);
							ee = solve[5] * rat[e / 500] - n;
						} else {
							assert(solve[5] * rat[e / 500 + 1] <= n);
							ee = n - solve[5] * rat[e / 500 + 1] + 1;
						}
						long long s1 = cal(a, b, c, d, e, 1);
						long long s2 = cal(a, b, c, d, e, 2);
						// if (a == 500 && b == 1500 && c == 1000 && d == 1500 && e == 3000)
						// 	cout << s1 << ' ' << s2 << endl;
						if (s1 > s2) {
							long long t = max(aa, max(bb, max(cc, max(dd, ee))));
							bool f = true;
							if (arr[1][1] == -1 && getsco(solve[1], n + t) != a) f = false;
							if (arr[1][2] == -1 && getsco(solve[2], n + t) != b) f = false;
							if (arr[1][3] == -1 && getsco(solve[3], n + t) != c) f = false;
							if (arr[1][4] == -1 && getsco(solve[4], n + t) != d) f = false;
							if (arr[1][5] == -1 && getsco(solve[5], n + t) != e) f = false;
							if (f) {
								ans = min(ans, t);
								if (max(aa, max(bb, max(cc, max(dd, ee)))) == 1) {
									// cout << a << ' ' << b << ' ' << c << ' ' << d << ' ' << e << endl;
									// cout << s1 << ' ' << s2 << endl;
								}
								
							}
						}
					}
				}
			}
		}
	}
	// for (int i = 1; i <= 5; i++)
	// 	cout << orisc[i] << " \n"[i == 5];
	if (ans == 0x3f3f3f3f) ans = -1;
	cout << ans << endl;

	return 0;
}
