#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <string>

#define MOD 7

using namespace std;

int pow(int a, int b) {
	int ans = 1;
	while (b) {
		if (b & 1) {
			ans *= a;
			ans %= MOD;
		}
		a *= a;
		a %= MOD;
		b >>= 1;
	}
	return ans;
}

int T, n;
int arr[297];
string str[9] = {"Saturday", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};
int main() {
	freopen("j.in", "r", stdin);
	scanf("%d", &T);
	int sum = 0;
	for (int i = 1; i <= 294; i++) {
		sum += pow(i, i);
		sum %= 7;
		arr[i] = sum;
	}
	while (T--) {
		scanf("%d", &n);
		n = (n - 1) % 294 + 1;
		cout << str[arr[n]] << endl;
	}


	return 0;
}
