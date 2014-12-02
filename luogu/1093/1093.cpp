#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

struct Node{
	int num, chi, mat, eng, tot;
	bool operator < (const Node &n) const {
		if (tot != n.tot) return tot > n.tot;
		if (chi != n.chi) return chi > n.chi;
		return num < n.num;
	}
};

int n;
Node arr[10000];
int main() {
	freopen("1093.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d %d %d", &arr[i].chi, &arr[i].mat, &arr[i].eng);
		arr[i].num = i + 1;
		arr[i].tot = arr[i].chi + arr[i].mat + arr[i].eng;
	}
	sort(arr, arr + n);
	for (int i = 0; i < 5; i++) {
		printf("%d %d\n", arr[i].num, arr[i].tot);
	}
	
	return 0;
}

