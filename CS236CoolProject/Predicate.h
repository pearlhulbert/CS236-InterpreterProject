//
// Created by pearlhulbert on 9/30/21.
//

#ifndef CS236COOLPROJECT_PREDICATE_H
#define CS236COOLPROJECT_PREDICATE_H
#include <iostream>
#include "Parameter.h"
#include <string>
#include <sstream>
#include <vector>

class Predicate {
private:
    std::string id = "";
    std::vector<Parameter*> parameters;
public:
  Predicate() = default;
  ~Predicate() {
      for (size_t i = 0; i < parameters.size(); ++i) {
          delete parameters.at(i);
      }
      parameters.clear();
  }
  Predicate(std::string iD, std::vector<Parameter*> params) {
      id = iD;
      parameters = params;
  }

  std::string getName() const {
      return id;
  }

  std::vector<std::string> getBody() const {
      std::vector<std::string> parameterStrings;
      for (size_t i = 0; i < parameters.size(); ++i) {
          parameterStrings.push_back(parameters.at(i)->toString());
      }
      return parameterStrings;
  }

  std::string toString() const {
      std::stringstream ss;
      std::string returnString;
      ss << id << "(";
      for (size_t i = 0; i < parameters.size(); ++i) {
          if (i == parameters.size() - 1) {
              ss << parameters.at(i)->toString();
          }
          else {
              ss << parameters.at(i)->toString() << ",";
          }
      }
      ss << ")";
      return ss.str();
  }

  friend std::ostream& operator<<(std::ostream& os, Predicate pred)
  {
    return os << pred.toString();
  }

};

#endif //CS236COOLPROJECT_PREDICATE_H
