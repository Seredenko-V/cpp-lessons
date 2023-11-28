#include <iostream>
#include <string>
#include <sstream>
#include <cassert>
#include <ctime>

using namespace std;

/// ЛР04. Хеширование данных. Вариант 11.
/// Формат ключа: БццццБ
/// Количество сегментов: 3000
/// Метод хеширования: Квадратичное опробование

enum class HashMethod {
    QUADRATIC, // квадратичное опробирование
    LINEAR,    // линейное опробирование
    OPEN,      // открытое хеширование
    DOUBLE     // двойное хеширование
};

/// Генерирование случайного числа в диапазоне [min_value; max_value]. По умолчанию [0; 9]
int GetRandomNumber(int min_value = 0, int max_value = 9) {
    srand(time(NULL));
    return min_value + rand() % (max_value - min_value + 1);
}

/// Генерирование случайного числа в диапазоне [min_symbol; max_symbol]. По умолчанию [A; Z]
char GetRandomSymbol(char min_symbol = 'A', char max_symbol = 'Z') {
    srand(time(NULL));
    return min_symbol + rand() % (min_symbol - max_symbol + 1);
}

int* GetRandomKey(const bool key_structure[], int key_size) {
    int* key = new int[key_size];
    for (int i = 0; i < key_size; ++i) {
        key[i] = key_structure[i] ? GetRandomNumber() : GetRandomSymbol();
    }
    return key;
}

void PrintKey(const int key[], int key_size) {
    constexpr uint16_t kZeroCodeAscii = 48u;
    string text(key_size, '#');
    for (int i = 0; i < key_size; ++i) {
        text[i] = key[i] < 9 ? key[i] + kZeroCodeAscii : key[i];
    }
    cout << text << endl;
}

int main() {
    constexpr uint16_t kKeySize = 6u;
    constexpr bool kKeyStructure[kKeySize]{1,0,0,0,0,1}; // 1 - цифра, 0 - буква
    int* random_key = GetRandomKey(kKeyStructure, kKeySize);
    PrintKey(random_key, kKeySize);
    delete[] random_key;

    constexpr uint16_t kNumSegments = 3000u; // до 65'535 элементов в таблице
    int hash_table[kNumSegments];
    return 0;
}
