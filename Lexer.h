//
// Created by pearlhulbert on 9/8/21.
//

#ifndef CS236MAINPROJECT_LEXER_H
#define CS236MAINPROJECT_LEXER_H
#include <vector>
#include "Automaton.h"
#include "Token.h"
#include "MatcherAutomaton.h"

class Lexer
{
private:
    std::vector<Automaton*> automata;
    std::vector<Token*> tokens;


    void CreateAutomata() {
        automata.push_back(new MatcherAutomaton());
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
            Automaton* maxAutomaton = automata.at(0);

            //deal with whitespace
            if (isspace(input.at(lineNumber))) {
                continue;
            }

            //parallel (all at once with same input
            for (unsigned int i = 0; i < automata.size(); ++i) {
                int inRead = automata.at(lineNumber)->Start(input);
                if (inRead > maxRead) {
                    maxRead = inRead;
                    maxAutomaton = automata.at(i);
                }
            }

            //max, ensures max accepted is chosen
            if (maxRead > 0) {
                newToken = maxAutomaton->CreateToken(input, lineNumber);
                lineNumber = lineNumber + maxAutomaton->NewLinesRead();
                tokens.push_back(newToken);
            }

                //no accepted input
            else {
                maxRead = 1;
                newToken = new Token(TokenType::UNDEFINED, input, lineNumber);
                tokens.push_back(newToken);
            }

            input.resize(input.size()-maxRead);
        }
        newToken = new Token(TokenType::EOFILE, "", lineNumber);
        tokens.push_back(newToken);

    }

};
#endif //CS236MAINPROJECT_LEXER_H
