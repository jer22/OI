#include <stdio.h>
#include <string.h>

int main( void ) {
	int arr[26];
	memset(arr, 0, sizeof(arr));
	char temp[10];
	int i = 0, n = 0;
	char ch;
	scanf("%s", temp);
	int max = 0, t;
	char c[1024];
	while (strcmp(temp, "ENDOFINPUT") != 0) {
		getchar();
		do {
			ch = getchar();
			if (ch >= 'a' && ch <= 'z') ch -= 32;
			c[i++] = ch;
		} while (ch != '\n');
		c[--i] = '\0';
		n = i;
		for (i = 0; i < n; i++) {
			arr[c[i] - 'A']++;
		}

		for (i = 0; i < 26; i++) {
			if (arr[i] > max) {
				max = arr[i];	
				t = i;
			} 
		}
		t -= 4;


		for (i = 0; i < n; i++) {
			if (c[i] >= 65 && c[i] <= 90) {
				c[i] -= t;
				if (c[i] <= 64) c[i] += 26;
				if (c[i] >= 91) c[i] -= 26;
			}
			printf("%c", c[i]);
		}
		printf("\n");


		scanf("%s", temp);
		i = 0; n = 0, max = 0;
		scanf("%s", temp);
	}
	
	

	system("pause");
	return 0;
}
