#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

long long C[55][55];

int main() {
	freopen("1002.in", "r", stdin);
	for (int i = 1; i <= 50; i++)
		C[i][0] = C[i][i] = 1;
	for (int i = 2; i <= 50; i++)
		for (int j = 1; j < i; j++)
			C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]);
	for (int i = 1; i <= 50; i++) {
		for (int j = 1; j <= i; j++) {
			printf("%-5d", C[i][j]);
		}
		cout << endl;
	}
	

	return 0;
}
