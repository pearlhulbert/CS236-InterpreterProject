//
// Created by pearlhulbert on 9/10/21.
//

#ifndef CS236COOLPROJECT_RULESAUTOMATON_H
#define CS236COOLPROJECT_RULESAUTOMATON_H
#include "Automaton.h"

class RulesAutomaton : public Automaton
{
private:
    const std::string matchString = "Rules";

public:
    RulesAutomaton() : Automaton(TokenType::RULES) {}  // Call the base constructor

    void S0(const std::string& input) {
        bool match = true;
        inputRead = 0;
        for (unsigned int i = 0; i < matchString.size() && match; ++i) {
            if (input[i] != matchString[i]) {
                match = false;
            }
        }
        if (match) {
            inputRead = matchString.size();
        }
        else {
            Serr();
        }
    }
};

#endif //CS236COOLPROJECT_RULESAUTOMATON_H
