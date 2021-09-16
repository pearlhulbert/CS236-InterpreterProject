//
// Created by pearlhulbert on 9/11/21.
//

#ifndef CS236COOLPROJECT_UNDEFINEDAUTOMATON_H
#define CS236COOLPROJECT_UNDEFINEDAUTOMATON_H
#include "Automaton.h"
#include "StringAutomaton.h"

class UndefinedAutomaton : public StringAutomaton
{
private:
    int lineNumber = 0;
public:
    UndefinedAutomaton() : Automaton(TokenType::UNDEFINED) {}// Call the base constructor
    //UndefinedAutomaton(int lineNum) : Automaton(TokenType::UNDEFINED), lineNumber(lineNum) {}

    void S0(const std::string& input) {}
#endif //CS236COOLPROJECT_UNDEFINEDAUTOMATON_H
