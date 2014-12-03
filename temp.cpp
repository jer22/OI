#include <cstdio>
#include <cstring>
#include <algorithm>
#include <stack>
#include <cmath>
#include <string>
#include <iostream>

using namespace std;

struct Node{
	int left, right;
};

int n, T;
Node arr[200];

void pre(int i) {
	if (!i) return;
	printf("%d ", i);
	pre(arr[i].left);
	pre(arr[i].right);
}

void in(int i) {
	if (!i) return;
	in(arr[i].left);
	printf("%d ", i);
	in(arr[i].right);
}

void post(int i) {
	if (!i) return;
	post(arr[i].left);
	post(arr[i].right);
	printf("%d ", i);
}

int main() {
	freopen("temp.in", "r", stdin);
	cin >> n;
	int a, b;
	for (int i = 1; i <= n; i++) {
		scanf("%d %d", &a, &b);
		arr[i].left = a;
		arr[i].right = b;
	}
	pre(1);
	cout << endl;
	in(1);
	cout << endl;
	post(1);
	return 0;
}
