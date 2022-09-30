#include <iostream>
#include <vector>
#include <string>
#include <utility> // для pair
#include <fstream> // для работы с файлами например .txt
#include <cassert> // для отладки

using namespace std;

vector<string> ReadMatrixFromFile(const string& name_file) {
    ifstream fin(name_file);
    if (!fin.is_open()) {
        cout << "File "s << name_file << " no opened"s << endl;
        return {};
    }

    vector<string> data_file;
    string line;
    while (getline(fin, line)) {
        if (line.empty() || line.front() < 32 || line.front() > 126) {
            continue;
        }
        data_file.push_back(line);
    }

    return data_file;
}

vector<pair<char, int>> ParseDataMatrix(vector<string>&& matrix) {
    vector<pair<char, int>> result(matrix.size() - 1);

    for (size_t i = 1; i < matrix.size(); ++i) {
        string value;
        for (const char& symbol : matrix[i]) {
            if (symbol == ' ') {
                continue;
            }
            // если текущий символ буква - записываем его как букву
            // иначе - накапливаем строку из ненулевых значений, после чего приводим ее к int
            if (isalpha(symbol)) {
                result[i - 1].first = symbol;
            } else if (symbol != '0') {
                value += symbol;
            }
        }
        result[i - 1].second = stoi(value);
    }

    return result;
}

vector<int> GetCoordinatesX(const string& x_coord) {
    vector<int> result;

    size_t end_value_pos = x_coord.find_first_of(' ');
    size_t begin_value_pos = 0;
    while (end_value_pos != x_coord.npos) {
        result.push_back(stoi(x_coord.substr(begin_value_pos, end_value_pos - begin_value_pos)));
        begin_value_pos = end_value_pos + 1;
        end_value_pos = x_coord.find_first_of(' ', begin_value_pos);
    }
    result.push_back(stoi(x_coord.substr(begin_value_pos, x_coord.npos - begin_value_pos)));

    return result;
}

struct Point {
    Point() = default;
    Point(double x, double y)
        : x(x)
        , y(y) {
    }
    double x = 0;
    double y = 0;
};

ofstream& operator<<(ofstream& output, const Point& point) {
    output << "X = "s << point.x << "Y = "s << point.y << endl;
    return output;
}

// Класс Polyline моделирует элемент <polyline> для отображения ломаных линий
// https://developer.mozilla.org/en-US/docs/Web/SVG/Element/polyline
class Polyline {
public:
    // Добавляет очередную вершину к ломаной линии
    Polyline& AddPoint(Point point) {
        points_.push_back(point);
    }

private:
    //void RenderObject(const RenderContext& context) const override;

    std::vector<Point> points_;
};

Polyline CreatePolilyne(const vector<int>& coord_x, const vector<pair<char, int>> coord_y) {
    Polyline line;
    // идем до coord_y.size() т.к. без значений для оси ординат график не построить
    for (size_t i = 0; i < coord_y.size(); ++i) {

    }

    return line;
}

void Draw(vector<pair<string, string>>&& data, ostream& out) {
    string begin_svg = "<svg viewBox=\"0 0 200 100\" xmlns=\"http://www.w3.org/2000/svg\">"s;
    string line = "<polyline points=\"0, 100 50, 25 50, 75 100, 0\" />"s;
    string end_svg = "</svg>"s;
    out << begin_svg << line << end_svg;
}

//vector<Point> CreatePoints(const vector<int>& coord_x, const vector<int>& coord_y) {
//    assert(coord_x.size() == coord_y.size());
//    vector<Point> points(coord_x.size());
//    for (size_t i = 0; i < coord_x.size(); ++i) {
//        points[i] = { static_cast<double>(coord_x[i]), static_cast<double>(coord_y[i]) };
//    }
//    return points;
//}

vector<Point> InvCoordY() {

    return {};
}



int main() {
    string name_file = "Task.txt"s;
    // считываем из файла матрицу (без текста задания)
    vector<string> data_file = ReadMatrixFromFile(name_file);
    for (const string& str : data_file) {
        cout << str << endl;
    }
    cout << "==========================" << endl;

    // получаем координаты оси абсцис из первой строки матрицы
    vector<int> Coordinates_X = GetCoordinatesX(data_file.front());
    cout << "Coordinates_X = "s;
    for (const int& value : Coordinates_X) {
        cout << value << " "s;
    }
    cout << endl;
    cout << "==========================" << endl;

    // получаем координаты оси ординат с имеющимися обозначениями (буквами)
    vector<pair<char, int>> data_matrix = ParseDataMatrix(move(data_file));
    for (const auto& [liter, value] : data_matrix) {
        cout << "liter = " << liter << '\t' << "value = " << value << endl;
    }
    cout << "==========================" << endl;

    // получаем вектор точек, по которым будем строить график



    //ofstream fout("image.svg");


    ////Draw(move(result_parse), fout);
    //vector<Point> points = CreatePoints(GetCoordinatesX(matrix.front()), GetCoordinatesY(result_parse));
    ////for (const Point& point : points) {
    ////    cout << point;
    ////}

    return 0;
}