//
// Created by pearlhulbert on 9/9/21.
//

#ifndef CS236COOLPROJECT_TOKEN_H
#define CS236COOLPROJECT_TOKEN_H
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

    int GetLine() const {
        return tokenLine;
    }

    friend std::ostream& operator<<(std::ostream& os, const Token& token)
    {
        os << token.toString();
        return os;
    }

    std::string TypeToString() const {
       if (tokenType == TokenType::COLON) {
           return "COLON";
       }
       else if (tokenType == TokenType::COLON_DASH) {
            return "COLON_DASH";
        }
       else if (tokenType == TokenType::EOFILE) {
           return "EOF";
       }
       else if (tokenType == TokenType::UNDEFINED) {
           return "UNDEFINED";
       }
       else if (tokenType == TokenType::PERIOD) {
           return "PERIOD";
       }
       else if (tokenType == TokenType::COMMA) {
           return "COMMA";
       }
       else if (tokenType == TokenType::Q_MARK) {
           return "Q_MARK";
       }
       else if (tokenType == TokenType::RIGHT_PAREN) {
           return "RIGHT_PAREN";
       }
       else if (tokenType == TokenType::LEFT_PAREN) {
           return "LEFT_PAREN";
       }
       else if (tokenType == TokenType::MULTIPLY) {
           return "MULTIPLY";
       }
       else if (tokenType == TokenType::ADD) {
           return "ADD";
       }
       else if (tokenType == TokenType::SCHEMES) {
           return "SCHEMES";
       }
       else if (tokenType == TokenType::FACTS) {
           return "FACTS";
       }
       else if (tokenType == TokenType::RULES) {
           return "RULES";
       }
       else if (tokenType == TokenType::QUERIES) {
           return "QUERIES";
       }
       else if (tokenType == TokenType::ID) {
           return "ID";
       }
       else if (tokenType == TokenType::STRING) {
           return "STRING";
       }
       else if (tokenType == TokenType::COMMENT) {
           return "COMMENT";
       }
       else {
           return "";
       }
    }

    std::string toString() const
    {
        std::stringstream ss;
        ss << "(" << TypeToString() << ",\"" << tokenDescription << "\"," << tokenLine << ")" << std::endl;
        std::string returnString = ss.str();
        return returnString;
    }

};
#endif //CS236COOLPROJECT_TOKEN_H
