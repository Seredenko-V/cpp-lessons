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

vector<vector<int>> ParseValueCopy(vector<int> elements) {
    vector<vector<int>> result;
    if (elements.empty()) {
        return result;
    }
    vector<int> box;

    for (size_t i = 0; i < elements.size() - 1; ++i) {
        box.push_back(elements[i]);
        if (elements[i + 1] != elements[i]) {
            result.push_back(box);
            box.clear();
        }
    }
    box.push_back(elements.back());
    result.push_back(box);
    return result;
}

vector<vector<int>> ParseValueRef(const vector<int>& elements) {
    vector<vector<int>> result;
    if (elements.empty()) {
        return result;
    }
    vector<int> box;

    for (size_t i = 0; i < elements.size() - 1; ++i) {
        box.push_back(elements[i]);
        if (elements[i + 1] != elements[i]) {
            result.push_back(box);
            box.clear();
        }
    }
    box.push_back(elements.back());
    result.push_back(box);
    return result;
}

int main() {
    const size_t SIZE = 9008000;
    vector<int> elements(SIZE);
    iota(elements.begin(), elements.end(), 1);

    {
        LogDuration dur("COPY");
        ParseValueCopy(elements);
    }
    {
        LogDuration dur("NO COPY");
        ParseValueRef(elements);
    }

    return 0;
}
