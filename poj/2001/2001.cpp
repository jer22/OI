#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>

#define SIGMA_SIZE 26
#define MAX_NODE 25000

using namespace std;

struct Node{
	int num;
	Node *child[26];
};

Node *root = (Node *)calloc(1, sizeof(Node));;
char str[1010][30];
int n = 1;

void insert(char *s) {
	Node *node = root;
	for (int i = 0; i < strlen(s); i++) {
		int id = s[i] - 'a';
		if (node -> child[id] == NULL) {
			Node *q = (Node *)calloc(1, sizeof(Node));
			node -> child[id] = q;
			node = q;
			node -> num = 1;
		} else {
			node = node -> child[id];
			node -> num++;
		}
	}
}

void find(char *s) {
	Node *node = root;
	printf("%s ", s);
	for (int i = 0; i < strlen(s); i++) {
		printf("%c", s[i]);
		int id = s[i] - 'a';
		if (node -> child[id] -> num == 1) {
			break;
		}
		node = node -> child[id];
	}
	printf("\n");
}

int main() {
	freopen("2001.in", "r", stdin);
	while (scanf("%s", str[n]) != EOF) {
		insert(str[n++]);
	}
	n -= 1;
	for (int i = 1; i <= n; i++) {
		find(str[i]);
	}

	return 0;
}
