#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

string s;
int Next[400005];
int lens;
int tot = 0;
int ans[400005];
void getNext() {
	Next[0] = -1;  
    int i = 0, j = -1;  
    while (i < lens)  
    {  
        if (j == -1 || s[i] == s[j])  
        {  
            ++i;  
            ++j;  
            Next[i] = j;  
        }  
        else j = Next[j];  
    }  
}

int main() {
	freopen("2752.in", "r", stdin);
	while (cin >> s) {
		lens = s.size();
		getNext();
		int i = lens - 1;
		tot = 0;
		memset(ans, 0, sizeof(ans));
		while (i != -1) {
			if (s[i] == s[lens - 1])
				ans[tot++] = i + 1;
			i = Next[i];
		}
		for (int i = tot - 1; i >= 0; i--) {
			cout << ans[i] << " \n"[i == 0];
		}
	}

	return 0;
}
