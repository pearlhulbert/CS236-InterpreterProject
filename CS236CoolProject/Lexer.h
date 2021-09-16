//
// Created by pearlhulbert on 9/9/21.
//

#ifndef CS236COOLPROJECT_LEXER_H
#define CS236COOLPROJECT_LEXER_H
#include <vector>
#include <sstream>
#include <iostream>
#include "Automaton.h"
#include "Token.h"
#include "ColonAutomaton.h"
#include "ColonDashAutomaton.h"
#include "CommaAutomaton.h"
#include "PeriodAutomaton.h"
#include "QuestionMarkAutomaton.h"
#include "LeftParenAutomaton.h"
#include "RightParenAutomaton.h"
#include "MultiplyAutomaton.h"
#include "AddAutomaton.h"
#include "Schemes.h"
#include "FactsAutomaton.h"
#include "RulesAutomaton.h"
#include "Queries.h"
#include "IDAutomaton.h"
#include "StringAutomaton.h"
#include "LineCommentAutomaton.h"
#include "BlockComment.h"
//#include "UndefinedAutomaton.h"

class Lexer
{
private:
    std::vector<Automaton*> automata;
    std::vector<Token*> tokens;


    void CreateAutomata() {
        automata.push_back(new ColonAutomaton());
        automata.push_back(new ColonDashAutomaton());
        automata.push_back(new CommaAutomaton());
        automata.push_back(new PeriodAutomaton());
        automata.push_back(new QuestionMarkAutomaton());
        automata.push_back(new LeftParenAutomaton());
        automata.push_back(new RightParenAutomaton());
        automata.push_back(new MultiplyAutomaton());
        automata.push_back(new AddAutomaton());
        automata.push_back(new Schemes());
        automata.push_back(new FactsAutomaton());
        automata.push_back(new RulesAutomaton());
        automata.push_back(new Queries());
        automata.push_back(new IDAutomaton());
        automata.push_back(new StringAutomaton());
        automata.push_back(new LineCommentAutomaton());
        automata.push_back(new BlockComment());
        //automata.push_back(new UndefinedAutomaton());
    }

    // TODO: add any other private methods here (if needed)

public:
    // TODO: add other public methods here

    Lexer() {
        CreateAutomata();
    }

    ~Lexer() {
        for (unsigned int i = 0; i < automata.size(); ++i) {
            delete automata.at(i);
        }
        automata.clear();

        for (unsigned int i = 0; i < tokens.size(); ++i) {
            delete tokens.at(i);
        }
        tokens.clear();
    }

    void Run(std::string& input) {
        int lineNumber = 1;
        Token* newToken = NULL;

        while (input.size() > 0) {
            int maxRead = 0;
            int inputRead = 0;
            Automaton* maxAutomaton = automata.at(0);

            //deal with whitespace
            if (isspace(input.at(inputRead))) {
                if (input.at(inputRead) == '\n') {
                    ++lineNumber;
                }
                input.erase(inputRead,1);
                continue;
            }

            //parallel (all at once with same input)
            for (unsigned int i = 0; i < automata.size(); ++i) {
                inputRead = automata.at(i)->Start(input);
                if (inputRead > maxRead) {
                    maxRead = inputRead;
                    maxAutomaton = automata.at(i);
                }
            }

            //max, ensures max accepted is chosen
            if (maxRead > 0) {
                if (!maxAutomaton->isValidToken()) {
                    maxAutomaton->SetType(TokenType::UNDEFINED);
                }
                std::string createTokenString = input;
                createTokenString.resize(maxRead);
                newToken = maxAutomaton->CreateToken(createTokenString, lineNumber);
                lineNumber = lineNumber + maxAutomaton->NewLinesRead();
                tokens.push_back(newToken);
            }

            //no accepted input
            else {
                maxRead = 1;
                char singleCharDescrip = input.at(0);
                std::string singleCharString;
                singleCharString = singleCharDescrip;
                newToken = new Token(TokenType::UNDEFINED, singleCharString, lineNumber);
                tokens.push_back(newToken);
            }
            input.erase(0,maxRead);
        }
        newToken = new Token(TokenType::EOFILE, "", lineNumber);
        tokens.push_back(newToken);
    }

    void EndOfFile() {
        int line = tokens.at(tokens.size() - 1)->GetLine();
        //line = line + 1;
        Token* end = new Token(TokenType::EOFILE, "", line);
        tokens.push_back(end);
    }


    friend std::ostream& operator<<(std::ostream& os, const Lexer& lex)
    {
        os << lex.toString();
        return os;
    }

    std::string toString() const
    {
        std::stringstream ss;
        for (unsigned int i = 0; i < tokens.size(); ++i) {
            ss << tokens.at(i)->toString();
        }
        ss << "Total Tokens = " << tokens.size() << std::endl;
        std::string returnString;
        returnString = ss.str();
        return returnString;
    }

};
#endif //CS236COOLPROJECT_LEXER_H
