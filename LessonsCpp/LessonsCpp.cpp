#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <iterator>

using namespace std;

template <typename It>
void PrintRange(It range_begin, It range_end) {
    for (auto it = range_begin; it != range_end; ++it) {
        cout << *it << " "s;
    }
    cout << endl;
}

template <typename It>
set<typename iterator_traits<It>::value_type> MakeSet(It range_begin, It range_end) {
    return set<typename iterator_traits<It>::value_type>(range_begin, range_end);
}

//template <typename It>
//auto MakeSet(It range_begin, It range_end) {
//    return set(range_begin, range_end);
//}

int main() {
    vector<string> langs = { "Python"s, "Java"s, "C#"s, "Ruby"s, "C++"s, "C++"s, "C++"s, "Ruby"s, "Java"s };
    set<string> unique_langs = MakeSet(langs.begin(), langs.end());
    PrintRange(unique_langs.begin(), unique_langs.end());
}