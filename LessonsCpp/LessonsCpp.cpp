// Нужно собрать рюкзак максимально возможной стоимости с учетом грузоподъемности

#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Object {
    string name;
    int cost = 0;
    int weight = 0;
};

struct Backpack {
    vector<Object> objects;
    int cost = 0;
    int weight = 0;
};

Backpack PackBackpack(int max_weight, const vector<Object>& objects) {
    // + 1 чтобы заполнить первую строку и первый столбец нулями для поиска максимума
    vector<vector<int>> table(objects.size() + 1, vector<int>(max_weight + 1));
    for (size_t i = 1; i <= objects.size(); ++i) {
        for (size_t j = 1; j <= max_weight; ++j) {
            // первый объект просто кладем в рюкзак, если помещается
            if (i == 1) {
                if (objects[i - 1].weight <= j) {
                    table[i][j] = objects[i - 1].cost;
                }
            } else {
                // максимальная стоимость рюкзака для текущей грузоподъемности на предыдущем шаге
                int old_max_cost = table[i - 1][j];
                if (objects[i - 1].weight <= j) {
                    // максимальная стоимость рюкзака для текущей грузоподъемности на текущем шаге
                    int new_max_cost = objects[i - 1].cost + table[i - 1][j - objects[i - 1].weight];
                    table[i][j] = max(old_max_cost, new_max_cost);
                } else {
                    table[i][j] = old_max_cost;
                }
            }
            cout << table[i][j] << ' ';
        }
        cout << endl;
    }

    return {};
}

int main() {
    int max_weight = 4; // макс. вес, который может выдержать рюкзак
    vector<Object> all_objects{
        {"laptop"s, 2000, 3},
        {"chainsaw"s, 3000, 4}, 
        {"guitar"s, 1500, 1}
        
    };

    PackBackpack(max_weight, all_objects);

    return 0;
}