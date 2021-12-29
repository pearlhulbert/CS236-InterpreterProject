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
    TokenType tokeType;
    std::string tokenDescription;
    int tokenLine;

public:
    Token(): tokeType(TokenType::UNDEFINED), tokenDescription(""), tokenLine(0) {}
    Token(TokenType type, std::string description, int line) {
        tokeType = type;
        tokenDescription = description;
        tokenLine = line;
    }
    ~Token() {}

    int GetLine() const {
        return tokenLine;
    }

    TokenType getType() const {
        return tokeType;
    }

    std::string getDescription() const {
        return tokenDescription;
    }

    friend std::ostream& operator<<(std::ostream& os, const Token& token)
    {
        os << token.toString();
        return os;
    }

    std::string TypeToString() const {
       if (tokeType == TokenType::COLON) {
           return "COLON";
       }
       else if (tokeType == TokenType::COLON_DASH) {
            return "COLON_DASH";
        }
       else if (tokeType == TokenType::EOFILE) {
           return "EOF";
       }
       else if (tokeType == TokenType::UNDEFINED) {
           return "UNDEFINED";
       }
       else if (tokeType == TokenType::PERIOD) {
           return "PERIOD";
       }
       else if (tokeType == TokenType::COMMA) {
           return "COMMA";
       }
       else if (tokeType == TokenType::Q_MARK) {
           return "Q_MARK";
       }
       else if (tokeType == TokenType::RIGHT_PAREN) {
           return "RIGHT_PAREN";
       }
       else if (tokeType == TokenType::LEFT_PAREN) {
           return "LEFT_PAREN";
       }
       else if (tokeType == TokenType::MULTIPLY) {
           return "MULTIPLY";
       }
       else if (tokeType == TokenType::ADD) {
           return "ADD";
       }
       else if (tokeType == TokenType::SCHEMES) {
           return "SCHEMES";
       }
       else if (tokeType == TokenType::FACTS) {
           return "FACTS";
       }
       else if (tokeType == TokenType::RULES) {
           return "RULES";
       }
       else if (tokeType == TokenType::QUERIES) {
           return "QUERIES";
       }
       else if (tokeType == TokenType::ID) {
           return "ID";
       }
       else if (tokeType == TokenType::STRING) {
           return "STRING";
       }
       else if (tokeType == TokenType::COMMENT) {
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
