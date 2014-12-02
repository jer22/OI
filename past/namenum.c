#include <stdio.h>
#include <string.h>

char map[10][3] = {{},{}, {'A','B','C'}, {'D','E','F'}, {'G','H','I'}
, {'J','K','L'}, {'M','N','O'}, {'P','R','S'}, {'T','U','V'}, {'W','X','Y'}};

int contents(char k, char v) {
	int i;
	for (i = 0; i < 3; i++) {
		if (map[k - '0'][i] == v)
			return 1;
	}
	return 0;
}

int main( void ) {
	FILE * dic = fopen("dict.txt", "r");
	FILE * in = fopen("namenum.in", "r");
	FILE * out = fopen("namenum.out", "w");
	char dict[5000][15];
	char arr[15];

	int i = 0;
	int j = 0;
	int n = 0;
	int has = 0;
	do {
		fscanf(dic, "%s", dict[i++]);
		n++;
	} while (fgetc(dic) != EOF);
	n--;
	fscanf(in, "%s", arr);
	int l = strlen(arr);
	for (i = 0; i < n; i++) {
		for (j = 0; j < l; j++) {
			if (!contents(arr[j], dict[i][j])) {
				break;
			}
		}
		if (j == l && strlen(dict[i]) == l) {
			fprintf(out, "%s\n", dict[i]);
			has = 1;
		}
	}
	if (!has) {
		fprintf(out, "NONE");
	}
	
	fclose(dic);
	fclose(in);
	fclose(out);
	return 0;
}
