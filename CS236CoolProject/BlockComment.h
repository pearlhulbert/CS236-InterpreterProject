//
// Created by pearlhulbert on 9/11/21.
//

#ifndef CS236COOLPROJECT_BLOCKCOMMENT_H
#define CS236COOLPROJECT_BLOCKCOMMENT_H
#include "Automaton.h"
#include <iostream>

class BlockComment : public Automaton
{
private:
    std::string commentString = "";
    int currState = 0;
    /*
     * state 0 = start
     * state 1 = # found
     * state 2 = | found, valid token
     * state 3 = character not |
     * state 4 = # with last char being | (|#)
     * state 7 = # not found or | not found after #, invalid token so exit
     * state 8 = # not found after | so undefined
     * state 9 = valid token, exit
     */

    void S1(const std::string& input) {
        if (input.at(index) == '|') {
            currState = 2;
        }
        else {
            currState = 7;
        }
        commentString += input.at(index);
    }

    void S2(const std::string& input) {
        if (input.at(index) == '|') {
            currState = 4;
        }
        else {
            if (input.at(index) == '\n') {
                ++newLines;
            }
            currState = 3;
        }
        commentString += input.at(index);
    }

    void S4(const std::string& input) {
        if (input.at(index) == '#') {
            currState = 9;
        }
        else {
            currState = 3;
            commentString += input.at(index);
        }
    }

public:
    BlockComment() : Automaton(TokenType::COMMENT) {}  // Call the base constructor

    void S0(const std::string& input) {
        validToken = false;
        commentString = "";
        while (!validToken && index < input.size()) {
            switch(currState) {
                case 0:
                    if (input.at(index) != '#') {
                        currState = 7;
                    }
                    else {
                        commentString += input.at(index);
                        currState = 1;
                    }
                    break;
                case 1:
                    S1(input);
                    break;
                case 2:
                    S2(input);
                    break;
                case 3:
                    S2(input);
                    break;
                case 4:
                    S4(input);
                    break;
                case 7:
                    validToken = false;
                    currState = 0;
                    Serr();
                    return;
                case 8:
                    validToken = false;
                    currState = 0;
                    inputRead = commentString.size();
                    return;
                case 9:
                    validToken = true;
                    currState = 0;
                    inputRead = commentString.size();
                    return;
            }
            ++index;
        }
        if (currState == 9) {
            validToken = true;
            inputRead = commentString.size();
        }
        if (!validToken) {
            currState = 8;
            inputRead = commentString.size();
        }

    }
};

#endif //CS236COOLPROJECT_BLOCKCOMMENT_H
