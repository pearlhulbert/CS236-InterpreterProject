//
// Created by pearlhulbert on 10/23/21.
//

#ifndef CS236COOLPROJECT_HEADER_H
#define CS236COOLPROJECT_HEADER_H
#include <iostream>
#include <string>
#include <vector>
#include "DatalogProgram.h"

class Header {
private:
    std::vector<std::string> attributes;
public:
    Header() {}
    Header(std::vector<std::string> att) {
        attributes = att;
    }
    ~Header() {
    }

    std::string toString() const {
        std::stringstream ss;
        for (std::string attr : attributes) {
            ss << attr << std::endl;
        }
        return ss.str();
    }

    void setAttributes(std::vector<std::string> newAttributes) {
        attributes = newAttributes;
    }

    std::vector<std::string> getAttributes() const {
        return attributes;
    }

    std::string at(int index) {
        return attributes.at(index);
    }

    size_t size() {
        return attributes.size();
    }

    friend std::ostream& operator<<(std::ostream& os,  const Header &head)
    {
        return os << head.toString();
    }

};

#endif //CS236COOLPROJECT_HEADER_H
