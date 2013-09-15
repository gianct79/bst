
#include <iostream>
#include <cstdint>

#include <fstream>
#include <sstream>

#include <vector>
#include <algorithm>

using namespace std;

class job {
    int w_;
    int l_;

public:
    job(const int &w, const int &l) : w_(w), l_(l) {
    }

    int weight() const { return w_; }
    int length() const { return l_; }

    int diff() const { return w_ - l_; }
    float ratio() const { return w_ / float(l_); }
};

class job_scheduler {

    typedef vector<job> job_list;
    job_list jobs_;

    int64_t weighted_sum(const job_list &jobs) const {

        int64_t sum(0), c(0);

        for (auto &j : jobs) {
            c += j.length();
            sum += j.weight() * c;
        }
        return sum;
    }

public:
    job_list &jobs() {
        return jobs_;
    }

    int64_t weighted_sum_diff() const {

        job_list copy(jobs_);

        stable_sort(copy.begin(), copy.end(), [](const job &a, const job &b) {
            if (a.diff() == b.diff())
                return a.weight() > b.weight();
            else
                return a.diff() > b.diff();
        });

        return weighted_sum(copy);
    }

    int64_t weighted_sum_ratio() const {

        job_list copy(jobs_);

        stable_sort(copy.begin(), copy.end(), [](const job &a, const job &b) {
            return a.ratio() > b.ratio();
        });

        return weighted_sum(copy);
    }

    friend istream& operator>>(istream& is, job_scheduler& list) {

        string line;
        getline(is, line);

        while (getline(is, line)) {

            stringstream linestream(line);

            if (linestream) {
                int w, l;
                linestream >> w >> l;

                list.jobs().push_back(job(w, l));
            }
        }

        return is;
    }
};

int main(int argc, char* argv[]) {

    job_scheduler scheduler;

    if (argc > 1) {
        ifstream ifs(argv[1], istream::in); ifs >> scheduler;
    }

    cout << "job count: " << scheduler.jobs().size() << '\n';
    cout << "sum diff : " << scheduler.weighted_sum_diff() << '\n';
    cout << "sum ratio: " << scheduler.weighted_sum_ratio() << '\n';

    cin.get();

    return 0;
}
