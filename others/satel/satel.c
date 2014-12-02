#include <stdio.h>

int arr[80][80];
int cow = 0;
int house = 0;

void research(int i, int j) {
	arr[i][j] = -1;
	if (arr[i - 1][j] == 1)
		research(i - 1, j);
	if (arr[i + 1][j] == 1)
		research(i + 1, j);
	if (arr[i][j + 1] == 1)
		research(i, j + 1);
	if (arr[i][j - 1] == 1)
		research(i, j - 1);
}

int main( void ) {
	FILE* in = fopen("satel.in", "r");
	FILE* out = fopen("satel.out", "w");
	int r, c;
	fscanf(in, "%d %d\n", &r, &c);
	int i, j, k, l;
	char temp;
	for (i = 1; i <= r; i++) {
		for (j = 1; j <= c; j++) {
			fscanf(in, "%c", &temp);
			if (temp == '#') {
				arr[i][j] = 1;
			}
		}
		fgetc(in);
	}

	for (i = 1; i <= r; i++) {
		for (j = 1; j <= c; j++) {
			if (!arr[i][j]) {
				if (arr[i][j + 1] == 1 && arr[i + 1][j] == 1 && arr[i + 1][j + 1] == 1) {
					cow++;
					research(i + 1, j + 1);
				}
				if (arr[i][j - 1] == 1 && arr[i + 1][j] == 1 && arr[i + 1][j - 1] == 1) {
					cow++;
					research(i + 1, j - 1);
				}
				if (arr[i - 1][j] == 1 && arr[i][j - 1] == 1 && arr[i - 1][j - 1] == 1) {
					cow++;
					research(i - 1, j - 1);
				}
				if (arr[i - 1][j] == 1 && arr[i][j + 1] == 1 && arr[i - 1][j + 1] == 1) {
					cow++;
					research(i - 1, j + 1);
				}
			}
			/*for (k = 1; k <= i; k++) {
				for (l = 1; l <= j; l++) {
					if (arr[k][l] == 1) {
						if (arr[k - 1][l] == -1 || arr[k + 1][l] == -1
							|| arr[k][l + 1] == -1 || arr[k][l - 1] == -1) {
							arr[k][l] = -1;
							if (arr[k - 1][l])
								arr[k - 1][l] = -1;
							if (arr[k][l - 1])
								arr[k][l - 1] = -1;
							if (arr[k + 1][l])
								arr[k + 1][l] = -1;
							if (arr[k][l + 1])
								arr[k][l + 1] = -1;
						}
					}
				}
			}*/
		}
	}

	for (i = 1; i <= r; i++) {
		for (j = 1; j <= c; j++) {
			if (arr[i][j] == 1) {
				if (!arr[i - 1][j] && !arr[i][j - 1]) {
					house++;
				}
			}
		}
	}

	/*for (i = 1; i <= r; i++) {
		for (j = 1; j <= c; j++) {
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}
	system("pause");*/
	fprintf(out, "%d\n%d\n", house, cow);
	fclose(in);
	fclose(out);
	return 0;
}
