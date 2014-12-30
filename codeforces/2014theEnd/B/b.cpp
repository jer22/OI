#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int n;
int arr[305];
int edges[305][305];
int connt[305][305];
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &arr[i]);
	}
	char c;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> c;
			edges[i][j] = c - '0';
		}
	}
	for (int k = 1; k <= n; k++) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				edges[i][j] = max(edges[i][j], edges[i][k] & edges[j][k]);
			}
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (!edges[i][j]) continue;
			if (i < j && arr[i] > arr[j]) swap(arr[i], arr[j]);
			else if (i > j && arr[i] < arr[j]) swap(arr[i], arr[j]);
		}
	}
	for (int i = 1; i <= n; i++) {
		printf("%d", arr[i]);
		if (i == n) printf("\n");
		else printf(" ");
	}

	return 0;
}
