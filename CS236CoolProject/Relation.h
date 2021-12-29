//
// Created by pearlhulbert on 10/23/21.
//

#ifndef CS236COOLPROJECT_RELATION_H
#define CS236COOLPROJECT_RELATION_H
#include <iostream>
#include <set>
#include <string>
#include <list>
#include "Header.h"
#include "Tuple.h"

class Relation {
private:
    std::string name;
    Header* attributes;
    std::set<Tuple> tuples;
    std::list<std::pair<int, int>> matchIndices;
    std::vector<int> uniqueIndices;
    std::set<Tuple> addedTuples;
public:
    Relation() {}
    Relation(std::string rName, Header* rHeader) {
        name = rName;
        attributes = rHeader;
    }
    ~Relation() {
    }


    int newTupleNum() const {
        return addedTuples.size();
    }

    std::string getName() const {
        return name;
    }

    Header* getHeader() const {
        return attributes;
    }

    void setHeader(Header* head) {
        attributes = head;
    }

    void setTuples(std::set<Tuple> setTuples) {
        tuples = setTuples;
    }

    void setName(std::string newName) {
        name = newName;
    }

    void addTuple(Tuple tup) {
        tuples.insert(tup);
    }

    size_t size() {
        return tuples.size();
    }

    std::set<Tuple> getTuples() const {
        return tuples;
    }

    std::set<Tuple> getAddTuples() const {
        return addedTuples;
    }

    bool matchTuple(int matchIndex, Tuple unionTul) {
        return false;
    }

    bool findAttributeIn(std::string findString, std::vector<std::string> newAttributes) {
        for (size_t i = 0; i < newAttributes.size(); ++i) {
            if (newAttributes.at(i) == findString) {
                return true;
            }
        }
        return false;
    }

    bool match(std::string matchString, int index) {
        if (matchString == attributes->at(index)) {
                return true;
            }
        return false;
    }

    Header* combineHeaders(Header* joinHeader) {
        std::vector<std::string> newAttributes = attributes->getAttributes();
        std::pair<int, int> matchPair;
        Header* newHeader = new Header(newAttributes);
        for (size_t i = 0; i < attributes->size(); ++i) {
            for (size_t j = 0; j < joinHeader->size(); ++j) {
                if (match(joinHeader->at(j), i)) {
                    matchPair = std::make_pair(i, j);
                    matchIndices.push_back(matchPair);
                    continue;
                }
                else {
                    if (findAttributeIn(joinHeader->at(j), newAttributes)) {
                        continue;
                    }
                    else {
                        newAttributes.push_back(joinHeader->at(j));
                        uniqueIndices.push_back(j);
                    }
                }
            }
        }
        newHeader->setAttributes(newAttributes);
        return newHeader;
    }

    bool isJoinable(Tuple t1, Tuple t2, bool headMatch) {
        if (matchIndices.empty()) {
            return true;
        }
        if (headMatch) {
            for (std::pair<int, int> matchPair : matchIndices) {
                if (matchPair.first == matchPair.second) {
                    if ((t1.at(matchPair.first) != t2.at(matchPair.second)) || (t1.toString() != t2.toString())) {
                        return false;
                    }
                    return true;
                }
                else {
                    if (t1.toString() != t2.toString()) {
                        if (t1.at(matchPair.first) == t2.at(matchPair.second)) {
                            if (t1.size() == t2.size()) {
                                if (t1.at(matchPair.second) != t2.at(matchPair.first)) {
                                    return false;
                                }
                            }
                            return true;
                        }
                        return false;
                    }
                }
            }
            return true;
        }
        for (std::pair<int, int> matchPair : matchIndices) {
            if (t1.at(matchPair.first) == t2.at(matchPair.second)) {
                return true;
            }
        }
        return false;
    }

    size_t getIndex(Tuple t1, Tuple t2) {
        size_t index = 0;
        if (matchIndices.empty()) {
            return index;
        }
        for (std::pair<int, int> matchPair : matchIndices) {
            if (t1.at(matchPair.first) == t2.at(matchPair.second)) {
                index = matchPair.second;
            }
        }
        return index;
    }


    Tuple combineTuples(Tuple t1, Tuple t2, size_t match) {
        std::vector<std::string> tupleVals;
        for (size_t i = 0; i < t1.size(); ++i) {
            tupleVals.push_back(t1.at(i));
        }
        if (matchIndices.empty()) {
            for (size_t i = 0; i < t2.size(); ++i) {
                tupleVals.push_back(t2.at(i));
            }
        }
        else {
            for (size_t i = 0; i < t2.size(); ++i) {
                if (i != match) {
                    tupleVals.push_back(t2.at(i));
                }
            }
        }
        Tuple returnTuple = Tuple(tupleVals);
        return returnTuple;
    }


