#include <iostream>
#include <iomanip>

using namespace std;

struct gt_time {

    static const unsigned short PM = 12;

    unsigned short h;
    unsigned short m;
    unsigned short s;

    string t;
};

ostream &operator<<(ostream &out, gt_time &tm) {
    out << setfill('0') <<
        setw(2) << tm.h << ':' <<
        setw(2) << tm.m << ':' << 
        setw(2) << tm.s << '\n';
    return out;
}

istream &operator>>(istream &in, gt_time &tm) {
    char c;
    in >> tm.h >> c >> tm.m >> c >> tm.s >> tm.t;
    if (tm.h == gt_time::PM && (tm.t == "AM" || tm.t == "am"))
        tm.h = 0;
    else if (tm.h < gt_time::PM && (tm.t == "PM" || tm.t == "pm"))
        tm.h += gt_time::PM;
    return in;
}


int main() {

    gt_time a;
    cin >> a;

    cout << a << '\n';

    return 0;
}