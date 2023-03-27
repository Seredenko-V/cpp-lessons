#include <iostream>
#include <vector>
#include <cassert>

using namespace std;


// Поиск ПОДпоследовательности, начинающейся с минимального элемента принимаемой послед-ти
// Длина подпослед-тей не сравнивается. Находится подпослед. с первого минимального элемента
// т.е. { 9,2,35,2,6,7,2 } -> { 2,35 }
vector<int> FindIncreaseSequenceWithMinimumStart(const vector<int>& seq) {
    vector<int> increase;
    increase.reserve(seq.size());
    increase.push_back(seq.front());
    bool is_new_seq = false;
    for (int i = 1; i < seq.size(); ++i) {
        if (seq[i] <= seq[i - 1]) {
            is_new_seq = true;
            if (increase.front() > seq[i]) {
                increase.clear();
                is_new_seq = false;
            }
        }
        if (!is_new_seq) {
            increase.push_back(seq[i]);
        }
    }
    return increase;
}

void Test() {
    vector<int> sequence{ 3,10,60, 5,10,60 };
    vector<int> result = FindIncreaseSequenceWithMinimumStart(sequence);
    vector<int> etalon{ 3,10,60 };
    assert(result == etalon);

    sequence = { 3,10,60, 1,10,60 };
    result = FindIncreaseSequenceWithMinimumStart(sequence);
    etalon = { 1,10,60 };
    assert(result == etalon);

    sequence = { 3,10,60, 5,10,60, 1,10,60};
    result = FindIncreaseSequenceWithMinimumStart(sequence);
    etalon = { 1,10,60 };
    assert(result == etalon);

    sequence = { 1,1,1,1,1 };
    result = FindIncreaseSequenceWithMinimumStart(sequence);
    etalon = { 1 };
    assert(result == etalon);

    sequence = { 9,2,35,2,6,7,2 };
    result = FindIncreaseSequenceWithMinimumStart(sequence);
    etalon = { 2,35 };
    assert(result == etalon);

    //for (int v : result) {
    //    cout << v << ' ';
    //}
    cout << "Tests is ok"s << endl;
}


int main() {
    Test();

	return 0;
}