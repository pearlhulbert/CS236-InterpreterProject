//
// Created by pearlhulbert on 9/9/21.
//

#ifndef CS236COOLPROJECT_AUTOMATON_H
#define CS236COOLPROJECT_AUTOMATON_H
#include "Token.h"

class Automaton
{
protected:
    int inputRead = 0;
    int newLines = 0;
    unsigned int index = 0;
    bool validToken;
    TokenType type;

public:
    // Default constructor -- since we have a constructor that takes a parameter,
    //   the compiler will autogenerate a default constructor if not explicit.
    Automaton() : Automaton(TokenType::UNDEFINED) {}

    Automaton(TokenType type) { this->type = type; }

   virtual ~Automaton() {}

    // Start the automaton and return the number of characters read
    //   read == 0 indicates the input was rejected
    //   read  > 0 indicates the input was accepted
    int Start(const std::string& input) {
        newLines = 0;
        inputRead = 0;
        index = 0;
        validToken = true;
        S0(input);
        return inputRead;
    }

    TokenType GetType() const {
        return type;
    }

    void SetType(TokenType tokenType) {
        type = tokenType;
    }

    bool isValidToken() const{
        return validToken;
    }

    // Every subclass must define this method
    virtual void S0(const std::string& input) = 0;

    void Serr() {
        // Indicate the input was rejected
        inputRead = 0;
    }

    virtual Token* CreateToken(std::string input, int lineNumber) { return new Token(type, input, lineNumber); }

    int NewLinesRead() const { return newLines; }

};

#endif //CS236COOLPROJECT_AUTOMATON_H
