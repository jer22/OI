#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

#define unsigned unsigned long long

using namespace std;

const int MAXN = 200005;

int n; 
int k;
long long arr[MAXN];
int main() {
	freopen("1186.in", "r", stdin);
	while (~scanf("%d", &n)) {
		for (int i = 1; i <= n; i++) {
			for (int j = 0; j < 26 - i; j++)
				printf(" ");
			for (int j = 'A'; j < 'A' + i; j++)
				printf("%c", j);
			for (int j = 'A' + i - 2; j >= 'A'; j--)
				printf("%c", j);
			printf("\n");
		}
	}


	return 0;
}



