#include <stdio.h>
#include <string.h>

int n, q;

int arr[1002][1002][3];

int main( void ) {
	FILE* in = fopen("faq.in", "r");
	FILE* out = fopen("faq.out", "w");
	fscanf(in, "%d %d\n", &n, &q);
	int i, j, k;
	char temp;
	int a, b;
	int x, y, z;
	char t;
	for (k = 0; k < q; k++) {
		fscanf(in, "%c %d %d", &temp, &a, &b);
		if (temp == 'Q') {
			fscanf(in, "\n");
			if (!arr[a][b][0] && !arr[a][b][1] && !arr[a][b][2]) {
				fprintf(out, "Not Sure\n");
			} else {
				if (arr[a][b][0] < 0)
					fprintf(out, "D %d ", -arr[a][b][0]);
				else
					fprintf(out, "U %d ", arr[a][b][0]);
				if (arr[a][b][1] < 0)
					fprintf(out, "R %d ", -arr[a][b][1]);
				else
					fprintf(out, "L %d ", arr[a][b][1]);
				if (arr[a][b][2] < 0)
					fprintf(out, "B %d\n", -arr[a][b][2]);
				else
					fprintf(out, "F %d\n", arr[a][b][2]);
			}
		} else if (temp == 'C') {
			fscanf(in, " ");
			fscanf(in, "%c %d ", &t, &z);
			if (t == 'D')
				z = -z;
			fscanf(in, "%c %d ", &t, &x);
			if (t == 'R')
				x = -x;
			fscanf(in, "%c %d\n", &t, &y);
			if (t == 'B')
				y = -y;
			arr[a][b][0] = z;
			arr[a][b][1] = x;
			arr[a][b][2] = y;
			arr[b][a][0] = -z;
			arr[b][a][1] = -x;
			arr[b][a][2] = -y;
			for (i = 1; i <= n; i++) {
				if (arr[b][i][0] || arr[b][i][1] || arr[b][i][2]) {
					arr[a][i][0] = arr[a][b][0] + arr[b][i][0];
					arr[a][i][1] = arr[a][b][1] + arr[b][i][1];
					arr[a][i][2] = arr[a][b][2] + arr[b][i][2];

					arr[i][a][0] = arr[b][a][0] + arr[i][b][0];
					arr[i][a][1] = arr[b][a][1] + arr[i][b][1];
					arr[i][a][2] = arr[b][a][2] + arr[i][b][2];
				}
				
				if (arr[a][i][0] || arr[a][i][1] || arr[a][i][2]) {
					arr[b][i][0] = arr[b][a][0] + arr[a][i][0];
					arr[b][i][1] = arr[b][a][1] + arr[a][i][1];
					arr[b][i][2] = arr[b][a][2] + arr[a][i][2];

					arr[i][b][0] = arr[a][b][0] + arr[i][a][0];
					arr[i][b][1] = arr[a][b][1] + arr[i][a][1];
					arr[i][b][2] = arr[a][b][2] + arr[i][a][2];
				}
			}
		}
	}
	fclose(in);
	fclose(out);
	return 0;
}



