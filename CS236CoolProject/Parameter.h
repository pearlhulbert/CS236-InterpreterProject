//
// Created by pearlhulbert on 9/30/21.
//

#ifndef CS236COOLPROJECT_PARAMETER_H
#define CS236COOLPROJECT_PARAMETER_H
#include <iostream>
#include <sstream>
#include <sstream>

class Parameter {
private:
    std::string param;
public:
    Parameter() = default;
    ~Parameter() = default;
    Parameter(std::string p) {
        param = p;
    }

    std::string toString() const {
        std::stringstream ss;
        ss << param;
        return ss.str();
    }

    friend std::ostream& operator<<(std::ostream& os, Parameter par)
    {
        return os << par.toString();
    }
};
#endif //CS236COOLPROJECT_PARAMETER_H
