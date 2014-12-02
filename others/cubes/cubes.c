#include <stdio.h>

int parent[30002];
int child[30002];

int find_parent(int n) {
	while(n != parent[n])
		n = parent[n];
	return n;
}

int find_child(int n) {
	while(n != child[n])
		n = child[n];
	return n;
}

void un(int p, int q) {
	int i = find_parent(p);
	int j = find_child(q);
	parent[i] = j;
	child[j] = i;
}

int main( void ) {
	FILE* in = fopen("cubes.in", "r");
	FILE* out = fopen("cubes.out", "w");
	int i, j;
	for (i = 0; i < 30000; i++) {
		parent[i] = i;
		child[i] = i;
	}
	int p;
	fscanf(in, "%d\n", &p);
	char temp;
	int a, b;
	for (i = 0; i < p; i++) {
		fscanf(in, "%c", &temp);
		if (temp == 'M') {
			fscanf(in, "%d %d\n", &a, &b);
			un(a, b);
		} else {
			fscanf(in, "%d\n", &a);
			int count = 0;
			while (a != parent[a]) {
				count++;
				a = parent[a];
			}
			fprintf(out, "%d\n", count);
		}
	}
	fclose(in);
	fclose(out);
	return 0;
}
