#include <iostream>
#include <string>
#include <random>
#include <cassert>

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
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(min_value, max_value);
    return dist(gen);
}

/// Генерирование случайного символа в диапазоне [min_symbol; max_symbol]. По умолчанию [A; Z]
char GetRandomSymbol(char min_symbol = 'A', char max_symbol = 'Z') {
    // произойдет неявная конвертация char к int согласно кодировке ascii
    return GetRandomNumber(min_symbol, max_symbol);
}

/// Генерирование случайного ключа в куче
int* GetRandomKey(const bool key_structure[], int key_size) {
    int* key = new int[key_size];
    for (int i = 0; i < key_size; ++i) {
        key[i] = key_structure[i] ? GetRandomNumber() : GetRandomSymbol();
    }
    return key;
}

string IntArrToStr(const int key[], int key_size) {
    constexpr uint16_t kZeroCodeAscii = 48u;
    string text(key_size, '#');
    for (int i = 0; i < key_size; ++i) {
        text[i] = key[i] < 10 ? key[i] + kZeroCodeAscii : key[i];
    }
    return text;
}

void PrintKey(const int key[], int key_size) {
    cout << IntArrToStr(key, key_size) << endl;
}

// =========================== НАЧАЛО ТЕСТОВ, ПРОВЕРЯЮЩИХ КОРРЕКТНОСТЬ РАБОТЫ ===========================>

void TestKeysRandomGenerator() {
    constexpr uint16_t kKeySize = 6u;
    constexpr uint16_t kNumChecksRandomStructKeys = 20u;
    constexpr uint16_t kNumChecksRandomKeys = 100u;
    for (uint16_t key_id = 0; key_id < kNumChecksRandomStructKeys; ++key_id) {
        bool key_structure[kKeySize];
        // генерируется случайная структура ключа
        for (uint16_t i = 0; i < kKeySize; ++i) {
            key_structure[i] = GetRandomNumber(0, 1);
        }
        // генерируются случайные ключи
        for (uint16_t i = 0; i < kNumChecksRandomKeys; ++i) {
            int* random_key = GetRandomKey(key_structure, kKeySize);
            string key = IntArrToStr(random_key, kKeySize);
            for (uint16_t j = 0; j < static_cast<int>(key.size()); ++j) {
                if (key_structure[j]) {
                    assert(isdigit(key[j]));
                } else {
                    assert(isupper(key[j]));
                }
            }
            delete random_key;
        }
    }
    cerr << "TestKeysRandomGenerator has passed\n";
}

// <=========================== КОНЕЦ ТЕСТОВ, ПРОВЕРЯЮЩИХ КОРРЕКТНОСТЬ РАБОТЫ ===========================


int main() {
    TestKeysRandomGenerator();
    constexpr uint16_t kKeySize = 6u;
    constexpr bool kKeyStructure[kKeySize]{0,1,1,1,1,0}; // 1 - цифра, 0 - буква
    constexpr uint16_t kNumSegments = 3000u; // до 65'535 элементов в таблице
    int hash_table[kNumSegments];
    return 0;
}
