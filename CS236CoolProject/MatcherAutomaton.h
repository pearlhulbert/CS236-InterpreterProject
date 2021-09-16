//
// Created by pearlhulbert on 9/9/21.
//

#ifndef CS236COOLPROJECT_MATCHERAUTOMATON_H
#define CS236COOLPROJECT_MATCHERAUTOMATON_H
#include "Automaton.h"
#include<iostream>

const int  NUM_MATCHERS = 13;
class MatcherAutomaton : public Automaton {
private:
    std::string matchString;
    TokenType typeMatch = TokenType::UNDEFINED;

public:
    MatcherAutomaton() : Automaton(typeMatch) {};
    //MatcherAutomaton(std::string matchString, TokenType tokenType);


    void S0(const std::string &input) {
        bool match = true;
        inputRead = 0;
        for (unsigned int i = 0; i < NUM_MATCHERS; ++i) {
            matchString = matches[i];
            for (unsigned int i = 0; i < matchString.size() && match; ++i) {
                if (input[i] != matchString[i]) {
                    match = false;
                }
            }
        }
        if (match) {
            std::cout << matchString << std::endl;
            inputRead = matchString.size();
            typeMatch = FindType(matchString);
        }
        else {
            Serr();
        }
    }

    TokenType FindType(std::string mString) {
        if (mString == ":") {
            return TokenType::COLON;
        }
        else if (mString == ":-") {
            return TokenType::COLON_DASH;
        }
        else if (mString == ",") {
            return TokenType::COMMA;
        }
        else if (mString == ".") {
            return TokenType::PERIOD;
        }
        else if (mString == "?") {
            return TokenType::Q_MARK;
        }
        else if (mString == "(") {
            return TokenType::LEFT_PAREN;
        }
        else if (mString == ")") {
            return TokenType::RIGHT_PAREN;
        }
        else if (mString == "*") {
            return TokenType::MULTIPLY;
        }
        else if (mString == "+") {
            return TokenType::ADD;
        }
        else if (mString == "Schemes") {
            return TokenType::SCHEMES;
        }
        else if (mString == "Facts") {
            return TokenType::FACTS;
        }
        else if (mString == "Rules") {
            return TokenType::RULES;
        }
        else if (mString == "Queries") {
            return TokenType::QUERIES;
        }
        else {
            return TokenType::UNDEFINED;
        }
    }

};
#endif //CS236COOLPROJECT_MATCHERAUTOMATON_H
