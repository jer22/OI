#include <bits/stdc++.h>

using namespace std;

int n, k;
int arr[305];
int main() {
	freopen("e.in", "r", stdin);
	scanf("%d %d", &n, &k);
	for (int i = 1; i <= n; i++)
		scanf("%d", &arr[i]);
	unsigned long long tot = 0ull;
	unsigned long long now = 0ull;
	priority_queue<int, vector<int>, greater<int> > q;
	for (int i = 1; i <= k; i++)
		q.push(arr[i]);
	int t = k + 1;
	while (!q.empty()) {
		int cur = q.top();
		q.pop();
		tot += now + cur;
		now += cur;
		if (t <= n) q.push(arr[t++]);
	}
	cout << tot << endl;


	return 0;
}
