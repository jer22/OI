#include <bits/stdc++.h>

using namespace std;

int n;
int main() {
	// freopen("a.in", "r", stdin);
	cin >> n;
	if (n <= 2)	printf("1\n1\n");
	else if (n == 3) printf("2\n1 3\n");
	else if (n == 4) printf("4\n3 1 4 2\n");
	else {
		cout << n << endl;
		for (int i = 1; i <= n; i += 2)
			cout << i << ' ';
		for (int i = 2; i <= n; i += 2)
			cout << i << " \n"[i >= n - 1];
	}
	return 0;
}
