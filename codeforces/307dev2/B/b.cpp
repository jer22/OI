/**
*　　　　　　　　┏┓　　　┏┓+ +
*　　　　　　　┏┛┻━━━┛┻┓ + +
*　　　　　　　┃　　　　　　　┃ 　
*　　　　　　　┃　　　━　　　┃ ++ + + +
*　　　　　　 ████━████ ┃+
*　　　　　　　┃　　　　　　　┃ +
*　　　　　　　┃　　　┻　　　┃
*　　　　　　　┃　　　　　　　┃ + +
*　　　　　　　┗━┓　　　┏━┛
*　　　　　　　　　┃　　　┃　　　　　　　　　　　
*　　　　　　　　　┃　　　┃ + + + +
*　　　　　　　　　┃　　　┃　　　　Code is far away from bug with the animal protecting　　　　　　　
*　　　　　　　　　┃　　　┃ + 　　　　神兽保佑,代码无bug　　
*　　　　　　　　　┃　　　┃
*　　　　　　　　　┃　　　┃　　+　　　　　　　　　
*　　　　　　　　　┃　 　　┗━━━┓ + +
*　　　　　　　　　┃ 　　　　　　　┣┓
*　　　　　　　　　┃ 　　　　　　　┏┛
*　　　　　　　　　┗┓┓┏━┳┓┏┛ + + + +
*　　　　　　　　　　┃┫┫　┃┫┫
*　　　　　　　　　　┗┻┛　┗┻┛+ + + +
*/
#include <bits/stdc++.h>

using namespace std;

char a[100005], b[100005], c[100005];
int cnta[30];
int cntb[30];
int cntc[30];
int temp[30];
int main() {
	// freopen("b.in", "r", stdin);
	cin >> a >> b >> c;
	int lena = strlen(a);
	int lenb = strlen(b);
	int lenc = strlen(c);
	for (int i = 0; i < lena; i++) {
		char c = a[i];
		cnta[c - 'a']++;
		temp[c - 'a']++;
	}
	for (int i = 0; i < lenb; i++) {
		cntb[b[i] - 'a']++;
	}
	for (int i = 0; i < lenc; i++) {
		cntc[c[i] - 'a']++;
	}
	int mx = 0;
	int mxi = 0, mxj = 0;
	for (int i = 0; i < lena; i++) {
		// cout << i << endl;
		int cc = 0x3f3f3f3f;
		for (int j = 0; j < 26; j++) {
			if (!cntc[j]) continue;
			// cout << cntc[j] << endl;
			int t = cnta[j] / cntc[j];
			cc = min(cc, t);
		}
		if (i + cc > mx) {
			mxi = i;
			mxj = cc;
			mx = i + cc;
		}
		bool flag = false;
		for (int k = 0; k < 26; k++) {
			cnta[k] -= cntb[k];
			// cout << cnta[i] << " \n"[k == 25];
			if (cnta[k] < 0) {
				flag = true;
				break;
			}
		}
		if (flag) break;
	}
	for (int i = 0; i < mxi; i++) {
		printf("%s", b);
	}
	for (int i = 0; i < mxj; i++) {
		printf("%s", c);
	}
	for (int i = 0; i < 26; i++) {
		for (int j = 0; j < temp[i] - mxi * cntb[i] - mxj * cntc[i]; j++)
			printf("%c", 'a' + i);
	}
	cout << endl;
	return 0;
}
