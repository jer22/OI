#include <bits/stdc++.h>

using namespace std;

int n;
int arr[300005];
int main() {
	freopen("b.in", "r", stdin);
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> arr[i];
	sort(arr + 1, arr + n + 1);
	cout << arr[n + 1 >> 1] << endl;
	return 0;
}
