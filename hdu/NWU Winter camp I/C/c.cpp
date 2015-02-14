#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int main() {
	freopen("c.in", "r", stdin);
	int n;
	long long m;
	scanf("%d", &n);
	while (n--) {
		cin >> m;
		cout << m - 1 << "/" << m << endl;
	}

	return 0;
}
