#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

int n;
int arr[MAXN];
int main() {
	freopen("a.in", "r", stdin);
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> arr[i];
	int ans = 0;
	sort(arr + 1, arr + n + 1);
	for (int i = 2; i < n; i++)
		if (arr[i] > arr[1] && arr[i] < arr[n]) ans++;
	cout << ans << endl;


	return 0;
}
