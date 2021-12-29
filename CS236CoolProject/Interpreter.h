//
// Created by pearlhulbert on 10/23/21.
//

#ifndef CS236COOLPROJECT_INTERPRETER_H
#define CS236COOLPROJECT_INTERPRETER_H
#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include "Database.h"
#include "DatalogProgram.h"
#include "Relation.h"
#include "Graph.h"

class Interpreter {
private:
    DataLogProgram* datalog;
    Database dBase;
public:
    Interpreter() {}
    Interpreter(DataLogProgram* data) {
        datalog = data;
    }
    ~Interpreter() {
    }


    void interpret() {
        std::vector<Predicate*> schemes = datalog->getSchemes();
        std::vector<Predicate*> facts = datalog->getFacts();
        std::vector<Predicate*> queries = datalog->getQueries();
        std::vector<Rule*> rules = datalog->getRules();
        for (Predicate* schemePred : schemes) {
            std::string relationName = schemePred->getName();
            std::vector<std::string> relationHeaderVector = schemePred->getBody();
            Header* relationHeader = new Header(relationHeaderVector);
            Relation* currRelation = new Relation(relationName, relationHeader);
            if (schemePred == schemes.front()) {
                dBase = Database(relationName, currRelation);
            }
            else {
                dBase.insert(relationName, currRelation);
            }
        }
        for (Predicate* factsPred : facts) {
            std::string relName = factsPred->getName();
            std::vector<std::string> relationTupleVector = factsPred->getBody();
            Tuple relationTuple = Tuple(relationTupleVector);
            Relation* nextRelation;
            nextRelation = dBase.matchRelation(relName);
            nextRelation->addTuple(relationTuple);
        }
        int currIndex = 0;
        for (Rule* rule : rules) {
            rule->setNumId(currIndex);
            ++currIndex;
        }
        Graph ruleDependencies = Graph(rules);
        ruleDependencies.findDependencies();
        std::cout << "Dependency Graph" << std::endl << ruleDependencies.toString() << std::endl;
        Graph reverseRuleDependecies = ruleDependencies.reverseGraph();
        //std::cout << "Reverse" << std::endl << reverseRuleDependecies.toString() << std::endl;
        reverseRuleDependecies.depthFirstForestPostOrder();
        std::vector<int> postOrder = reverseRuleDependecies.getPostOrder();
        std::reverse(postOrder.begin(), postOrder.end());
        ruleDependencies.setPostOrder(postOrder);
        ruleDependencies.depthFirstForestSCC();
        std::vector<std::set<int>> SCCs = ruleDependencies.getSCCs();
        std::vector<std::vector<Rule*>> evalRules;
        std::vector<Rule*> evalVec;
        for (std::set<int> SCC : SCCs) {
            for (int element : SCC) {
                if (element == rules.at(element)->getNumId()) {
                    evalVec.push_back(rules.at(element));
                }
            }
            evalRules.push_back(evalVec);
            evalVec.clear();
        }
        std::cout << "Rule Evaluation" << std::endl;
        for (size_t i = 0; i < evalRules.size(); ++i) {
            std::vector<Rule*> evalRuleVec = evalRules.at(i);
            std:: cout << "SCC: " << printSCC(evalRuleVec) << std::endl;
            if (evalRuleVec.size() == 1 && !ruleDependencies.checkSelfLoop(evalRuleVec.at(0)->getNumId())) {
                evaluateRule(evalRuleVec.at(0));
                std::cout << "1 passes: " << printSCC(evalRuleVec) << std::endl;
            }
            else {
                fixedPointAlgorithm(evalRuleVec);
            }
        }
        std::cout << std::endl << "Query Evaluation" << std::endl;
        for (Predicate* queryPred : queries) {
            std::cout << queryPred->toString() << "?";
            Relation* newRelation = evaluatePredicate(*queryPred);
            if (!newRelation->empty()) {
                std::cout << " Yes(" << newRelation->size() << ")\n" << newRelation->toString();
            }
            else {
                std::cout << " No" << std::endl;
            }
        }
    }

    Relation* evaluatePredicate(const Predicate &p) {
        std::map<std::string, int> selectMapT2;
        std::vector<int> indices;
        std::vector<std::string> values;
        Relation* currRelation = dBase.matchRelation(p.getName());
        std::vector<std::string> parameters;
        parameters = p.getBody();
        for (size_t i = 0; i < parameters.size(); ++i) {
            if (parameters.at(i).front() == '\'') {
               currRelation = currRelation->selectType1(i, parameters.at(i));
            }
            else if (parameters.at(i) == selectMapT2.find(parameters.at(i))->first) {
                currRelation = currRelation->selectType2(i, selectMapT2.find(parameters.at(i))->second);
            }
            else {
                selectMapT2.insert(std::pair<std::string, int>(parameters.at(i), i));
                indices.push_back(i);
                values.push_back(parameters.at(i));
            }
        }
        currRelation = currRelation->project(indices);
        currRelation = currRelation->rename(values);
        return currRelation;
    }

