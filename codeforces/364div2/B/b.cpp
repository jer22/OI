#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int n, m;
int visx[100005], visy[100005];
int cntx = 0, cnty = 0;
int main() {
	// freopen("b.in", "r", stdin);
	cin >> n >> m;
	int a, b;
	long long sum = (long long)n * n;
	long long ocu = 0;
	for (int i = 1; i <= m; i++) {
		scanf("%d %d", &a, &b);
		if (!visx[a] && !visy[b]) {
			ocu += (n << 1) - 1;
			ocu -= cntx;
			ocu -= cnty;
		} else if (!visx[a]) {
			ocu += n;
			ocu -= cnty;
		} else if (!visy[b]) {
			ocu += n;
			ocu -= cntx;
		}


		if (!visx[a]) cntx++;
		if (!visy[b]) cnty++;
		visx[a] = visy[b] = 1;
		if (i != 1) printf(" ");
		cout << sum - ocu;
	}
	printf("\n");

	return 0;
}
