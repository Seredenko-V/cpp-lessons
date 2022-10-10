#include <iostream>
#include <vector>
#include <string>
#include <utility> // для pair
#include <fstream> // для работы с файлами например .txt
#include <cassert> // для отладки
#include <algorithm>
#include <optional>

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

vector<int> GetCoordinatesY(const vector<pair<char, int>>& coord_y_and_text) {
    vector<int> only_coord(coord_y_and_text.size());
    for (size_t i = 0; i < only_coord.size(); ++i) {
        only_coord[i] = coord_y_and_text[i].second;
    }
    return only_coord;
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

struct BordersImage {
    uint32_t x = 100;
    uint32_t y = 100;
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
        return *this;
    }

    Polyline& SetColor(string&& color) {
        color_ = move(color);
        return *this;
    }


    ostream& GetTextSVG(ostream& out) const {
        out << "<polyline points=\""sv;
        bool is_first = true;
        for (const Point& point : points_) {
            if (is_first) {
                out << point.x << ","sv << point.y;
                is_first = false;
            } else {
                out << " "sv << point.x << ","sv << point.y;
            }
        }
        out << "\" fill=\"none\" stroke=\"" << color_ << "\""sv;
        out << "/>"sv;
        return out;
    }

private:
    vector<Point> points_;
    string color_ = "black"s;
};

/*
* Класс Circle моделирует элемент <circle> для отображения круга
* https://developer.mozilla.org/en-US/docs/Web/SVG/Element/circle
*/
class Circle {
public:
    Circle& SetCenter(Point center) {
        center_ = center;
        return *this;
    }
    Circle& SetRadius(double radius) {
        radius_ = radius;
        return *this;
    }
    Circle& SetColor(string&& color) {
        color_ = move(color);
        return *this;
    }

    ostream& GetTextSVG(ostream& out) const {
        out << "<circle cx=\""sv << center_.x << "\" cy=\""sv << center_.y << "\" "sv;
        out << "r=\""sv << radius_ << "\" fill=\"" << color_ << "\"";
        out << "/>"sv;
        return out;
    }

private:
    Point center_ = { 0.0, 0.0 };
    double radius_ = 1.0;
    string color_ = "red"s;
};

// Перерасчет координат У для рисования графика в положительной плоскости (см. оси координат изображений)
void SetOnlyPositiveValues(vector<int>& coordinates) {
    // находим модуль минимального значения
    uint32_t mod_min_value = abs(*min_element(coordinates.begin(), coordinates.end()));
    // прибавляем ко всем элементам найденное значение (чтобы поднять график в положительную плоскость)
    for (int& value : coordinates) {
        value += mod_min_value + 1;
    }
}

// инверсия координат для привычного восприятия графика (не перевернутого)
void InversCoordinates(vector<int>& coordinates) {
    for (int& value : coordinates) {
        value *= -1;
    }
}

void PrepareCoordinates(vector<int>& coordinates) {
    InversCoordinates(coordinates);
    SetOnlyPositiveValues(coordinates);
}

BordersImage FindBordersImage(const vector<int>& coord_x, const vector<int> coord_y) {
    // +1 для того, чтобы отчетливо была видна минимальная точка
    uint32_t max_x = *max_element(coord_x.begin(), coord_x.end()) + 1;
    uint32_t max_y = *max_element(coord_y.begin(), coord_y.end()) + 1;
    return { max_x, max_y };
}


vector<Point> CreateVectorPoint(const vector<int>& coord_x, const vector<int> coord_y) {
    vector<Point> points(coord_y.size());
    for (size_t i = 0; i < points.size(); ++i) {
        points[i] = { static_cast<double>(coord_x[i]), static_cast<double>(coord_y[i]) };
    }
    return points;
}

Polyline CreatePolilyne(const vector<Point>& points) {
    Polyline line;
    // идем до coord_y.size() т.к. без значений для оси ординат график не построить
    for (size_t i = 0; i < points.size(); ++i) {
        line.AddPoint(points[i]);
    }
    return line;
}

void Draw(BordersImage&& bourders, const vector<Point>& points, ostream& out) {
    Polyline line = CreatePolilyne(points);

    out << "<svg viewBox=\"0 0 "sv << bourders.x << " "sv << bourders.y << "\" xmlns=\"http://www.w3.org/2000/svg\">"sv;
    line.GetTextSVG(out);
    for (const Point& point : points) {
        Circle circle;
        circle.SetCenter(point).SetRadius(0.5);
        circle.GetTextSVG(out);
    }

    out << "</svg>"sv;
}

int main() {
    string name_file = "Task.txt"s;
    // считываем из файла матрицу (без текста задания)
    vector<string> data_file = ReadMatrixFromFile(name_file);

    // получаем координаты оси абсцис из первой строки матрицы
    vector<int> Coordinates_X = GetCoordinatesX(data_file.front());

    // получаем координаты оси ординат с имеющимися обозначениями (буквами)
    vector<pair<char, int>> data_matrix = ParseDataMatrix(move(data_file));

    vector<int> Coordinates_Y = GetCoordinatesY(data_matrix);
    PrepareCoordinates(Coordinates_Y);

    vector<Point> points = CreateVectorPoint(Coordinates_X, Coordinates_Y);

    // добавить надписи к точкам
    // сделать концы линии круглыми

    ofstream fout("image.svg");
    Draw(FindBordersImage(Coordinates_X, Coordinates_Y), points, fout);


    return 0;
}