    Relation* joinRules(std::vector<Relation*> ruleRelations, std::string name) {
        Relation* ruleRelation = ruleRelations.at(0);
        for (size_t i = 0; i < ruleRelations.size(); ++i) {
            if (i != ruleRelations.size() - 1) {
               ruleRelation = ruleRelation->naturalJoin(ruleRelations.at(i+1));
            }
            else if (ruleRelations.size() == 1) {
                ruleRelation->setTuples(ruleRelations.at(i)->getTuples());
            }
            else {
                break;
            }
        }
        ruleRelation->setName(name);
        return ruleRelation;
    }

    std::vector<int> getProjectIndices(Relation* currRel, Relation* ruleHead) {
        std::vector<std::string> currRelAttributes = currRel->getHeader()->getAttributes();
        std::vector<std::string> ruleHeadAttributes = ruleHead->getHeader()->getAttributes();
        std::vector<int> keepColumns;
        for (size_t i = 0; i < ruleHeadAttributes.size(); ++i) {
            for (size_t j = 0; j < currRelAttributes.size(); ++j) {
                if (ruleHeadAttributes.at(i) == currRelAttributes.at(j)) {
                    keepColumns.push_back(j);
                }
            }
        }
        return keepColumns;
    }

    bool printAll(std::vector<Rule*> rules) {
        int fullRules = 0;
        for (Rule* rule : rules) {
            if (!rule->getPrintCondition()) {
                ++fullRules;
            }
        }
        if (fullRules > 0) {
            return true;
        }
        return false;
    }

    void fixedPointAlgorithm(std::vector<Rule*> rules) {
        int passNum = 1;
        int tuplesAdded = 0;
        Rule* lastRule = rules.at(rules.size()-1);
        Rule* currRule = rules.at(0);
        do {
            for (Rule* rule : rules) {
                currRule = rule;
                Predicate* ruleHead = rule->getHead();
                Relation* headRule = evaluatePredicate(*ruleHead);
                Relation* unionRelation = dBase.matchRelation(headRule->getName());
                std::vector<Relation*> evalRelations;
                std::vector<Predicate*> ruleBody = rule->getRuleBody();
                for (Predicate* ruleBod: ruleBody) {
                    Relation* newRelation = evaluatePredicate(*ruleBod);
                    evalRelations.push_back(newRelation);
                }
                Relation* currRelation = joinRules(evalRelations, headRule->getName());
                std::vector<int> keepColumns = getProjectIndices(currRelation, headRule);
                currRelation = currRelation->project(keepColumns);
                std::vector<std::string> newAttributes = dBase.matchRelation(headRule->getName())->getHeader()->getAttributes();
                currRelation = currRelation->rename(newAttributes);
                unionRelation->makeUnion(currRelation);
                tuplesAdded = unionRelation->newTupleNum();
                if (tuplesAdded == 0) {
                    if (currRule == lastRule) {
                        std::cout << rule->toString() << "." << std::endl;
                        rule->setPrintCondition(true);
                        if (!printAll(rules)) {
                            std::cout << passNum << " passes: " << printSCC(rules) << std::endl;
                        }
                        break;
                    }
                    else {
                        std::cout << rule->toString() << "." << std::endl;
                        //std::cout << passNum << " passes: " << printSCC(rules) << std::endl;
                        rule->setPrintCondition(true);
                        continue;
                    }
                }
                else {
                    std::cout << rule->toString() << ".";
                    rule->setPrintCondition(false);
                    std::cout << std::endl << unionRelation->addedToString();
                }
                dBase.setDBRelation(unionRelation->getName(), unionRelation);
            }
            if (tuplesAdded != 0) {
                ++passNum;
            }
            else if (printAll(rules)) {
                for (Rule *rule: rules) {
                    if (rule == rules.at(0)) {
                        std::cout << rule->toString() << ".";
                    }
                    else {
                        std::cout << std::endl << rule->toString() << ".";
                    }
                }
                ++passNum;
                std::cout << std::endl << passNum << " passes: " << printSCC(rules) << std::endl;
            }
        }
        while (tuplesAdded != 0 || currRule != lastRule);
    }

    void evaluateRule(Rule* evalRule) {
        Predicate* ruleHead = evalRule->getHead();
        Relation* headRule = evaluatePredicate(*ruleHead);
        Relation* unionRelation = dBase.matchRelation(headRule->getName());
        std::vector<Relation*> evalRelations;
        std::vector<Predicate*> ruleBody = evalRule->getRuleBody();
        for (Predicate* ruleBod: ruleBody) {
            Relation* newRelation = evaluatePredicate(*ruleBod);
            evalRelations.push_back(newRelation);
        }
        Relation* currRelation = joinRules(evalRelations, headRule->getName());
        std::vector<int> keepColumns = getProjectIndices(currRelation, headRule);
        currRelation = currRelation->project(keepColumns);
        std::vector<std::string> newAttributes = dBase.matchRelation(headRule->getName())->getHeader()->getAttributes();
        currRelation = currRelation->rename(newAttributes);
        unionRelation->makeUnion(currRelation);
        std::cout << evalRule->toString() << ".";
        std::cout << std::endl << unionRelation->addedToString();
    }

    std::string printSCC(std::vector<Rule*> evalRules) {
        std::stringstream ss;
        for (Rule* rule: evalRules) {
            if (rule != *(evalRules.end() - 1)) {
                ss << "R" << rule->getNumId() << ",";
            }
            else {
                ss << "R" << rule->getNumId();
            }
        }
        return ss.str();
    }
    

};

#endif //CS236COOLPROJECT_INTERPRETER_H
