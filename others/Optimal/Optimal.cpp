#include <iostream>

using namespace std;

int arr[2002];
double re = 0.0f;

int cmp(const void* a, const void* b) {
	return *(int *)a - *(int *)b;
}

int main( void ) {
	freopen("Optimal.in", "r", stdin);
	freopen("Optimal.out", "w", stdout);
	int n, s;
	scanf("%d %d", &n, &s);
	int i, j = n / s + 1;
	for (i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}
	qsort(arr, n, sizeof(arr[0]), cmp);
	for (i = 0; i < n; i++) {
		if (!(i % s))
			j--;
		re += arr[i] * j;
	}
	re /= 10;
	cout << re << endl;
	return 0;
}
