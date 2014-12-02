#include <cstdio>
#include <cstring>
#include <algorithm>

#define MAXN 100010

using namespace std;

int n;
double H,S1,V,L,K;
double ball[MAXN][2];
double car[MAXN][2];
int main() {
	freopen("1033.in", "r", stdin);
	scanf("%lf%lf%lf%lf%lf%d", &H, &S1, &V, &L, &K, &n);
	memset(ball, 0, sizeof(ball));
	memset(car, 0, sizeof(car));
	double t1 = H / 5;
	double t2 = (H - K) / 5;
	for (int i = 0; i < n; i++) {
		ball[i][0] = t1;
		ball[i][1] = t2;
		car[i][0] = ((S1 - i) / V) * ((S1 - i) / V);
		car[i][1] = ((S1 + L - i) / V) * ((S1 + L - i) / V);
	}
	for (int i = 0; i < n; i++) {
		printf("%lf %lf %lf %lf\n", ball[i][0], ball[i][1], car[i][0], car[i][1]);
	}
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		if (ball[i][1] <= car[i][1] && ball[i][0] >= car[i][0]) {
			cnt++;
		}
	}
	printf("%d\n", cnt);
	return 0;
}
