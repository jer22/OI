#include <stdio.h>
#include <string.h>

char id[18];
int arr[17] = {7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9, 10, 5, 8, 4, 2};
int main( void ) {
	FILE * fin = fopen("id.in", "r");
	FILE * fout = fopen("id.out", "w");
	int re = 0;
	char c;
	fscanf(fin, "%s", &id);
	if ((id[16] - '0') % 2)
		fprintf(fout, "Male\n");
	else
		fprintf(fout, "Female\n");
	int i, j;
	for (i = 6; i <= 9; i++)
		fprintf(fout, "%c", id[i]);
	fprintf(fout, "-");
	for (j = 0; j < 2; j++) {
		if (id[i++] - '0')
			fprintf(fout, "%c", id[i - 1]);
		fprintf(fout, "%c", id[i++]);
		if (!j)
			fprintf(fout, "-");
		else
			fprintf(fout, "\n");
	}
	for (i = 0; i < 17; i++) {
		arr[i] *= id[i] - '0';
		re += arr[i];
	}
	re %= 11;
	if (!re)
		c = '1';
	else if (re == 1)
		c = '0';
	else if (re == 2)
		c = 'X';
	else 
		c = (12 - re) + '0';
	id[17] = c;
	fprintf(fout, "%s", id);
	fclose(fin);
	fclose(fout);
	return 0;
}
