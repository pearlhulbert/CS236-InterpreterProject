//
// Created by pearlhulbert on 9/10/21.
//

#ifndef CS236COOLPROJECT_IDAUTOMATON_H
#define CS236COOLPROJECT_IDAUTOMATON_H
#include "Automaton.h"

class IDAutomaton : public Automaton
{
private:
    std::string idString = "";
public:
    IDAutomaton() : Automaton(TokenType::ID) {}  // Call the base constructor

    void S0(const std::string& input) {
        if (!isalpha(input.front())) {
            Serr();
            return;
        }
        idString = "";
        for (unsigned int i = 0; i < input.size(); ++i) {
            if (isspace(input.at(i)) || !isalnum(input.at(i))) {
                break;
            }
            idString += input.at(i);
        }
        if (idString != "") {
            inputRead = idString.size();
        }
        else {
            Serr();
        }
    }
};
#endif //CS236COOLPROJECT_IDAUTOMATON_H
