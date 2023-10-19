#include <iostream>
#include <string>
#include <cmath>

using namespace std;

/// ЛР02. Операторы ветвления. Вариант 36

int main() {
    float x = 0.0;
    float y = 0.0;
    cout << "Enter point coordinates:\n"s;
    cout << "x = "s;
    cin >> x;
    cout << "y = "s;
    cin >> y;

    // Значения площадей посчитать самостоятельно в качестве числа ПИ взять M_PI из cmath
    if (((x - 1) * (x - 1) + (y - 1) * (y - 1) < 1) && (x * x + (y - 1) * (y - 1) > 1) && y > 1) { // M1
        cout << "Point is in area M1. S1 = "s << "CALCULATED"s << endl;
    } else if ((x * x + (y - 1) * (y - 1) < 1) && (x * x + y * y < 1) && ((x + 1) * (x + 1) + (y - 1) * (y - 1) < 1)) { // M2
        cout << "Point is in area M2. S2 = "s << "CALCULATED"s << endl;
    } else if (((x - 1) * (x - 1) + y * y < 1) && x < 1 && ((x - 1) * (x - 1) + (y - 1) * (y - 1) > 1)) { // M3
        cout << "Point is in area M3. S3 = "s << "CALCULATED"s << endl;
    } else if (((x + 1) * (x + 1) + (y + 1) * (y + 1) < 1) && ((x + 1) * (x + 1) + y * y < 1) && (x * x + y * y > 1) && (x * x + (y + 1) * (y + 1) > 1)) { // M4
        cout << "Point is in area M4. S4 = "s << "CALCULATED"s << endl;
    }

    cout << "Repeat? y/n\n"s;
    char answer = '#';
    cin >> answer;
    if (answer == 'y') {
        main();
    }
    return 0;
}
