#include <iostream>
#include <string>
#include <map>

using namespace std;

int main() {

    map<string, string> test_input = { {"cat"s, "meow"s},
                                       {"dog"s, "bark"s},
                                       {"cow"s, "moo"s},
                                       {"owl"s, "hoot"s},
                                       {"tiger"s, "roar"s} };

    map<string, string> test_output = { {"bark"s, "dog"s},
                                        {"hoot"s, "owl"s},
                                        {"meow"s, "cat"s},
                                        {"moo"s, "cow"s},
                                        {"roar"s, "tiger"s} };
    /* Необходимо поменять ключи и значения местами. 
    test_input - исходный map
    test_output - результат замены */
    return 0;
}