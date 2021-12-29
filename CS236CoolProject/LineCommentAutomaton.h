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
    int currState = 0;


public:
    LineCommentAutomaton() : Automaton(TokenType::COMMENT) {}  // Call the base constructor

    void S0(const std::string& input) {
        validToken = true;
        commentString = "";
        while (validToken && index < input.size()) {
            switch(currState) {
                case 0:
                    if (input.at(index) == '#') {
                        currState = 1;
                        commentString += input.at(index);
                    }
                    else {
                        currState = 7;
                    }
                    break;
                case 1:
                    if (input.at(index) == '|') {
                        currState = 7;
                    }
                    else {
                        commentString += input.at(index);
                        currState = 2;
                    }
                    break;
                case 2:
                    if (input.at(index) == '\n') {
                        currState = 8;
                    }
                    else {
                        currState = 2;
                        commentString += input.at(index);
                    }
                    break;
                case 7:
                    validToken = false;
                    currState = 0;
                    Serr();
                    return;
                case 8:
                    inputRead = commentString.size();
                    currState = 0;
                    return;
            }
            ++index;
        }
        if (currState == 8) {
            inputRead = commentString.size();
        }
    }
};
#endif //CS236COOLPROJECT_LINECOMMENTAUTOMATON_H
