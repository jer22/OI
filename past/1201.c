#include <stdio.h>
#include <string.h>

int main( void ) {
	int n;
	char name[12][15];
	char temp[15], tempN[15];
	int cost[12];
	int get[12];
	memset(cost, 0, sizeof(cost));
	memset(get, 0, sizeof(get));
	int i, j, k, l;
	int now, np;

	scanf("%d", &n);
	for (i = 0; i < n; i++)
		scanf("%s", name[i]);
	for (i = 0; i < n; i++) {
		scanf("%s", &temp);
		for (j = 0; j < n; j++)
			if (strcmp(temp, name[j]) == 0)
				break;
		scanf("%d %d", &now, &np);
		for (k = 0; k < np; k++) {
			scanf("%s", &tempN);
			for (l = 0; l < n; l++)
				if (strcmp(tempN, name[l]) == 0)
					break;
			get[l] += now / np;
		}
		if (np != 0)
			cost[j] += now / np * np;
	}
	for (i = 0; i < n; i++) {
		printf("%s %d\n",name[i], get[i] - cost[i]);
	}

	system("pause");
	return 0;
}
