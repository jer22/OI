#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int main() {
	srand(time(0));
	freopen("1078.in", "w", stdout);
	printf("100 100\n");
	for (int i = 1; i <= 100; i++) {
		for (int j = 1; j <= 100; j++) {
			int a = rand() % 101;
			if (i==1 && j==1) a=0;
			cout << a << ' ';
		}
		cout << endl;
	}
	printf("-1 -1\n");
	return 0;
}
