#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;

int T;
long long h, v;
int main() {
	freopen("1003.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		scanf("%lld %lld", &h, &v);
		double x = x = v * sqrt(v * v + 2 * 9.8 * h) / 9.8; 
		printf("%.2lf\n", x);
	}

	return 0;
}
