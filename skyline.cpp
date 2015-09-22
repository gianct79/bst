/*
 * Copyleft GTO Inc. All rights reversed.
 */

#include <iostream>
#include <vector>
#include <queue>


struct building {
    int xl;
    int xr;
    int h;
};

using building_vector = std::vector<building>;

std::ostream &operator<<(std::ostream &out, building_vector const &input) {
    out << '[';
    for (auto &b : input) {
        out << '(' << b.xl << ',' << b.xr << ',' << b.h << ')';
    }
    out << ']';
    return out;
}

struct point {
    int x;
    int h;

    bool operator>(point const &rhs) const {
        return (x > rhs.x);
    }
};

using skyline = std::priority_queue<point, std::vector<point>, std::greater<point>>;

skyline merge(skyline &sk1, skyline &sk2) {

    skyline sk;

    int curH1 = 0;
    int curH2 = 0;
    int prevH = 0;

    while (!sk1.empty() && !sk2.empty()) {

        int curX;

        point top1 = sk1.top();
        point top2 = sk2.top();

        if (top1.x < top2.x) {

            curX = top1.x;
            curH1 = top1.h;
            sk1.pop();

        } else {

            curX = top2.x;
            curH2 = top2.h;
            sk2.pop();
        }

        int maxH = std::max(curH1, curH2);

        if (maxH != prevH) {
            sk.push({curX, maxH});
            prevH = maxH;
        }
    }

    while (!sk1.empty()) {
        sk.push(sk1.top());
        sk1.pop();
    }

    while (!sk2.empty()) {
        sk.push(sk2.top());
        sk2.pop();
    }

    return sk;
}

int perimeter(skyline sk) {

    if (!sk.size())
        return 0;

    point prev = sk.top();
    sk.pop();

    int p = prev.h;

    while (!sk.empty()) {

        point curr = sk.top();
        sk.pop();

        p += std::abs(curr.x - prev.x);
        p += std::abs(curr.h - prev.h);

        prev = curr;
    }

    return p;
}

skyline create_r(building_vector const &B, unsigned lo, unsigned hi) {

    skyline sk;

    if (lo == hi) {

        // skyline from building
        sk.push({B[lo].xl, B[lo].h});
        sk.push({B[lo].xr, 0});

    } else {

        unsigned mid = (lo + hi) / 2;

        skyline sk1 = create_r(B, lo, mid);
        skyline sk2 = create_r(B, mid + 1, hi);

        sk = merge(sk1, sk2);
    }

    return sk;
}

skyline create(building_vector const &B) {

    skyline sk;

    if (B.size())
        sk = create_r(B, 0, B.size() - 1);

    return sk;
}


int main() {

    building_vector input;

    std::cout << "Enter values x, w, h; one building per line...\n";

    int x, h, w;
    while (std::cin >> x >> w >> h) {
        input.push_back({x, x + w, h});
    }

    std::cout << input << '\n';

    skyline sk = create(input);
    std::cout << perimeter(sk) << '\n';

    return 0;
}
