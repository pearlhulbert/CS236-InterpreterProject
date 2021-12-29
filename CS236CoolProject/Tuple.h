//
// Created by pearlhulbert on 10/23/21.
//

#ifndef CS236COOLPROJECT_TUPLE_H
#define CS236COOLPROJECT_TUPLE_H
#include <iostream>
#include <string>
#include <vector>
#include "DatalogProgram.h"

class Tuple {
private:
    std::vector<std::string> values;
public:
    Tuple() {}
    Tuple(std::vector<std::string> vals) {
        values = vals;
    }
    ~Tuple() {
        values.clear();
    }

    bool operator< (const Tuple &rhs) const {
        return values < rhs.values;
    }

    bool operator == (const Tuple &rhs) const {
        return values == rhs.values;
    }

    bool operator!= (const Tuple &rhs) const {
        return values != rhs.values;
    }

    std::string toString() const {
        std::stringstream ss;
        for (std::string val: values) {
            ss << val;
        }
        return ss.str();
    }

    size_t size() {
        return values.size();
    }

    std::vector<std::string> getValues() const {
        return values;
    }

    std::string at(int index) {
        return values.at(index);
    }

    friend std::ostream& operator<<(std::ostream& os,  const Tuple &tu)
    {
        return os << tu.toString();
    }

};

#endif //CS236COOLPROJECT_TUPLE_H
