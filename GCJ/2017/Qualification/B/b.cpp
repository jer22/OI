#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <stack>

using namespace std;

long long n;
int arr[20];

int main() {
	// freopen("b.in", "r", stdin);
	// freopen("out", "w", stdout);
	int T;
	scanf("%d", &T);
	stack<int> s;
	for (int cas = 1; cas <= T; cas++) {
		printf("Case #%d: ", cas);
		cin >> n;
		long long nn = n;
		while (n) {
			s.push(n % 10);
			n /= 10;
		}
		int len = 0;
		while (!s.empty()) {
			arr[++len] = s.top();
			s.pop();
		}
		int idx = -1;
		for (int i = 2; i <= len; i++) {
			if (arr[i - 1] > arr[i]) {
				idx = i - 1;
				break;
			}
		}
		if (idx == -1) cout << nn << endl;
		else {
			arr[idx]--;
			while (arr[idx] < arr[idx - 1]) {
				arr[idx - 1]--;
				idx--;
			}
			for (int i = idx + 1; i <= len; i++) arr[i] = 9;
			bool f = 0;
			for (int i = 0; i <= len; i++) {
				if (!f && !arr[i]) continue;
				f = 1;
				cout << arr[i];
			}
			cout << endl;
		}


	}


	return 0;
}
