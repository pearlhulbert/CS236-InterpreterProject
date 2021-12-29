//
// Created by pearlhulbert on 9/28/21.
//

#ifndef CS236COOLPROJECT_PARSER_H
#define CS236COOLPROJECT_PARSER_H
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include "Token.h"
#include "DatalogProgram.h"
#include "Predicate.h"
#include "Parameter.h"
#include "Rule.h"

class Parser {
private:
    int parseIndex = 0;
    bool isScheme = false;
    bool isRule = false;
    bool isQuery = false;
    std::string except = "";
    std::string currId = "";
    DataLogProgram* dLP = NULL;
    Predicate* predicate1 = NULL;
    Predicate* rulePred = NULL;
    Parameter* parameter1 = NULL;
    Rule* parseRule = NULL;
    std::set<std::string> parseDomain;
    std::vector<Predicate*> rulePreds;
    std::vector<Parameter*> params;
    std::vector<Predicate*> parseSchemes;
    std::vector<Predicate*> parseFacts;
    std::vector<Rule*> parseRules;
    std::vector<Predicate*> parseQueries;
    std::vector<Token*> inputStream;
    std::vector<TokenType> firstSchemes = {TokenType::ID, TokenType::LEFT_PAREN, TokenType::ID};
    std::vector<TokenType> firstFacts = {TokenType::ID, TokenType::LEFT_PAREN, TokenType::STRING};
    std::vector<TokenType> firstPredicates = {TokenType::ID, TokenType::LEFT_PAREN};
public:
    Parser() = default;
    ~Parser() {
        for (size_t i = 0; i < inputStream.size(); ++i) {
            delete inputStream.at(i);
        }
        inputStream.clear();
        for (size_t i = 0; i < params.size(); ++i) {
            delete params.at(i);
        }
        params.clear();
        for (size_t i = 0; i < rulePreds.size(); ++i) {
            delete rulePreds.at(i);
        }
        rulePreds.clear();
        for (size_t i = 0; i < parseSchemes.size(); ++i) {
            delete parseSchemes.at(i);
        }
        parseSchemes.clear();
        for (size_t i = 0; i < parseFacts.size(); ++i) {
            delete parseFacts.at(i);
        }
        parseFacts.clear();
        for (size_t i = 0; i < parseQueries.size(); ++i) {
            delete parseQueries.at(i);
        }
        parseQueries.clear();
        for (size_t i = 0; i < parseRules.size(); ++i) {
            delete parseRules.at(i);
        }
        parseRules.clear();
    }
    Parser(std::vector<Token*> inTokens) {
        inputStream = inTokens;
    }

    DataLogProgram* getDataLog() const {
        return dLP;
    }

    void advance() {
        ++parseIndex;
    }

    bool match(TokenType matchType) {
        if (inputStream.at(parseIndex)->getType() == matchType) {
            return true;
        }
        return false;
    }

    void clearParams() {
        params.clear();
    }

    void checkKeyword(TokenType keyType) {
        if (match(TokenType::EOFILE)) {
            return;
        }
        else if (match(keyType)) {
            if (keyType == TokenType::SCHEMES) {
                isScheme = true;
            }
            else if (keyType == TokenType::RULES) {
                isRule = true;
            }
            else if (keyType == TokenType::QUERIES) {
                isQuery = true;
                isRule = false;
            }
            else {
                isScheme = false;
                isRule = false;
                isQuery = false;
            }
            advance();
        }
        else {
            except = "Failure!\n" + inputStream.at(parseIndex)->toString();
            throw except;
        }
        if (match(TokenType::COLON)) {
            advance();
        }
        else {
            except = "Failure!\n" + inputStream.at(parseIndex)->toString();
            throw except;
        }
    }


    void parseAll() {
        try {
            checkKeyword(TokenType::SCHEMES);
            scheme();
            checkKeyword(TokenType::FACTS);
            factList();
            checkKeyword(TokenType::RULES);
            ruleList();
            checkKeyword(TokenType::QUERIES);
            query();
            dLP = new DataLogProgram(parseSchemes, parseFacts, parseRules, parseQueries, parseDomain);
        }
        catch(...) {
            std::cout << except;
            return;
        }
        //std::cout << toString();
    }

