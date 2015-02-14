#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int n;
long long f[50];
int main() {
	freopen("d.in", "r", stdin);
	f[1] = 1;
	for (int i = 2; i <= 45; i++)
		f[i] = f[i - 1] + f[i - 2];
	while (~scanf("%d", &n)) {
		cout << f[n] << endl;
	}

	return 0;
}
