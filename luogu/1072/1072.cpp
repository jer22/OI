#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

#define INF 0x3f3f3f3f

using namespace std;

long long GCD(long long a, long long b) {
	long long t;
	if (!a || !b)
		return 0;
	if (a < b) {
		t = a;
		a = b;
		b = t;
	}
	if (!(a % b)) {
		return b;
	} else {
		return GCD(b, a % b);
	}
}

long long LCM(long long a, long long b) {
	return a * b / GCD(a, b);
}

struct divisor {
	int num;
	int minPower;
	int maxPower;
};

int n;
int a, b, c, d;
int prime[50000];
int primeNum = 0;

vector<divisor> divis(int a) {
	vector<divisor> v;
	divisor d;
	int num, power = 0;
	int idx = 0;
	while (true) {
		num = prime[idx];
		if (!num) {
			d.num = a;
			d.minPower = 1;
			d.maxPower = 1;
			v.push_back(d);
			break;
		}
		if (!(a % num)) {
			power++;
			a /= num;
		} else {
			if (power) {
				d.num = num;
				d.minPower = power;
				d.maxPower = power;
				v.push_back(d);

			}
			idx++;
			power = 0;
			if (a == 1)
				break;
		}
	}
	return v;
}

int main() {
	freopen("1072.in", "r", stdin);
	int p[50000];
	memset(p, 0, sizeof(p));
	memset(prime, 0, sizeof(prime));
	p[1] = 1;
	for (int i = 2; i < 50000; i++) {
		if (!p[i]) {
			for (int j = i << 1; j < 50000; j += i) {
				p[j] = 1;
			}
		}
	}
	for (int i = 2; i < 50000; i++) {
		if (!p[i])
			prime[primeNum++] = i;
	}
	scanf("%d", &n);
	int cnt = 1;
	for (int i = 0; i < n; i++) {
		cnt = 1;
		scanf("%d %d %d %d", &a, &b, &c, &d);
		vector<divisor> va = divis(a);
		vector<divisor> vb = divis(b);
		vector<divisor> vc = divis(c);
		vector<divisor> vd = divis(d);

		// for (int j = 0; j < va.size(); j++) {
		// 	printf("%d %d\n", va[j].num, va[j].minPower);
		// }
		// printf("-------\n");
		// for (int j = 0; j < vb.size(); j++) {
		// 	printf("%d %d\n", vb[j].num, vb[j].minPower);
		// }
		// printf("-------\n");
		// for (int j = 0; j < vc.size(); j++) {
		// 	printf("%d %d\n", vc[j].num, vc[j].minPower);
		// }
		// printf("-------\n");
		// for (int j = 0; j < vd.size(); j++) {
		// 	printf("%d %d\n", vd[j].num, vd[j].minPower);
		// }
		// printf("-------\n");
		int t1 = 0, t2 = 0;
		vector<divisor> v;
		divisor d;

		for (int j = 0; j < vd.size(); j++) {
			if (t1 < vc.size() && vd[j].num == vc[t1].num) {
				d.num = vd[j].num;
				d.minPower = vc[t1].minPower;
				d.maxPower = vc[t1].maxPower;
				v.push_back(d);
				t1++;
			} else {
				d.num = vd[j].num;
				d.minPower = 0;
				d.maxPower = 0;
				v.push_back(d);
			}
		}
		vc = v;
		v.clear();
		t1 = 0;
		for (int j = 0; j < va.size(); j++) {
			if (t1 < vb.size() && va[j].num == vb[t1].num) {
				d.num = va[j].num;
				d.minPower = vb[t1].minPower;
				d.maxPower = vb[t1].maxPower;
				v.push_back(d);
				t1++;
			} else {
				d.num = va[j].num;
				d.minPower = 0;
				d.maxPower = 0;
				v.push_back(d);
			}
		}
		vb = v;
		v.clear();
		t1 = 0;
		// for (int j = 0; j < va.size(); j++) {
		// 	printf("%d %d | ", va[j].num, va[j].minPower);
		// }
		// printf("\n");
		// for (int j = 0; j < vb.size(); j++) {
		// 	printf("%d %d | ", vb[j].num, vb[j].minPower);
		// }
		// printf("\n");
		// for (int j = 0; j < vc.size(); j++) {
		// 	printf("%d %d | ", vc[j].num, vc[j].minPower);
		// }
		// printf("\n");
		// for (int j = 0; j < vd.size(); j++) {
		// 	printf("%d %d | ", vd[j].num, vd[j].minPower);
		// }
		// printf("\n");
		bool flag = false;
		for (int j = 0; j < va.size() + vc.size(); j++) {
			if (t1 < va.size() || t2 < vc.size()) {
				if (va.size() != t1 && vc.size() != t2 &&va[t1].num == vc[t2].num) {
					d.num = va[t1].num;
					d.minPower = vb[t1].minPower;
					if (va[t1].minPower > vb[t1].minPower) {
						d.maxPower = vb[t1].minPower;
					} else {
						d.maxPower = INF;
					}
					int mi, ma;
					mi = 0;
					ma = vd[t2].minPower;
					if (vc[t2].minPower < vd[t2].minPower) {
						mi = vd[t2].minPower;
					}
					d.minPower = max(d.minPower, mi);
					d.maxPower = min(d.maxPower, ma);
					if (d.minPower > d.maxPower) {
						flag = true;
						break;
					}
					v.push_back(d);
					t1++;
					t2++;
				} else if (t1 == va.size() || va[t1].num > vc[t2].num) {
					d.num = vc[t2].num;
					d.minPower = 0;
					d.maxPower = vd[t2].minPower;
					if (vc[t2].minPower < vd[t2].minPower) {
						d.minPower = vd[t2].minPower;
					}
					v.push_back(d);
					t2++;
				} else if (t2 == vc.size() || va[t1].num < vc[t2].num) {
					d.num = va[t1].num;
					d.minPower = vb[t1].minPower;
					d.maxPower = INF;
					if (va[t1].minPower > vb[t1].minPower) {
						d.maxPower = vb[t1].minPower;
					}
					v.push_back(d);
					t1++;
				}
			}
		}
		for (int j = 0; j < v.size(); j++) {
			if (v[j].maxPower == INF || v[j].maxPower < v[j].minPower) {
				flag = true;
				break;
			}
		}
		if (flag) {
			printf("0\n");
		} else {
			for (int j = 0; j < v.size(); j++) {
				// printf("%d %d %d\n", v[j].num, v[j].minPower, v[j].maxPower);
				cnt *= v[j].maxPower - v[j].minPower + 1;
			}
			printf("%d\n", cnt);
		}
		// for (int j = 0; j < v.size(); j++) {
		// 	printf("%d %d %d\n", v[j].num, v[j].minPower, v[j].maxPower);
		// }

	}

	// vector<divisor> v = divis(1);
	// for (int j = 0; j < v.size(); j++) {
	// 	printf("%d %d\n", v[j].num, v[j].minPower);
	// }
	return 0;
}
