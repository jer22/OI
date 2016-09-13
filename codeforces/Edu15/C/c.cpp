#include <bits/stdc++.h>

using namespace std;

int n, m;
long long arr[100005];
long long brr[100005];
int main() {
	freopen("c.in", "r", stdin);
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		cin >> arr[i];
	long long a;
	for (int i = 1; i <= m; i++) {
		cin >> brr[i];
	}
	brr[0] = -10000000000000000;
	brr[m + 1] = 10000000000000000;
	int idx = 0;
	
	long long ans = 0;
	for (int i = 1; i <= n; i++) {
		while (idx < m && brr[idx + 1] < arr[i]) idx++;
		ans = max(ans, min(arr[i] - brr[idx], brr[idx + 1] - arr[i]));
		
	}
	cout << ans << endl;

	return 0;
}
