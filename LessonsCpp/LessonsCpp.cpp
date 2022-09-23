#include <iostream>
#include <vector>
#include <string>
#include <utility> // для pair
#include <fstream> // для работы с файлами например .txt
#include <cassert> // для отладки

using namespace std;

vector<vector<string>> FillMatrix() {
    vector<vector<string>> matrix = {
        {"1","2","3","4","5","6","7","8","9","10"},
        {"a","0","0","0","-1","0","0","0","0"},
        {"0","6","0","0","0","0","0","0","0","0"},
        {"0","0","0","0","8","0","0","a","0","0"},
        {"0","0","0","0","0","0","7","0","0","0"},
        {"0","b","0","12","0","0","0","0","0","0"},
        {"0","0","0","0","0","0","0","0","0","-3","0"},
        {"0","0","0","0","15","0","0","0","0","0"},
        {"0","-4","0","0","0","0","0","g","0","0"},
        {"0","0","0","0","11","0","0","0","0","0"},
        {"0","0","0","0","11","0","0","0","0","0"}
    };
    return matrix;
}

void PrintMatrix(const vector<vector<string>>& matrix) {
    for (size_t i = 0; i < matrix.size(); ++i) {
        for (size_t j = 0; j < matrix[i].size(); ++j) {
            cout << matrix[i][j] << " "s;
        }
        cout << endl;
    }
}

vector<pair<string, int>> ParseDataMatrix(const vector<vector<string>>& matrix) {
    vector<pair<string, int>> result(matrix.size() - 1);
    for (size_t i = 1; i < matrix.size(); ++i) {
        for (const string& str : matrix[i]) {
            if (str != "0"s) {
                if (isalpha(str.front())) {
                    result[i - 1].first = str;
                } else {
                    result[i - 1].second = stoi(str);
                }
            }
        }
    }
    return result;
}

vector<int> GetCoordinatesX(const vector<string>& x_coord) {
    vector<int> result(x_coord.size());
    for (size_t i = 0; i < x_coord.size(); ++i) {
        result[i] = stoi(x_coord[i]);
    }
    return result;
}

vector<int> GetCoordinatesY(vector<pair<string, int>> y_coord) {
    vector<int> result(y_coord.size());
    for (size_t i = 0; i < result.size(); ++i) {
        result[i] = y_coord[i].second;
    }
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

/*
 * Класс Polyline моделирует элемент <polyline> для отображения ломаных линий
 * https://developer.mozilla.org/en-US/docs/Web/SVG/Element/polyline
 */
class Polyline {
public:
    // Добавляет очередную вершину к ломаной линии
    //Polyline& AddPoint(Point point);

private:
    //void RenderObject(const RenderContext& context) const override;

    std::vector<Point> points_;
};

void Draw(vector<pair<string, string>>&& data, ostream& out) {
    string begin_svg = "<svg viewBox=\"0 0 200 100\" xmlns=\"http://www.w3.org/2000/svg\">"s;
    string line = "<polyline points=\"0, 100 50, 25 50, 75 100, 0\" />"s;
    string end_svg = "</svg>"s;
    out << begin_svg << line << end_svg;
}

vector<Point> CreatePoints(const vector<int>& coord_x, const vector<int>& coord_y) {
    assert(coord_x.size() == coord_y.size());
    vector<Point> points(coord_x.size());
    for (size_t i = 0; i < coord_x.size(); ++i) {
        points[i] = { static_cast<double>(coord_x[i]), static_cast<double>(coord_y[i]) };
    }
    return points;
}

vector<Point> InvCoordY() {

    return {};
}

Polyline CreatePolilyne(const vector<Point>& points) {
    // без инверсии координат
    Polyline line;

    
    return line;
}

int main() {
    ofstream fout("image.svg");

    vector<vector<string>> matrix = FillMatrix();
    PrintMatrix(matrix);
    vector<pair<string, int>> result_parse = ParseDataMatrix(matrix);
    for (const auto& [key, value] : result_parse) {
        cout << "liter = " << key << " value = " << value << endl;
    }
    //Draw(move(result_parse), fout);
    vector<Point> points = CreatePoints(GetCoordinatesX(matrix.front()), GetCoordinatesY(result_parse));
    //for (const Point& point : points) {
    //    cout << point;
    //}

    return 0;
}