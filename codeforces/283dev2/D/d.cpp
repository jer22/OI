#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Point{
	int a, b;
	Point(int c, int d) : a(c), b(d) {}
};

int n;
int arr[100011];
int cnt = 0;
vector<Point> ans;

bool check(int b, int a) {
	int s[3] = {0, 0, 0};
	int t[3] = {0, 0, 0};
	for (int i = 0; i < n; i++) {
		s[arr[i]]++;
		if (s[1] == a) {
			t[1]++;
			s[1] = s[2] = 0;
		} else if (s[2] == a) {
			t[2]++;
			s[1] = s[2] = 0;
		}
		if (t[2] == b) return false;
		if (t[1] == b) {
			if (i < n - 1) return false;
			else return true;
		}
	}
	return false;
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
		if (arr[i] == 1) cnt++;
	}
	// if (arr[n - 1] == 2) {
	// 	printf("0\n");
	// 	return 0;
	// }
	int a, b;
	for (int a = 1; a <= cnt; a++) {
		b = cnt / a;
		if (check(a, b)) {
			ans.push_back(Point(a, b));
		}
	}
	int siz = ans.size();
	printf("%d\n", siz);
	for (int i = 0; i < siz; i++) {
		printf("%d %d\n", ans[i].a, ans[i].b);
	}
	return 0;
}