    Relation* selectType1(int column, std::string value) {
        Relation* newRelation = new Relation(name, attributes);
        std::vector<std::string> newValues;
        for (Tuple tul : tuples) {
                if (tul.at(column) == value) {
                    newRelation->addTuple(tul);
                }
        }
        return newRelation;
    }

    Relation* selectType2(int column1, int column2) {
        Relation* newRelation = new Relation(name, attributes);
        Tuple newTuple;
        std::vector<std::string> newAttributes;
        std::vector<std::string> newValues;
        for (Tuple tul : tuples) {
            if (tul.at(column1) == tul.at(column2)) {
                newRelation->addTuple(tul);
            }
        }
        return newRelation;
    }

    Relation* project(std::vector<int> keepColumns) {
        Header* newHeader;
        Relation* newRelation = new Relation(name, attributes);
        Tuple newTuple;
        std::vector<std::string> newAttributes;
        std::vector<std::string> newValues;
        for (size_t i = 0; i < keepColumns.size(); ++i) {
            newAttributes.push_back(attributes->at(keepColumns.at(i)));
        }
        for (Tuple tul : tuples) {
            for (size_t i = 0; i < keepColumns.size(); ++i) {
                newValues.push_back(tul.at(keepColumns.at(i)));
            }
            newTuple = Tuple(newValues);
            newRelation->addTuple(newTuple);
            newValues.clear();
        }
        newHeader = new Header(newAttributes);
        newRelation->setHeader(newHeader);
        return newRelation;
    }

    Relation* rename(std::vector<std::string> newAttributes) {
        Header* newHeader;
        Relation* newRelation;
        std::vector<std::string> newValues;
        Tuple newTuple;
        newHeader = new Header(newAttributes);
        newRelation = new Relation(name, newHeader);
        //copy tuples over
        for (Tuple tul : tuples) {
            for (size_t i = 0; i < newAttributes.size(); ++i) {
               newValues.push_back(tul.at(i));
            }
            newTuple = Tuple(newValues);
            newRelation->addTuple(newTuple);
            newValues.clear();
        }
        return newRelation;
    }

    Relation* naturalJoin(Relation* relToJoin) {
        Relation* newRelation = new Relation(name, attributes);
        std::set<Tuple> joinTuples = relToJoin->getTuples();
        Header* joinHead = relToJoin->getHeader();
        Header* newHead = combineHeaders(joinHead);
        newRelation->setHeader(newHead);
        bool headMatch = false;
        if (newHead->size() == attributes->size()) {
            for (size_t i = 0; i < attributes->size(); ++i) {
                if (newHead->at(i) == attributes->at(i)) {
                    headMatch = true;
                    continue;
                }
                headMatch = false;
            }
        }
        if (headMatch && (tuples == joinTuples)) {
            newRelation->setTuples(tuples);
            return newRelation;
        }
        for (Tuple tul : tuples) {
            for (Tuple joinTul : joinTuples) {
                if (isJoinable(tul, joinTul, headMatch)) {
                    size_t match = getIndex(tul, joinTul);
                    Tuple newTuple = combineTuples(tul, joinTul, match);
                    newRelation->addTuple(newTuple);
                }
            }
        }
        return newRelation;
    }

    void makeUnion(Relation* currRelation) {
        std::set<Tuple> unionTuples = currRelation->getTuples();
        bool added = false;
        if (this->getTuples() == currRelation->getTuples()) {
            addedTuples.clear();
            return;
        }
        else if (currRelation->getName() == name && !addedTuples.empty()) {
            addedTuples.clear();
        }
        else if (unionTuples == addedTuples) {
            addedTuples.clear();
            return;
        }
        for (Tuple unionTul : unionTuples) {
            added = tuples.insert(unionTul).second;
            if (added) {
                addTuple(unionTul);
                //std::cout << unionTul;
                addedTuples.insert(unionTul);
            }
        }
    }

    bool empty() {
        if (tuples.empty()) {
            return true;
        }
        return false;
    }

    std::string addedToString()  {
        std::stringstream ss;
        for (Tuple tul : addedTuples) {
            for (size_t i = 0; i < attributes->size(); ++i) {
                if (i == attributes->size() - 1) {
                    ss << " " << attributes->at(i) << "=" << tul.at(i) << std::endl;
                }
                else {
                    ss << " " << attributes->at(i) << "=" << tul.at(i) << ", ";
                }
            }
        }
        return ss.str();
    }

    std::string toString() const {
        std::stringstream ss;
        for (Tuple tul : tuples) {
            for (size_t i = 0; i < attributes->size(); ++i) {
                if (i == attributes->size() - 1) {
                    ss << " " << attributes->at(i) << "=" << tul.at(i) << std::endl;
                }
                else {
                    ss << " " << attributes->at(i) << "=" << tul.at(i) << ", ";
                }
            }
        }
        return ss.str();
    }

    friend std::ostream& operator<<(std::ostream& os,  const Relation &rel)
    {
        return os << rel.toString();
    }
};

#endif //CS236COOLPROJECT_RELATION_H
