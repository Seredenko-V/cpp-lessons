#include <iostream>
#include <string>
#include <random>
#include <cassert>
#include <fstream>
#include <functional>

using namespace std;

/// ЛР04. Хеширование данных. Вариант 11.
/// Формат ключа: БццццБ
/// Количество сегментов: 3000
/// Метод хеширования: Квадратичное опробование

// ======================================== РАНДОМАЙЗЕР КЛЮЧЕЙ ==========================================>
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
uint16_t* GetRandomKey(const bool key_structure[], uint16_t key_size) {
    uint16_t* key = new uint16_t[key_size];
    for (uint16_t i = 0; i < key_size; ++i) {
        key[i] = key_structure[i] ? GetRandomNumber() : GetRandomSymbol();
    }
    return key;
}

string IntArrToStr(const uint16_t key[], uint16_t key_size) {
    constexpr uint16_t kZeroCodeAscii = 48u;
    string text(key_size, '#');
    for (uint16_t i = 0; i < key_size; ++i) {
        text[i] = key[i] < 10 ? key[i] + kZeroCodeAscii : key[i];
    }
    return text;
}

void PrintKey(const uint16_t key[], uint16_t key_size) {
    cout << IntArrToStr(key, key_size) << endl;
}
// <======================================== РАНДОМАЙЗЕР КЛЮЧЕЙ ==========================================
// #######################################################################################################
// ============================================= ХЕШИРОВАНИЕ ============================================>
struct Segment {
    uint16_t* key = nullptr;
    uint32_t number_calculated_hash = 0u;
};

/// Информация, необходимая для корректировки хеша, чтобы использовались все ячейки таблицы
struct CorrectKey {
    uint16_t min_key_code = 0u;
    uint16_t max_key_code = 0u;
    uint16_t expansion_coef = 0u;
};

CorrectKey DetermineDataForCorrectKeys(const bool key_structure[], uint16_t key_size, uint16_t num_segments) {
    static constexpr uint16_t kMinDigitCode = '0';
    static constexpr uint16_t kMaxDigitCode = '9';
    static constexpr uint16_t kMinSymbolCode = 'A';
    static constexpr uint16_t kMaxSymbolCode = 'Z';

    uint16_t min_key_code = 0u;
    uint16_t max_key_code = 0u;
    for (uint16_t i = 0; i < key_size; ++i) {
        if (key_structure[i]) { // если цифра
            min_key_code += kMinDigitCode;
            max_key_code += kMaxDigitCode;
        } else {
            min_key_code += kMinSymbolCode;
            max_key_code += kMaxSymbolCode;
        }
    }
    uint16_t expansion_coef = num_segments / (max_key_code - min_key_code);
    return {min_key_code, max_key_code, expansion_coef};
}

/// Освобождение динамической памяти, выделенной для ключей
void DeteleKeys(Segment hash_table[], uint16_t num_segments) {
    for (uint16_t i = 0; i < num_segments; ++i) {
        if (hash_table[i].key) {
            delete[] hash_table[i].key;
        }
    }
}

uint16_t GetSimpleHash(const uint16_t key[], uint16_t key_size) {
    uint16_t hash_value = 0;
    for (uint16_t i = 0; i < key_size; ++i) {
        hash_value += key[i]; // переполнение на этом этапе скажется положительно
    }
    return hash_value;
}

uint16_t GetGoodHash(const uint16_t key[], uint16_t key_size) {
    uint16_t hash_value = 0;
    for (uint16_t i = 0; i < key_size; ++i) {
        hash_value += key[i] * key[i] * i; // переполнение на этом этапе скажется положительно
    }
    return hash_value;
}

uint16_t GetQuadraticProbHash(Segment& segment, uint16_t key_size, uint16_t num_segments, CorrectKey correcter_keys,
                              function<uint16_t(const uint16_t*, uint16_t)> hash_func) {
    static constexpr uint16_t kFirstSimpleValue = 29u;
    static constexpr uint16_t kSecondSimpleValue = 101u;
    uint32_t& number_calculated_hash = segment.number_calculated_hash;
    uint16_t hash_value = hash_func(segment.key, key_size)
            + kFirstSimpleValue * number_calculated_hash + kSecondSimpleValue * number_calculated_hash * number_calculated_hash;
    hash_value = ((hash_value - correcter_keys.min_key_code) * correcter_keys.expansion_coef);
    ++number_calculated_hash;
    return hash_value % num_segments;
}

void RunHesher(const bool key_structure[], uint16_t key_size, Segment hash_table[], uint16_t num_segments,
               function<uint16_t(const uint16_t*, uint16_t)> hash_func = GetGoodHash) {
    const uint32_t kNumKeys = num_segments * 3;
    const uint32_t kMaxNumProb = kNumKeys * 2;
    const CorrectKey kCorrecterKeys = DetermineDataForCorrectKeys(key_structure, key_size, num_segments);
    for (uint32_t key_id = 0; key_id < kNumKeys; ++key_id) {
        Segment new_segment{GetRandomKey(key_structure, key_size), 0};
        uint16_t hash_value = GetQuadraticProbHash(new_segment, key_size, num_segments, kCorrecterKeys, hash_func);
        // сегмент по данному хешу существует и еще не достигнут максимум проб
        while (hash_table[hash_value].key != nullptr && new_segment.number_calculated_hash != kMaxNumProb) {
            hash_value = GetQuadraticProbHash(new_segment, key_size, num_segments, kCorrecterKeys, hash_func);
        }
        // если достигнут максимум проб, то сегмент не будет добавлен в таблицу и переходим к следующему ключу
        if (new_segment.number_calculated_hash == kMaxNumProb) {
            continue;
        }
        hash_table[hash_value] = new_segment;
    }
}

void PrintStatToFile(Segment hash_table[], uint16_t num_segments, const string& file_name = "hash_stat.txt"s) {
    ofstream fout(file_name);
    assert(fout.is_open());
    for (uint16_t i = 0; i < num_segments; ++i) {
        fout << hash_table[i].number_calculated_hash << endl;
    }
}
// <============================================ ХЕШИРОВАНИЕ =============================================
// #######################################################################################################
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
            uint16_t* random_key = GetRandomKey(key_structure, kKeySize);
            string key = IntArrToStr(random_key, kKeySize);
            for (uint16_t j = 0; j < static_cast<int>(key.size()); ++j) {
                if (key_structure[j]) {
                    assert(isdigit(key[j]));
                } else {
                    assert(isupper(key[j]));
                }
            }
            delete[] random_key;
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
    { // с плохой хеш-функцией
        Segment hash_table[kNumSegments];
        cout << "Hashing random keys with simple hash function, wait...\n"s;
        RunHesher(kKeyStructure, kKeySize, hash_table, kNumSegments, GetSimpleHash);
        PrintStatToFile(hash_table, kNumSegments, "simple_hash_stat.txt"s);
        DeteleKeys(hash_table, kNumSegments);
        cout << "Hashing random keys with simple hash function finished successfully.\n"s;
    }{ // с хорошей хеш-функцией
        Segment hash_table[kNumSegments];
        cout << "Hashing random keys with good hash function, wait...\n"s;
        RunHesher(kKeyStructure, kKeySize, hash_table, kNumSegments, GetGoodHash);
        PrintStatToFile(hash_table, kNumSegments, "good_hash_stat.txt"s);
        DeteleKeys(hash_table, kNumSegments);
        cout << "Hashing random keys with good hash function finished successfully.\n"s;
    }
    return 0;
}
