#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

struct Gas{
	double dist, cost;
	bool operator < (const Gas &g) const {
		return dist < g.dist;
	}
};

double D1, C, D2, P;
int N;
Gas sta[1111111];
double far;
double ans = 0;
void find(int i, int k) {
	if (i == N) return;
	bool flag = false;
	int j;
	for (j = i + 1; j <= N; j++) {
		if (sta[j].dist - sta[i].dist > far) break;
		if (sta[j].cost <= sta[i].cost) {
			flag = true;
			break;
		}
	}
	if (flag) {
		double req = (sta[j].dist - sta[i].dist) / D2;
		if (k < req) {
			ans += sta[i].cost * (req - k);
			k = req;
		}
		find(j, k - req);
	} else {
		if (sta[N].dist - sta[i].dist <= far) {
			double req = (sta[N].dist - sta[i].dist) / D2;
			if (k < req) {
				ans += sta[i].cost * (req - k);
				k = req;
			}
			find(N, k - req);
		} else {
			ans += sta[i].cost * (C - k);
			int nex;
			double minnum = 111111111.0;
			for (j = i + 1; j <= N; j++) {
				if (sta[j].dist - sta[i].dist > far) break;
				if (sta[j].cost < minnum) {
					nex = j;
					minnum = sta[j].cost;
				}
			}
			double req = (sta[nex].dist - sta[i].dist) / D2;
			find(j, C - req);
		}
	}

}

int main() {
	freopen("1016.in", "r", stdin);
	cin >> D1 >> C >> D2 >> P >> N;
	sta[0].cost = P;
	sta[0].dist = 0;
	double a, b;
	for (int i = 1; i <= N; i++) {
		cin >> sta[i].dist >> sta[i].cost;
	}
	sta[N + 1].dist = D1;
	sta[N + 1].cost = 0;
	sort(sta, sta + N + 1);
	N++;
	far = C * D2;
	for (int i = 0; i <= N; i++) {
		if (sta[i].dist == D1) {
			N = i;
			break;
		}
	}
	for (int i = 1; i <= N; i++) {
		if (sta[i].dist - sta[i - 1].dist > far) {
			printf("No Solution\n");
			return 0;
		}
	}
	find(0, 0);
	printf("%.2lf\n", ans);


	return 0;
}
