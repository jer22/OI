#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

struct Node {
	int cnt;
	Node *child[26];
} *root;

void insert(string s) {
	Node *node = root;
	for (int i = 0; i < s.size(); i++) {
		int id = s[i] - 'a';
		if (node -> child[id] == NULL) {
			node -> child[id] = (Node *)calloc(1, sizeof(Node));
			node = node -> child[id];
			node -> cnt = 1;
		} else {
			node = node -> child[id];
			node -> cnt++;
		}
	}
}

void find(string s) {
	Node *node = root;
	for (int i = 0; i < s.size(); i++) {
		int id = s[i] - 'a';
		if (node -> child[id] == NULL) {
			printf("0\n");
			return;
		} else {
			node = node -> child[id];
		}
	}
	printf("%d\n", node -> cnt);
}

int main() {
	freopen("1251.in", "r", stdin);
	string s;
	root = (Node *)calloc(1, sizeof(Node));
	while (getline(cin, s)) {
		if (!s.size()) break;
		insert(s);
	}
	while (getline(cin, s)) {
		find(s);
	}

	return 0;
}
