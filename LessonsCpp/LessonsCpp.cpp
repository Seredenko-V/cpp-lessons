#include <chrono>
#include <iostream>
#include <cassert>
#include <vector>
#include <numeric>

using namespace std;

class LogDuration {
public:
    using Clock = std::chrono::steady_clock;

    LogDuration(const std::string name_block, std::ostream& output = std::cerr)
        : name_block_(name_block) {
    }

    ~LogDuration() {
        using namespace std::chrono;
        using namespace std::literals;

        const auto end_time = Clock::now();
        const auto dur = end_time - start_time_;
        std::cerr << name_block_ << ": "s << duration_cast<milliseconds>(dur).count() << " ms"s << std::endl;
    }

private:
    const Clock::time_point start_time_ = Clock::now();
    const std::string name_block_;
};

double AverageCopy(vector<double> elements) {
    double result = 0.0;
    for (const double& value : elements) {
        result += value;
    }
    return result /= elements.size();
}

double AverageRef(const vector<double>& elements) {
    double result = 0.0;
    for (const double& value : elements) {
        result += value;
    }
    return result /= elements.size();
}

int main() {
    const size_t size = 10000000;
    vector<double> test(size);
    iota(test.begin(), test.end(), 1);
    {
        LogDuration timer("Copy");
        cout << AverageCopy(test) << endl;
    }
    {
        LogDuration timer("NO copy");
        cout << AverageRef(test) << endl;
    }

    return 0;
}