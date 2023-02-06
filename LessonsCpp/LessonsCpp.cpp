#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <cassert>

using namespace std;

// out - куда, text - что
void WriteToStream(ostream& out, const vector<string>& text) {
    for (const string& str : text) {
        out << str << endl;
    }
}

void WriteToFile(const string& name_file, const vector<string>& text) {
    ofstream fout(name_file);
    WriteToStream(fout, text);
    fout.close();
}

void Test() {
    {
        vector<string> text = { "Hello mtischi"s, "I am Viktor"s, "I from is Dragunka"s };
        string only_string;
        for (const string& str : text) {
            only_string += (str + '\n');
        }
        stringstream etalon;
        WriteToStream(etalon, text);
        assert(etalon.str() == only_string);
    }
}

int main() {
    Test();

    string name_file = "MyFile.txt"s;
    vector<string> text = { "Hello mtischi"s, "I am Viktor"s, "I from is Dragunka"s };

    WriteToFile(name_file, text);
    return 0;
}