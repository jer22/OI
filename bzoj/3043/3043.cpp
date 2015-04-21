#include <bits/stdc++.h>

using namespace std;

int n;
long long arr[100005];
long long a, b;
int main() {
	freopen("3043.in", "r", stdin);
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> arr[i];
	for (int i = 1; i < n; i++)
		if (arr[i] > arr[i - 1]) a += arr[i] - arr[i - 1];
		else b += arr[i - 1] - arr[i];
	cout << max(a, b) << endl << abs(a - b) + 1 << endl;
	return 0;
}
