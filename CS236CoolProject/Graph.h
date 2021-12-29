//
// Created by pearlhulbert on 12/6/21.
//

#ifndef CS236COOLPROJECT_GRAPH_H
#define CS236COOLPROJECT_GRAPH_H

#include <string>
#include <map>
#include <set>
#include <vector>
#include <stack>
#include "Rule.h"

class Graph {
private:
    std::map<int, std::set<int>> dependGraph;
    std::map<int, bool> visited;
    std::vector<int> postOrder;
    std::vector<std::set<int>> SCCs;
    std::vector<Rule*> dependRules;
    std::vector<int> dfsTree;
    std::vector<std::vector<int>> dfsForest;
    std::set<int> SCCSet;
public:
    Graph() {}
    ~Graph() {}
    Graph(std::vector<Rule*> rules) {
        dependRules = rules;
        std::pair<int, bool> newVisitPair;
        std::pair<int, std::set<int>> newRulePair;
        std::set<int> initializeList;
        int currIndex = 0;
        for (Rule* rule : dependRules) {
            currIndex = rule->getNumId();
            newVisitPair = std::make_pair(currIndex, false);
            visited.insert(newVisitPair);
            newRulePair = std::make_pair(currIndex, initializeList);
            dependGraph.insert(newRulePair);
        }
    }

    std::vector<std::set<int>> getSCCs() const {
        return SCCs;
    }

    std::vector<int> getPostOrder() const {
        return postOrder;
    }

    void setPostOrder(std::vector<int> pOrder) {
        postOrder = pOrder;
    }

    void findDependencies() {
        for (Rule* headRule : dependRules) {
            std::string headName = headRule->getHead()->getName();
            for (Rule* rule : dependRules) {
                for (Predicate* rulePred : rule->getRuleBody()) {
                    if (rulePred->getName() == headName) {
                        addToList(rule->getNumId(), headRule->getNumId());
                    }
                }
            }
        }
    }

    bool checkSelfLoop(int vertex) {
        for (int element : dependGraph.at(vertex)) {
            if (element == vertex) {
                return true;
            }
        }
        return false;
    }

    void addToList(int currVertex, int nextVertex) {
        std::set<int> listSet;
        for (std::pair<int, std::set<int>> listPair : dependGraph) {
            if (listPair.first == currVertex) {
                listSet = listPair.second;
                listSet.insert(nextVertex);
            }
        }
        dependGraph.at(currVertex) = listSet;
    }

    void markVisited(int currVertex) {
        visited.at(currVertex) = true;
    }

    Graph reverseGraph() {
        Graph revGraph = Graph(dependRules);
        for (std::pair<int, std::set<int>> reversePair : dependGraph) {
            for (std::pair<int, std::set<int>> reversePairInner : dependGraph) {
                for (int element : reversePairInner.second) {
                    if (element == reversePair.first) {
                        revGraph.addToList(reversePair.first, reversePairInner.first);
                    }
                }
            }
        }
        return revGraph;
    }

    std::vector<int> depthFirstSearchPostOrder(int vertex) {
        markVisited(vertex);
        dfsTree.clear();
        std::set<int> currSet = dependGraph.at(vertex);
        for (int element : currSet) {
            if (!visited.at(element)) {
                depthFirstSearchPostOrder(element);
            }
        }
        postOrder.push_back(vertex);
        dfsTree.push_back(vertex);
        return dfsTree;
    }

    std::set<int> depthFirstSearchSCC(int vertex) {
        markVisited(vertex);
        std::set<int> currSet = dependGraph.at(vertex);
        for (int element : currSet) {
            if (!visited.at(element)) {
                depthFirstSearchSCC(element);
            }
        }
        SCCSet.insert(vertex);
        return SCCSet;
    }


    std::vector<std::vector<int>> depthFirstForestPostOrder() {
        if (!dfsForest.empty()) {
            dfsForest.clear();
        }
        std::vector<int> newTree;
        for (std::pair<int, std::set<int>> searchPair : dependGraph) {
            if(!visited.at(searchPair.first)) {
                newTree = depthFirstSearchPostOrder(searchPair.first);
            }
        }
        dfsForest.push_back(newTree);
        dfsTree.clear();
        return dfsForest;
    }

    std::vector<std::set<int>> depthFirstForestSCC() {
        if (!SCCs.empty()) {
            SCCs.clear();
        }
        std::set<int> newSet;
        for (int postNum : postOrder) {
            if(!visited.at(postNum)) {
                newSet = depthFirstSearchSCC(postNum);
            }
            if(!newSet.empty()) {
                SCCs.push_back(newSet);
                newSet.clear();
            }
            SCCSet.clear();
        }
        return SCCs;
    }

    /*std::set<int> getAdjList(int vertex) const {
        for (std::pair<int, set<int>> listPair : dependGraph) {
            if (listPair.first == vertex) {
                return listPair.second;
            }
        }
    }*/

    std::string toString() const {
        std::stringstream ss;
        for (std::pair<int, std::set<int>> printPair : dependGraph) {
            ss << "R" << printPair.first << ":";
            for(int element : printPair.second) {
                if (element != *printPair.second.rbegin() && printPair.second.size() != 1) {
                    ss << "R" << element << ",";
                }
                else {
                    ss << "R" << element;
                }
            }
            ss << std::endl;
        }
        return ss.str();
    }
};


#endif //CS236COOLPROJECT_GRAPH_H
