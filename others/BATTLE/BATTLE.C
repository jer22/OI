#include <stdio.h>

int arr[1005][1005];
int main ( void ) {
	FILE* in = fopen("BATTLE.IN", "r");
	FILE* out = fopen("BATTLE.OUT", "w");
	int r, c;
	fscanf(in, "%d %d", &r, &c);
	fgetc(in);
	int i, j;
	for (i = 0; i <= c; i++) {
		arr[0][i] = '.';
		arr[r + 1][i] = '.';
	}
	for (i = 0; i <= r; i++) {
		arr[i][0] = '.';
		arr[i][c + 1] = '.';
	}
	for (i = 1; i <= r; i++) {
		for (j = 1; j <= c; j++) {
			fscanf(in, "%c", &arr[i][j]);
		}
		fgetc(in);
	}
	
	for (i = 2; i <= r; i++) {
		for (j = 2; j <= c; j++) {
			if (arr[i][j] == '.') {
				if (arr[i - 1][j] == '#'
					&& arr[i][j - 1] == '#'
					&& arr[i - 1][j - 1] == '#' || 
					arr[i][j - 1] == '#' && arr[i + 1][j - 1] == '#' && arr[i + 1][j] == '#' ||
					arr[i][j + 1] == '#' && arr[i - 1][j] == '#' && arr[i - 1][j + 1] == '#' ||
					arr[i][j + 1] == '#' && arr[i + 1][j] == '#' && arr[i + 1][j + 1] == '#') {
					fprintf(out, "Bad placement.");
					return(0);
				}
			}
		}
	}
	int count = 0;
	for (i = 1; i <= r; i++) {
		for (j = 1; j <= c; j++) {
			if (arr[i][j] == '#') {
				if (arr[i - 1][j] == '.'
					&& arr[i][j - 1] == '.'
					&& arr[i - 1][j - 1] == '.') {
					count++;
				}
			}
		}
	}
	fprintf(out, "There are %d ships.", count);
	fclose(in);
	fclose(out);
	return 0;
}
