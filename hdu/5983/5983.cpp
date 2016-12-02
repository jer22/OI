#include <bits/stdc++.h>

using namespace std;

int T;
int arr[26];
int op[][12] = {
	{0, 2, 4, 6, 8, 10, 12, 14, 16, 17, 19, 18},
	{1, 3, 5, 7, 9, 11, 13, 15, 20, 21, 23, 22},
	{0, 1, 20, 21, 11, 10, 16, 17, 12, 13, 15, 14},
	{2, 3, 22, 23, 9, 8, 18, 19, 4, 5, 7, 6},
	{17, 19, 4, 5, 22, 20, 15, 14, 0, 1, 3, 2},
	{16, 18, 6, 7, 23, 21, 13, 12, 8, 9, 11, 10}
};
bool fin() {
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 3; j++)
			if (arr[i * 4 + j] != arr[i * 4 + j + 1]) return false;
	return true;
}

void change(int x) {
	int a = arr[op[x][0]], b = arr[op[x][1]];
	for (int i = 0; i < 6; i += 2)
		arr[op[x][i]] = arr[op[x][i + 2]], arr[op[x][i + 1]] = arr[op[x][i + 3]];
	arr[op[x][6]] = a, arr[op[x][7]] = b;
	a = arr[op[x][8]];
	for (int i = 8; i < 11; i++)
		arr[op[x][i]] = arr[op[x][i + 1]];
	arr[op[x][11]] = a;
}
void rchange(int x) {
	int a = arr[op[x][6]], b = arr[op[x][7]];
	for (int i = 6; i > 0; i -= 2)
		arr[op[x][i]] = arr[op[x][i - 2]], arr[op[x][i + 1]] = arr[op[x][i - 1]];
	arr[op[x][0]] = a, arr[op[x][1]] = b;
	a = arr[op[x][11]];
	for (int i = 11; i > 8; i--)
		arr[op[x][i]] = arr[op[x][i - 1]];
	arr[op[x][8]] = a;
}

bool check() {
	for (int i = 0; i < 6; i++) {
		change(i);
		if (fin()) return true;
		rchange(i);
		rchange(i);
		if (fin()) return true;
		change(i);
	}
	return false;
}

int main() {
	freopen("5983.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		for (int i = 0; i < 24; i++)
				scanf("%d", &arr[i]);
		if (fin()) {
			printf("YES\n");
			continue;
		}
		if (check()) printf("YES\n");
		else printf("NO\n");
		
	}


	return 0;
}
