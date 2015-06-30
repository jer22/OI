#include <bits/stdc++.h>

using namespace std;

int n;
double w;
int arr[200005];
int main() {
	// freopen("b.in", "r", stdin);
	cin >> n >> w;
	for (int i = 1; i <= n * 2; i++)
		cin >> arr[i];
	double mi = w / 3 / n;
	sort(arr + 1, arr + n + n + 1);
	mi = min(mi, (double)arr[1]);
	mi = min(mi, (double)arr[n + 1] / 2);

	printf("%f\n", mi * n * 3);

	return 0;
}
