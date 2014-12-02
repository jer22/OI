#include<stdio.h>
#include<string.h>

int mod(char a[],int m) {
	int i,j;
	int a1[1000];
	int l=strlen(a);
	memset(a1,0,sizeof(a1));
	for(i=0;i<l;i++)
		a1[i]=a[i]-'0';
	for(i=0;i<l;i++) {
		a1[i+1]+=a1[i]%m*10;
	}
	return a1[l]/10;
}

int main(void) {
	int n,m,j,i;
	char a[1000],c[1000];
	scanf("%s%d",a,&n);
	m=mod(a,n);
	printf("%d",m);
	return 0;
}
