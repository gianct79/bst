#include <iostream>
#include <vector>

using namespace std;

struct date {
    short d;
    short m;
    short y;

    static short fine(date const &d1, date const &d2) {
        if (d1.y > d2.y)
            return 10000;
        if (d1.m > d2.m && d1.y == d2.y)
            return 500 * (d1.m - d2.m);
        if (d1.d > d2.d && d1.m == d2.m)
            return 15 * (d1.d - d2.d);
        return 0;
    }
};


int main() {

    date d1;
    cin >> d1.d >> d1.m >> d1.y;
    date d2;
    cin >> d2.d >> d2.m >> d2.y;

    cout << date::fine(d1, d2) << '\n';

    return 0;
}