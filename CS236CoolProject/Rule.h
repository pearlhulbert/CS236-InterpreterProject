//
// Created by pearlhulbert on 9/30/21.
//

#ifndef CS236COOLPROJECT_RULE_H
#define CS236COOLPROJECT_RULE_H
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "Predicate.h"

class Rule {
private:
    Predicate* headPredicate;
    std::vector<Predicate*> bodyPredicates;
    bool printedEmpty;
    int numId;
public:
    Rule() {
        printedEmpty = false;
    }
    ~Rule() {
        bodyPredicates.clear();
        delete headPredicate;
    }
    Rule(Predicate* headP, std::vector<Predicate*> preds) {
        headPredicate = headP;
        bodyPredicates = preds;
        printedEmpty = false;
        numId = 0;
    }

    void setPrintCondition(bool condition) {
        printedEmpty = condition;
    }

    void setNumId(int id) {
        numId = id;
    }

    int getNumId() const {
        return numId;
    }

    bool getPrintCondition() const {
        return printedEmpty;
    }

    Predicate* getHead() const {
        return headPredicate;
    }

    std::vector<Predicate*> getRuleBody() const {
        return bodyPredicates;
    }

    std::string toString() const {
        std::stringstream ss;
        ss << headPredicate->toString() << " :- ";
        for (size_t i = 0; i < bodyPredicates.size(); ++i) {
            if (i == bodyPredicates.size() - 1) {
                ss << bodyPredicates.at(i)->toString();
            }
            else {
                ss << bodyPredicates.at(i)->toString() << ",";
            }
        }
        return ss.str();
    }

    friend std::ostream& operator<<(std::ostream& os, Rule r)
    {
        return os << r.toString();
    }

};
#endif //CS236COOLPROJECT_RULE_H
