#include <iostream>
#include <vector>

using namespace std;

struct point {
    float x_;
    float y_;

    point(float x = 0.0f, float y = 0.0f) : x_(x), y_(y) {
    }
};

ostream &operator<<(ostream &out, const point &pt) {
    out << '(' << pt.x_ << ',' << pt.y_ << ')';
    return out;
}

struct bounding_box {
    point center_;
    point hsize_;

    bounding_box(point const &center = {}, point const &hsize = {}) : center_(center), hsize_(hsize) {
    }

    bool contains(point const &pt) const {
        return (pt.x_ < (center_.x_ + hsize_.x_) && pt.x_ > (center_.x_ - hsize_.x_))
            && (pt.y_ < (center_.y_ + hsize_.y_) && pt.y_ > (center_.y_ - hsize_.y_));
    }

    bool intersects(bounding_box const &o) const {
        return ((center_.x_ + hsize_.x_) > (o.center_.x_ - o.hsize_.x_) || (center_.x_ - hsize_.x_) < (o.center_.x_ + o.hsize_.x_))
            && ((center_.y_ + hsize_.y_) > (o.center_.y_ - o.hsize_.y_) || (center_.y_ - hsize_.y_) < (o.center_.y_ + o.hsize_.y_));
    }
};

ostream &operator<<(ostream &out, const bounding_box &bb) {
    out << '('
    << '(' << (bb.center_.x_ - bb.hsize_.x_) << ',' << (bb.center_.y_ - bb.hsize_.y_) << ')'
    << '(' << (bb.center_.x_ + bb.hsize_.x_) << ',' << (bb.center_.y_ + bb.hsize_.y_) << ')'
    << ')';
    return out;
}

istream &operator>>(istream &in, bounding_box &bb) {
    in >> bb.center_.x_ >> bb.center_.y_ >> bb.hsize_.x_ >> bb.hsize_.y_;
    return in;
}

template <typename T>
struct data {
    point pt_;
    T data_;

    data(point const &pt = {}, T const &data = {}) : pt_(pt), data_(data) {
    };
};

template <typename T>
struct quad_tree {

    static constexpr unsigned capacity = 4;

    quad_tree* nw_ {nullptr};
    quad_tree* ne_ {nullptr};
    quad_tree* sw_ {nullptr};
    quad_tree* se_ {nullptr};

    bounding_box bounds_;
    vector<data<T>> data_;

    quad_tree(bounding_box const &bounds = {}) : bounds_(bounds) {
    }

    ~quad_tree() {
        delete nw_; delete ne_; delete sw_; delete se_;
    }

    void split() {
        point qsize {bounds_.hsize_.x_, bounds_.hsize_.y_};
        point qcenter {bounds_.center_.x_ - qsize.x_, bounds_.center_.y_ - qsize.y_};
        nw_ = new quad_tree{{qcenter, qsize}};
        qcenter = {bounds_.center_.x_ + qsize.x_, bounds_.center_.y_ - qsize.y_};
        ne_ = new quad_tree{{qcenter, qsize}};
        qcenter = {bounds_.center_.x_ - qsize.x_, bounds_.center_.y_ + qsize.y_};
        sw_ = new quad_tree{{qcenter, qsize}};
        qcenter = {bounds_.center_.x_ + qsize.x_, bounds_.center_.y_ + qsize.y_};
        se_ = new quad_tree {{qcenter, qsize}};
    }

    bool insert(data<T> const &d) {
        if (!bounds_.contains(d.pt_)) {
            return false;
        }
        if (data_.size() < capacity) {
            data_.push_back(d);
            return true;
        }
        if (!nw_) {
            split();
        }
        if (nw_->insert(d)) {
            return true;
        }
        if (ne_->insert(d)) {
            return true;
        }
        if (sw_->insert(d)) {
            return true;
        }
        if (se_->insert(d)) {
            return true;
        }
        return false; // hu?
    }

    vector<data<T>> query(bounding_box const &range) const {
        if (!bounds_.intersects(range)) {
            return {};
        }
        vector<data<T>> in;
        for (auto& o: data_) {
            if (range.contains(o.pt_)) {
                in.push_back(o);
            }
        }
        if (!nw_) {
            return in;
        }
        vector<data<T>> temp = nw_->query(range);
        in.insert(in.end(), temp.begin(), temp.end());
        temp = ne_->query(range);
        in.insert(in.end(), temp.begin(), temp.end());
        temp = sw_->query(range);
        in.insert(in.end(), temp.begin(), temp.end());
        temp = se_->query(range);
        in.insert(in.end(), temp.begin(), temp.end());
        return in;
    }
};

template <typename T>
ostream &operator<<(ostream &out, const quad_tree<T> &qt) {
    out << qt.bounds_ << '\n';
    for (auto &i : qt.data_) {
        cout << i.pt_ << ": " << i.data_ << '\n';
    }
    return out;
}

int main() {

    vector<data<string>> data {
        {{-2.f,-2.f}, "Rua do Menonc"},
        {{-1.f,-1.f}, "Rua do Viccari"},
        {{0.f,0.f}, "Rua do Xcao"},
        {{1.f,1.f}, "Rua do Bruño"},
        {{2.f,2.f}, "Rua do Gião"}
    };

    bounding_box world {{0.f,0.f}, {2.5f,2.5f}};
    quad_tree<string> qt {world};
    for (auto &d : data) {
        qt.insert(d);
    }
    cout << qt << '\n';

    cout << "Type bounding boxes (center x y, size x y) queries\n";
    bounding_box bb;
    while (cin >> bb) {
        auto q = qt.query(bb);
        cout << bb << ':' << q.size() << '\n';
        for (auto &i : q) {
            cout << i.pt_ << ": " << i.data_ << '\n';
        }
    }

    return 0;
}