    void idList() {
        if (match(TokenType::COMMA)) {
            advance();
        }
        else if (match(TokenType::ID)) {
            parameter1 = new Parameter(inputStream.at(parseIndex)->getDescription());
            params.push_back(parameter1);
            advance();
        }
        else if (match(TokenType::RIGHT_PAREN) && inputStream.at(parseIndex-1)->getType() != TokenType::ID) {
            except = "Failure!\n" + inputStream.at(parseIndex)->toString();
            throw except;
        }
        else if (match(TokenType::RIGHT_PAREN)) {
            advance();
            if (match(TokenType::EOFILE)) {
                return;
            }
            else if (isScheme) {
                predicate1 = new Predicate(currId, params);
                parseSchemes.push_back(predicate1);
                clearParams();
                if (match(TokenType::FACTS)) {
                    isScheme = false;
                    return;
                }
            }
            else if (isRule) {
                rulePred = new Predicate(currId, params);
                clearParams();
                if (match(TokenType::COLON_DASH)) {
                    advance();
                    predicate();
                }
            }
            else if (validProduction(firstSchemes)) {
                return;
            }
            return;
        }
        else if (!isScheme) {
            return;
        }
        else {
            except = "Failure!\n" + inputStream.at(parseIndex)->toString();
            throw except;
        }
        idList();
    }

    void stringList() {
        if (isRule) {
            return;
        }
        else if (match(TokenType::COMMA)) {
            advance();
        }
        else if (match(TokenType::STRING)) {
            parameter1 = new Parameter(inputStream.at(parseIndex)->getDescription());
            params.push_back(parameter1);
            parseDomain.insert(inputStream.at(parseIndex)->getDescription());
            advance();
        }
        else if (match(TokenType::RIGHT_PAREN) && inputStream.at(parseIndex-1)->getType() != TokenType::STRING) {
            except = "Failure!\n" + inputStream.at(parseIndex)->toString();
            throw except;
        }
        else if (match(TokenType::RIGHT_PAREN)) {
            advance();
            if (match(TokenType::PERIOD)) {
                advance();
                if (match(TokenType::EOFILE) || match(TokenType::RULES)
                || match(TokenType::ID)) {
                    predicate1 = new Predicate(currId, params);
                    parseFacts.push_back(predicate1);
                    clearParams();
                    return;
                }
                else {
                    except = "Failure!\n" + inputStream.at(parseIndex)->toString();
                    throw except;
                }
            }
            else {
                except = "Failure!\n" + inputStream.at(parseIndex)->toString();
                throw except;
            }
        }
        else {
            except = "Failure!\n" + inputStream.at(parseIndex)->toString();
            throw except;
        }
        stringList();
    }

    bool validProduction(std::vector<TokenType> firstSet) {
        bool valid = true;
        if (match(TokenType::EOFILE)) {
            return false;
        }
        for (size_t i = 0; i < firstSet.size(); ++i) {
            if ( i == 0 && match(firstSet.at(i))) {
                if (inputStream.at(parseIndex)->getType() == TokenType::ID) {
                    currId = inputStream.at(parseIndex)->getDescription();
                }
            }
            else if (i != 0 && match(firstSet.at(i))) {
                if (inputStream.at(parseIndex)->getType() == TokenType::ID) {
                    parameter1 = new Parameter(inputStream.at(parseIndex)->getDescription());
                    params.push_back(parameter1);
                }
               else if (inputStream.at(parseIndex)->getType() == TokenType::STRING) {
                    parameter1 = new Parameter(inputStream.at(parseIndex)->getDescription());
                    params.push_back(parameter1);
                    parseDomain.insert(inputStream.at(parseIndex)->getDescription());
                }
            }
            if (match(TokenType::EOFILE)) {
                return false;
            }
            else if (isScheme) {
                if (match(TokenType::FACTS)) {
                    return false;
                }
                if (i == firstSet.size() - 1 &&  !match(TokenType::ID)) {
                    except = "Failure!\n" + inputStream.at(parseIndex)->toString();
                    throw except;
                }
            }
            else if (!isScheme && !isRule && !isQuery) {
                if (match(TokenType::RULES)) {
                    return false;
                }
            }
            else if (isRule) {
                if (match(TokenType::QUERIES)) {
                    return false;
                }
            }
            else if (isQuery) {
                if (match(TokenType::EOFILE)) {
                    return false;
                }
            }
            else {
                except = "Failure!\n" + inputStream.at(parseIndex)->toString();
                throw except;
            }
            advance();
        }
        return valid;
    }

