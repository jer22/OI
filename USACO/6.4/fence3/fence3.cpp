/*
ID:shijiey1
LANG:C++
PROG:fence3
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

struct Line{
	int x1, y1, x2, y2;
}line[155];

int n;

double dist(double x1, double y1, double x2, double y2) {
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

double getDist(double x, double y, int i) {
	if (line[i].x1 == line[i].x2) {
		if (y < line[i].y1) return dist(x, y, (double)line[i].x1, (double)line[i].y1);
		if (y > line[i].y2) return dist(x, y, (double)line[i].x2, (double)line[i].y2);
		return fabs(x - line[i].x1);
	} else {
		if (x < line[i].x1) return dist(x, y, line[i].x1, line[i].y1);
		if (x > line[i].x2) return dist(x, y, line[i].x2, line[i].y2);
		return fabs(y - line[i].y1);
	}
}

int main() {
	freopen("fence3.in", "r", stdin);
	freopen("fence3.out", "w", stdout);
	srand(time(0));
	cin >> n;
	double ansx, ansy;
	double x = rand() % 100;
	double y = rand() % 100;
	double best=0;
	for(int i = 1; i <= n; i++){
		cin >> line[i].x1 >> line[i].y1 >> line[i].x2 >> line[i].y2;
		if(line[i].y1 > line[i].y2) swap(line[i].y1, line[i].y2);
		if(line[i].x1 > line[i].x2) swap(line[i].x1, line[i].x2);
		best += getDist(x, y, i);
	}
	int d = 31;
	double t = 100;
	while (t > 1e-2) {
		for (int i = 1; i <= 500; i++) {
			double nx = t * (double(rand()) / double(RAND_MAX)) * ((rand() % 2) * 2 - 1);
			double ny = sqrt(t * t - nx * nx) * ((rand() % 2) * 2 - 1);
			nx += x;
			ny += y;
			double temp = 0;
			for (int j = 1; j <= n; j++)
				temp += getDist(nx, ny, j);
			double p = temp - best;
			double yy = 0;
			if (p < 0) {
				best = temp;
				ansx = nx, ansy = ny;
				yy = 1;
			} else yy = exp(-p / t);
			double q = double(rand()) / double(RAND_MAX);
			if (q < yy) x = nx, y = ny;
		}
		d++;
		t = t / (log10(d) / log10(20));
	}
	printf("%.1lf %.1lf %.1lf\n", ansx, ansy, best);
	return 0;
}
