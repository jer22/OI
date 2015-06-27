#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int n;
int arr = 0;
int sum = 0;
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= 150; i++) {
		arr += i;
		sum += arr;
		if (sum > n) {
			printf("%d\n", i - 1);
			return 0;
		}
	}
	return 0;
}