    void scheme() {
        if (!isScheme) {
            return;
        }
        else if (validProduction(firstSchemes)) {
            idList();
        }
        else {
            except = "Failure!\n" + inputStream.at(parseIndex)->toString();
            throw except;
        }
        schemeList();
    }

    void schemeList() {
        scheme();
    }

    void fact() {
        if (isRule) {
            return;
        }
        else if (validProduction(firstFacts)) {
            stringList();
        }
        else {
            return;
        }
        factList();
    }

    void factList() {
        fact();
    }

    void headPredicate() {
        if (isQuery) {
            return;
        }
        else if (validProduction(firstSchemes)) {
            idList();
        }
        else {
            return;
        }
    }

    void parameterList() {
        if (match(TokenType::RIGHT_PAREN)) {
            advance();
            if (isRule) {
                predicate1 = new Predicate(currId, params);
                rulePreds.push_back(predicate1);
                clearParams();
                if (match(TokenType::PERIOD)) {
                    parseRule = new Rule(rulePred, rulePreds);
                    parseRules.push_back(parseRule);
                    rulePreds.clear();
                    advance();
                    if (match(TokenType::EOFILE) || match(TokenType::QUERIES)) {
                        isRule = false;
                        return;
                    }
                    else if (match(TokenType::ID)) {
                        return;
                    }
                    else {
                        except = "Failure!\n" + inputStream.at(parseIndex)->toString();
                        throw except;
                    }
                }
                else if (match(TokenType::RIGHT_PAREN) && (inputStream.at(parseIndex-1)->getType() != TokenType::ID
                || inputStream.at(parseIndex-1)->getType() != TokenType::STRING)) {
                    except = "Failure!\n" + inputStream.at(parseIndex)->toString();
                    throw except;
                }
                else if (match(TokenType::COMMA)) {
                    predicateList();
                }
                else {
                    except = "Failure!\n" + inputStream.at(parseIndex)->toString();
                    throw except;
                }
            }
            else if (isQuery) {
                if (match(TokenType::Q_MARK)) {
                    advance();
                    if (match(TokenType::EOFILE)) {
                        predicate1 = new Predicate(currId, params);
                        parseQueries.push_back(predicate1);
                        clearParams();
                        return;
                    }
                    else if (match(TokenType::ID)) {
                        predicate1 = new Predicate(currId, params);
                        parseQueries.push_back(predicate1);
                        clearParams();
                        predicate();
                    }
                    else {
                        except = "Failure!\n" + inputStream.at(parseIndex)->toString();
                        throw except;
                    }
                }
                else {
                    except = "Failure!\n" + inputStream.at(parseIndex)->toString();
                    throw except;
                }
            }
        }
        else if (match(TokenType::COMMA)) {
            advance();
            parameter();
        }
        else {
            except = "Failure!\n" + inputStream.at(parseIndex)->toString();
            throw except;
        }
    }

    void parameter() {
        if (match(TokenType::STRING) || match(TokenType::ID)) {
            parameter1 = new Parameter(inputStream.at(parseIndex)->getDescription());
            params.push_back(parameter1);
            advance();
        }
        else {
            except = "Failure!\n" + inputStream.at(parseIndex)->toString();
            throw except;
        }
        parameterList();
    }

    void predicate() {
        if (validProduction(firstPredicates)) {
            parameter();
        }
        predicateList();
    }

    void predicateList() {
        if (match(TokenType::COMMA)) {
            advance();
            predicate();
        }
        else if (isRule && match(TokenType::ID)) {
            headPredicate();
        }
        else if (!isRule) {
            return;
        }
        else {
            except = "Failure!\n" + inputStream.at(parseIndex)->toString();
            throw except;
        }
    }

    void rule() {
        headPredicate();
        if (match(TokenType::COLON_DASH)) {
            advance();
        }
        else {
            return;
        }
        predicate();
    }

    void ruleList() {
        rule();
    }

    void query() {
        predicate();
        queryList();
    }

    void queryList() {
        if (match(TokenType::ID)) {
            query();
        }
        else {
            return;
        }
    }

    std::string toString() const {
        std::stringstream ss;
        ss << "Success!" << std::endl;
        ss << dLP->toString();
        return ss.str();
    }

};


#endif //CS236COOLPROJECT_PARSER_H
