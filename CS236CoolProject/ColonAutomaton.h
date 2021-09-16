//
// Created by pearlhulbert on 9/10/21.
//

#ifndef CS236COOLPROJECT_COLONAUTOMATON_H
#define CS236COOLPROJECT_COLONAUTOMATON_H
#include "Automaton.h"

class ColonAutomaton : public Automaton
{
private:
    const std::string matchString = ":";

public:
    ColonAutomaton() : Automaton(TokenType::COLON) {}  // Call the base constructor

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
            ++newLines;
        }
        else {
            Serr();
        }
    }

    /*friend std::ostream& operator<<(std::ostream& os, const Automaton& autom)
    {
        os << autom.toString();
        return os;
    }

    std::string toString() const
    {
        std::stringstream ss;

        std::string returnString = ss.str();
        returnString.pop_back();
        return returnString;
    }*/

};

#endif //CS236COOLPROJECT_COLONAUTOMATON_H
