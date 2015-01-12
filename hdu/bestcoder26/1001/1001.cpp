#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

int n, m;
int main() {
	freopen("1001.in", "r", stdin);
	while (~scanf("%d %d", &n, &m)) {
		m--;
		printf("%d\n", m % n);
	}



	return 0;
}
