#include <stdio.h>
#include <stdlib.h>

#define dst(x1, y1, x2, y2)    sqrt(((x1)-(x2)) * ((x1)-(x2)) + ((y1)-(y2)) * ((y1)-(y2)))

int hole[100][2];			
int air[100];				
int q_num[100];				
int q_point[100][50][2];	
double distant[100][50][50];
double dp[2][50];

int main( void ) {
	FILE* fin = fopen("heaven.in", "r");
	FILE* fout = fopen("heaven.out", "w");
	int n, m, q;
	double result = 0;
	fscanf(fin, "%d%d%d", &n, &m, &q);
	int i;
	for (i = 0; i < n - 1; i++)
		fscanf(fin, "%d%d", &hole[i][0], &hole[i][1]);
	for (i = 0; i < n - 1; i++)
		fscanf(fin, "%d", &air[i]);
	int a1, a2, a3;
	for (i = 0; i < q; i++) {
		fscanf(fin, "%d%d%d", &a1, &a2, &a3);
		a3--;
		q_point[a3][q_num[i]][0] = a1;
		q_point[a3][q_num[i]++][1] = a2;
	}
	for (i = 0; i < n - 1; i++) {
		for (a1 = 0; a1 < q_num[i]; a1++)
			for (a2 = 0; a2 < q_num[i]; a2++)
				distant[i][a1][a2] = dst(
					q_point[i][a1][0], q_point[i][a1][1],
					q_point[i][a2][0], q_point[i][a2][1]);
	}
	int p = 0;
	int j, k, l;
	double temp;
	for (i = 0; i < n - 1; i++) {
		j = air[i];
		if (j < m) {
			for (k = 0; k < q_num[i]; k++) {
				dp[p][k] = dst(
					hole[i][0], hole[i][1],
					q_point[i][k][0], q_point[i][k][1]);
			}
			j++;
			while(j < m) {
				for (k = 0; k < q_num[i]; k++) {
					dp[!p][k] = 900000;
					for (l = 0; l < q_num[i]; l++) {
						if (k != l)
							if (dp[p][l] + distant[i][k][l] < dp[!p][k])
								dp[!p][k] = dp[p][l] + distant[i][k][l];
					}
					p = !p;
					j++;
				}
			}
			temp = 900000;
			for (j = 0; j < q_num[i]; j++) {
				dp[p][j] = dp[p][j] + dst(
					hole[i + 1][0], hole[i + 1][1],
					q_point[i][j][0], q_point[i][j][1]);
				if (dp[p][j] < temp)
					temp = dp[p][j];
				printf("%lf\n", temp);
				system("pause");
			}
			result += temp;
		} else
		result += dst(hole[i][0], hole[i][1], hole[i + 1][0], hole[i + 1][1]);
	}
	printf("%.2lf", result);


	fclose(fin);
	fclose(fout);
	system("pause");
	return 0;
}
