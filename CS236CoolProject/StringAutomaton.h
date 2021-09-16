//
// Created by pearlhulbert on 9/10/21.
//

#ifndef CS236COOLPROJECT_STRINGAUTOMATON_H
#define CS236COOLPROJECT_STRINGAUTOMATON_H
#include "Automaton.h"

class StringAutomaton : public Automaton
{
private:
    std::string stringString = "";
    int currState = 0;
    /* state 0 = start
     * state 1 = first apostrophe
     * state 2 = any char not apostrophe
     * state 3 = apostrophe
     * state 4 = apostrophe with last char being apostrophe ('')
     * state 7 = error/exit no starting apostrophe, no token
     * state 8 = no ending apostrophe, undefined string
     * state 9 = exit with token
     * */


    void S1(const std::string& input) {
        if (input.at(index) == '\'') {
            currState = 3;
        }
        else {
            if (input.at(index) == '\n') {
                ++newLines;
            }
            currState = 2;
        }
        stringString += input.at(index);
    }

    void S3(const std::string& input) {
        if(input.at(index) == '\'') {
            currState = 4;
            stringString += input.at(index);
        }
        else {
            /*if (input.at(index) == '\n') {
                ++newLines;
            }*/
            currState = 9;
        }
    }

    void S4(const std::string& input) {
        if (input.at(index) == '\'') {
            currState = 3;
        }
        else {
            if (input.at(index) == '\n') {
                ++newLines;
            }
            currState = 2;
        }
        stringString += input.at(index);
    }



public:
    StringAutomaton() : Automaton(TokenType::STRING) {}  // Call the base constructor

    void S0(const std::string& input) {
        validToken = false;
        stringString = "";
        while(!validToken && index < input.size()) {
            switch (currState) {
                case 0:
                    if (input.at(index) != '\'') {
                        currState = 7;
                    }
                    else {
                        stringString += input.at(index);
                        currState = 1;
                    }
                    break;
                case 1:
                    S1(input);
                    break;
                case 2:
                    S1(input);
                    break;
                case 3:
                    S3(input);
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
                    inputRead = stringString.size();
                    return;
                case 9:
                    validToken = true;
                    currState = 0;
                    inputRead = stringString.size();
                    return;
            }
            ++index;
        }
        if (currState == 9) {
            validToken = true;
            inputRead = stringString.size();
        }
        if (!validToken) {
            inputRead = stringString.size();
        }
    }
};
#endif //CS236COOLPROJECT_STRINGAUTOMATON_H
