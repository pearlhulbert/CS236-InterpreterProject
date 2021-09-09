//
// Created by pearlhulbert on 9/8/21.
//

#ifndef CS236MAINPROJECT_TOKEN_H
#define CS236MAINPROJECT_TOKEN_H
#include <string>

enum class TokenType {
    COLON,
    COLON_DASH,
    COMMA,
    PERIOD,
    Q_MARK,
    LEFT_PAREN,
    RIGHT_PAREN,
    MULTIPLY,
    ADD,
    SCHEMES,
    FACTS,
    RULES,
    QUERIES,
    ID,
    STRING,
    COMMENT,
    EOFILE,
    UNDEFINED
};

class Token
{
private:
    TokenType tokenType;
    std::string tokenDescription;
    int tokenLine;

public:
    Token(): tokenType(TokenType::UNDEFINED), tokenDescription(""), tokenLine(0) {}
    Token(TokenType type, std::string description, int line) {
        tokenType = type;
        tokenDescription = description;
        tokenLine = line;
    }
    ~Token() {}

    TokenType GetType() const {
        return tokenType;
    }

    void SetType(TokenType token) {
        tokenType = token;
    }


};

#endif //CS236MAINPROJECT_TOKEN_H
