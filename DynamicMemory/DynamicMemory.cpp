/*******************************************************************************
    std::vector
*******************************************************************************/

#include <iostream> 
#include <cassert>
#include <vector>

using namespace std;

vector<int> SumVector(vector<int> a, vector<int> b) {
    vector<int> result(a.size());
    for (size_t i = 0; i < a.size(); ++i) {
        result[i] = a[i] + b[i];
    }
    return result;
}

int main() {
    setlocale(LC_ALL, "ru");
    
    vector<int> first(5, 5);
    vector<int> second(5, 3);
    vector<int> result = SumVector(first, second);

    for (size_t i = 0; i < result.size(); ++i) {
        cout << result[i] << ' ';
    }
    cout << endl;

    return 0;
}