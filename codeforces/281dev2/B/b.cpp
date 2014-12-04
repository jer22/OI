#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int n;
vector<int> a;
vector<int> b;
long long sa = 0, sb = 0;
int main() {
	scanf("%d", &n);
	int t;
	for (int i = 0; i < n; i++) {
		scanf("%d", &t);
		if (t > 0) {
			a.push_back(t);
			sa += t;
		} else {
			b.push_back(-t);
			sb -= t;
		}
	}
	if (sa > sb) {
		printf("first\n");
		return 0;
	} else if (sa < sb) {
		printf("second\n");
		return 0;
	}
	int l = min(a.size(), b.size());
	for (int i = 0; i < l; i++) {
		if (a[i] > b[i]) {
			printf("first\n");
			return 0;
		} else if (a[i] < b[i]) {
			printf("second\n");
			return 0;
		}
	}
	if (a.size() > b.size()) {
		printf("first\n");
		return 0;
	} else if (a.size() < b.size()) {
		printf("second\n");
		return 0;
	}
	if (t > 0) {
		printf("first\n");
	} else {
		printf("second\n");
	}
 	return 0;
}
