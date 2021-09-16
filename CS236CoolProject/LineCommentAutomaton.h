//
// Created by pearlhulbert on 9/11/21.
//

#ifndef CS236COOLPROJECT_LINECOMMENTAUTOMATON_H
#define CS236COOLPROJECT_LINECOMMENTAUTOMATON_H
#include "Automaton.h"

class LineCommentAutomaton : public Automaton
{
private:
    std::string commentString = "";
public:
    LineCommentAutomaton() : Automaton(TokenType::COMMENT) {}  // Call the base constructor

    void S0(const std::string& input) {
        validToken = false;
        commentString = "";
        if (input.front() == '#' && input.at(1) != '|') {
            validToken = true;
            //Serr();
        }
        for (unsigned int i = 0; i < input.size(); ++i) {
            commentString += input.at(i);
            if (input.at(i) == '\n') {
                break;
            }
        }
        if (validToken) {
            commentString.pop_back();
            inputRead = commentString.size();
        }
        else {
            Serr();
        }
    }
};
#endif //CS236COOLPROJECT_LINECOMMENTAUTOMATON_H
