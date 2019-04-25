#include <iostream>
#include <iomanip>

using namespace std;

int dayOfWeek(int y, int m, int d) {

	static int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
    y -= m < 3;

    return (y + y/4 - y/100 + y/400 + t[m-1] + d) % 7;
}

static int dm[2][13] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int main() {

	int y, m;
	cin >> y;
	cin >> m;

	int dw = dayOfWeek(y, m, 1);

	int lp = (y % 4 == 0);

	if (y % 100 == 0 && y % 400 != 0)
		lp = 0;

	int mx[42] = {0};
	int h = dm[lp][m];
	
	for (int i = 1; i <= h; ++i)
		mx[i + dw] = i;

	for (int i = 1; i < 42; ++i) {
		if (mx[i])
			cout << setw(2) << setfill(' ') << mx[i] << ' ';
		else
			cout << "   ";

		if (i % 7 == 0)
			cout << '\n';
	}

	return 0;
}
