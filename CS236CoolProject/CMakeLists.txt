cmake_minimum_required(VERSION 3.16)
project(CS236CoolProject)

set(CMAKE_CXX_STANDARD 14)

add_executable(CS236CoolProject main.cpp Automaton.h Token.h Lexer.h ColonDashAutomaton.h ColonAutomaton.h CommaAutomaton.h PeriodAutomaton.h QuestionMarkAutomaton.h LeftParenAutomaton.h RightParenAutomaton.h MultiplyAutomaton.h AddAutomaton.h Schemes.h FactsAutomaton.h RulesAutomaton.h Queries.h IDAutomaton.h StringAutomaton.h LineCommentAutomaton.h BlockComment.h UndefinedAutomaton.h DatalogProgram.h Parser.h Predicate.h Parameter.h Rule.h Tuple.h Header.h Relation.h Interpreter.h DataBase.h Graph.h)
