#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <vector>
#include <map>

using namespace std;

int n, m;
int arr[1000005];
int shu[1000005];
int num[1000005];


int main() {
	srand(time(0));
	freopen("1002.in", "w", stdout);
	printf("1000000 1000000\n");
	int t;
	for (int i = 0; i < 1000000; i++) {
		t = rand() % 1000000000 + 1;
		cout << t << " \n"[i == 1000000 - 1];
	}
	for (int i = 0; i < 1000000; i++) {
		t = rand() % 1000000000 + 1;
		cout << t << " \n"[i == 1000000 - 1];
	}
	
	return 0;
}
