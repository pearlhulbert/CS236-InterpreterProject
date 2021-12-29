//
// Created by pearlhulbert on 9/25/21.
//

#ifndef CS236COOLPROJECT_DATALOGPROGRAM_H
#define CS236COOLPROJECT_DATALOGPROGRAM_H
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <set>
#include "Predicate.h"
#include "Rule.h"

class DataLogProgram {
private:
    std::vector<Predicate *> schemes;
    std::vector<Predicate *> facts;
    std::vector<Rule *> rules;
    std::vector<Predicate *> queries;
    std::set<std::string> domain;
public:
    DataLogProgram() = default;
    ~DataLogProgram() {
        for (size_t i = 0; i < schemes.size(); ++i) {
            delete schemes.at(i);
        }
        schemes.clear();
        for (size_t i = 0; i < facts.size(); ++i) {
            delete facts.at(i);
        }
        facts.clear();
        for (size_t i = 0; i < rules.size(); ++i) {
            delete rules.at(i);
        }
        rules.clear();
        for (size_t i = 0; i < queries.size(); ++i) {
            delete queries.at(i);
        }
        queries.clear();
        domain.clear();
    }
    DataLogProgram(std::vector<Predicate*> scheme, std::vector<Predicate*> fact,
                   std::vector<Rule*> rule, std::vector<Predicate*> query,
                   std::set<std::string> dom) {
        schemes = scheme;
        facts = fact;
        rules = rule;
        queries = query;
        domain = dom;
    }

    std::vector<Predicate*> getSchemes() const {
        return schemes;
    }

    std::vector<Predicate*> getFacts() const {
        return facts;
    }

    std::vector<Predicate*> getQueries() const {
        return queries;
    }

    std::vector<Rule*> getRules() const {
        return rules;
    }

    std::string toString() const {
        std::stringstream ss;
        ss << "Schemes(" << schemes.size() << "):" << std::endl;
        for (size_t i = 0; i < schemes.size(); ++i) {
            ss << "  " << schemes.at(i)->toString() << std::endl;
        }

        ss << "Facts(" << facts.size() << "):" << std::endl;
        for (size_t i = 0; i < facts.size(); ++i) {
            ss << "  " << facts.at(i)->toString() << "." << std::endl;
        }

        ss << "Rules(" << rules.size() << "):" << std::endl;
        for (size_t i = 0; i < rules.size(); ++i) {
            ss << "  " << rules.at(i)->toString() << "." << std::endl;
        }

        ss << "Queries(" << queries.size() << "):" << std::endl;
        for (size_t i = 0; i < queries.size(); ++i) {
            ss << "  " << queries.at(i)->toString() << "?" << std::endl;
        }

        ss << "Domain(" << domain.size() << "):" << std::endl;
        std::set<std::string>::iterator itr = domain.begin();
        std::string currP = *itr;
        while (itr != domain.end()) {
            currP = *itr;
            ss << currP << std::endl;
            ++itr;
        }
        return ss.str();
    }

    friend std::ostream& operator<<(std::ostream& os, DataLogProgram dL)
    {
        return os << dL.toString();
    }

};

#endif //CS236COOLPROJECT_DATALOGPROGRAM_H
