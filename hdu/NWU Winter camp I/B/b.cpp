#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int f[10005];
int main() {
	freopen("b.in", "r", stdin);
	f[1] = 0;
	f[2] = 1;
	int t = 1;
	for (int i = 3; i <= 9999; i++) {
		int end = i + t;
		t++;
		for (int j = i; j <= end; j++)
			f[j] = t;
		i = end;
	}
	int n;
	while (~scanf("%d", &n))
		cout << f[n] << endl;

	return 0;
}
