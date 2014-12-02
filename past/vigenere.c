#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char vigenere(char c, char key) {
	char k = key;
	char c1 = c;
	if (key >= 'a') k = key - 32;
	if (c1 >= 'a') c1 = c - 32;
	
	if (c1 >= k) return c1 -(k - 'A');
	else return 'Z' - k + 1 + c1;
	
}

int main ( void ) {
	char m[1005];
	char key[105];
	char c[1005];
	
	scanf("%s%s", &key, &c);
	int i;
	int j = 0;
	for (i = 0; i < strlen(c); i++, j++) {
		m[i] = vigenere(c[i], key[j % strlen(key)]);
		if (c[i] >= 97) m[i] += 32;
	}
	m[i] = '\0';
	printf("%s\n", key);
	printf("%s\n", c);

	printf("%s\n", m);
	system("pause");
	return 0;
}
