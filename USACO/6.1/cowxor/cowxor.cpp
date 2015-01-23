/*
ID:shijiey1
LANG:C++
PROG:cowxor
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cstdlib>

using namespace std;

struct Node{
	int idx, value;
	int child[2];
}node[700000];

int n, tot = 0;
int root;
int arr[100002];
int bit(int value, int i) {
	return (value & (1 << i)) >> i;
}

int newNode() {
	node[tot].idx = node[tot].value = -1;  
	node[tot].child[0] = node[tot].child[1] = -1;  
	return tot++;      
}

void insert(int idx, int value) {
	int pos = root;
	for (int i = 20; i >= 0; i--) {
		int t = bit(value, i);
		if (node[pos].child[t] == -1)
			node[pos].child[t]= newNode();
		pos = node[pos].child[t];
	}
	node[pos].idx = idx;
	node[pos].value = value;
}

int find(int idx, int value) {
	int pos = root;
	for (int i = 20; i >= 0 && pos != -1; i--) {
		int t = bit(value, i);
		if (node[pos].child[(t + 1) % 2] != -1)
			pos = node[pos].child[(t + 1) % 2];
		else pos = node[pos].child[t];
	}
	return pos;
}

int main() {
	freopen("cowxor.in", "r", stdin);
	freopen("cowxor.out", "w", stdout);
	scanf("%d", &n);
	root = newNode();
	insert(0, 0);
	int t;
	int ans = -1, idx1, idx2;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &t);
		arr[i] = arr[i - 1] ^ t;
		int x = find(i, arr[i]);
		if (x != -1) {
			if ((arr[i] ^ node[x].value) > ans) {
				ans = (arr[i] ^ node[x].value);
				idx1 = node[x].idx + 1;
				idx2 = i;
			}
		}
		insert(i, arr[i]);
	}
	printf("%d %d %d\n", ans, idx1, idx2);
	return 0;
}
