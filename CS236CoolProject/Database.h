//
// Created by pearlhulbert on 10/23/21.
//

#ifndef CS236COOLPROJECT_DATABASE_H
#define CS236COOLPROJECT_DATABASE_H
#include <iostream>
#include <map>
#include "Relation.h"

class Database {
private:
    std::map<std::string, Relation*> dataMap;
public:
    Database() {}
    Database(std::string name, Relation* relation) {
        dataMap.insert(std::pair<std::string, Relation*>(name, relation));
    }
    ~Database() {
    }

    void insert(std::string name, Relation* relation) {
        dataMap.insert(std::pair<std::string, Relation*>(name, relation));
    }

    void setDBRelation(std::string name, Relation* modRelation) {
        dataMap.at(name) = modRelation;
    }

    Relation* matchRelation(std::string name) {
        return dataMap.at(name);
    }

};

#endif //CS236COOLPROJECT_DATABASE_H
