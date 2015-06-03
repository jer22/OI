#include <bits/stdc++.h>

using namespace std;
class BinaryCode{
	public : 
	vector<string> decode(string s) {
		vector<string> ans;
		if (s.size() == 1) {
			string a = "0", b = "1";
			if (s[0] == '0') b = "NONE";
			else if (s[0] == '1') a = "NONE";
			else {
				a = "NONE";
				b = "NONE";
			}
			ans.push_back(a);
			ans.push_back(b);
			return ans;
		}
		string a = "0";
		int tot = s[0] - '0';
		a += '0' + tot;
		if (tot && tot != 1) {
			a = "NONE";
		} else {
			for (int i = 1; i < s.size() - 1; i++) {
				tot = s[i] - '0' - (a[i - 1] - '0' + a[i] - '0');
				a += '0' + tot;
				if (tot && tot != 1) {
					a = "NONE";
					break;
				}
			}
			int t = s.size() - 1;
			if (a[t] - '0' + a[t - 1] - '0' != s[t] - '0') {
				a = "NONE";
			}
		}
		string b = "1";
		tot = s[0] - '1';
		b += '0' + tot;
		if (tot && tot != 1) {
			b = "NONE";
		} else {
			for (int i = 1; i < s.size() - 1; i++) {
				tot = s[i] - '0' - (b[i - 1] - '0' + b[i] - '0');
				b += '0' + tot;
				if (tot && tot != 1) {
					b = "NONE";
					break;
				}
			}
			int t = s.size() - 1;
			if (b[t] - '0' + b[t - 1] - '0' != s[t] - '0') {
				b = "NONE";
			}
		}
		// cout << a << endl;
		ans.push_back(a);
		ans.push_back(b);
		return ans;
	}
};

int main() {
	BinaryCode b;
	vector<string> ans = b.decode("123210120");


	return 0;
}
