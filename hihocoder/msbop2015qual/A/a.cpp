#include <iostream>

using namespace std;

int T;
string jan = "January", feb = "February";

bool check(int y) {
	return !(y % 400) || ((y % 100) && !(y % 4));
}

int getans(int s, int e) {
	int ans = 0;
	for(int i = s; i < e; i++)
		ans += check(i);
	return ans;
}

int main() {
	cin >> T;
	string smonth, emonth;
	char c;
	int sday, syear, eday, eyear;
	for (int cas = 1; cas <= T; cas++) {
		cin >> smonth >> sday >> c >> syear;
		cin >> emonth >> eday >> c >> eyear;
		if (smonth != jan && smonth != feb) syear++;
		if (emonth == jan || (emonth == feb && eday != 29)) eyear--;
		cout << "Case #" << cas << ": " << getans(syear, eyear + 1) << endl;
	}
	return 0;
}
