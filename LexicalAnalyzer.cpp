#include "LexicalAnalyzer.h"
#include "Token.h"
#include <iostream>
#include <vector>
#include <cctype>
using namespace std;

enum class State {
    START,       
    ID_NAME_STATE,  
    NUMBER_STATE, 
    OPERATOR_STATE,
    DELIMITER_STATE,
    ERROR_STATE    
};


bool LexicalAnalyzer::isOperator(char elem) const {
    return (elem == '+' || elem == '-' || elem == '=');
}

bool LexicalAnalyzer::isDelimiter(char elem) const {
    return (elem == '(' || elem == ')' || elem == ',');
}

bool LexicalAnalyzer::isWrongSymbol(char elem) const
{
    bool isNum = (elem == '0' || elem == '1' || elem == '2' || elem == '3' || elem == '4' || elem == '5' ||
        elem == '6' || elem == '7' || elem == '8' || elem == '9');
    return (!isDelimiter(elem) && !isOperator(elem) && !isalpha(elem) && !isNum && elem != ' ');
}

Token LexicalAnalyzer::getNextLexeme() {
    string lexeme;
    char elem;
    State currentState = State::START;
    int index = 1;

    while (inputFile.get(elem)) {
        switch (currentState) {
        case State::START:
            if (isspace(elem)) {
                index++;
                continue;
            }

            if (isalpha(elem)) {
                currentState = State::ID_NAME_STATE;
                lexeme += elem;
                //inputFile.unget();
                //inputFile.unget();
            }
            else if (isdigit(elem)) {
                currentState = State::NUMBER_STATE;
                lexeme += elem;
            }
            else if (isOperator(elem)) {
                currentState = State::OPERATOR_STATE;
                lexeme += elem;
            }
            else if (isDelimiter(elem)) {
                currentState = State::DELIMITER_STATE;
                lexeme += elem;
            }
            else {
                currentState = State::ERROR_STATE;
                lexeme += elem;
            }
            break;

        case State::ID_NAME_STATE:
            if (isalpha(elem)) {
                lexeme += elem;
                //Распознавание лексемы начала программы "PROGRAM"
                if (elem == 'R' && lexeme.size() == 2) {
                    inputFile.get(elem);
                    lexeme += elem;
                    if (isdigit(elem) || isWrongSymbol(elem)) {
                        currentState = State::ERROR_STATE;
                        break;
                    }
                    else if (isalpha(elem)) {
                        if (elem != 'O') {
                            currentState = State::ID_NAME_STATE;
                        }
                        else if (elem == 'O') {
                            inputFile.get(elem);
                            lexeme += elem;
                            if (isdigit(elem) || isWrongSymbol(elem)) {
                                currentState = State::ERROR_STATE;
                                break;
                            }
                            else if (isalpha(elem)) {
                                if (elem != 'G') {
                                    currentState = State::ID_NAME_STATE;
                                }
                                else if (elem == 'G') {
                                    inputFile.get(elem);
                                    lexeme += elem;
                                    if (isdigit(elem) || isWrongSymbol(elem)) { 
                                        currentState = State::ERROR_STATE;
                                        break;
                                    }
                                    else if (isalpha(elem)) {
                                        if (elem != 'R') {
                                            currentState = State::ID_NAME_STATE; 
                                        }
                                        else if (elem == 'R') {
                                            inputFile.get(elem);
                                            lexeme += elem;
                                            if (isdigit(elem) || isWrongSymbol(elem)) { 
                                                currentState = State::ERROR_STATE;
                                                break;
                                            }
                                            else if (isalpha(elem)) {
                                                if (elem != 'A') {
                                                    currentState = State::ID_NAME_STATE; 
                                                }
                                                else if (elem == 'A') {
                                                    inputFile.get(elem);
                                                    lexeme += elem;
                                                    if (isdigit(elem) || isWrongSymbol(elem)) { 
                                                        currentState = State::ERROR_STATE;
                                                        break;
                                                    }
                                                    else if (isalpha(elem)) {
                                                        if (elem != 'M') {
                                                            currentState = State::ID_NAME_STATE; 
                                                        }
                                                        else if (elem == 'M') {
                                                            inputFile.get(elem);
                                                            lexeme += elem;
                                                            if (isdigit(elem) || isWrongSymbol(elem)) { 
                                                                currentState = State::ERROR_STATE;
                                                                break;
                                                            }
                                                            else if (isalpha(elem)) {
                                                                return Token(TokenType::ID_NAME, lexeme, index, 0);
                                                            }
                                                            else if (elem == ' ') {
                                                                inputFile.unget();
                                                                lexeme.erase(lexeme.end() - 1);
                                                                return Token(TokenType::PROGRAM, lexeme, index, 0);
                                                            }
                                                        }
                                                    }
                                                    else if (isDelimiter(elem) || isOperator(elem) || elem == ' ') {
                                                        inputFile.unget();
                                                        return Token(TokenType::ID_NAME, lexeme, index, 0);
                                                    }
                                                }
                                            }
                                            else if (isDelimiter(elem) || isOperator(elem) || elem == ' ') {
                                                inputFile.unget();
                                                return Token(TokenType::ID_NAME, lexeme, index, 0);
                                            }
                                        }
                                    }
                                    else if (isDelimiter(elem) || isOperator(elem) || elem == ' ') {
                                        inputFile.unget();
                                        return Token(TokenType::ID_NAME, lexeme, index, 0);
                                    }
                                }
                            }
                            else if (isDelimiter(elem) || isOperator(elem) || elem == ' ') {
                                inputFile.unget();
                                return Token(TokenType::ID_NAME, lexeme, index, 0);
                            }
                        }
                    }
                    else if (isDelimiter(elem) || isOperator(elem) || elem == ' ') {
                        inputFile.unget();
                        return Token(TokenType::ID_NAME, lexeme, index, 0);
                    }

                }
                //Распознавание лексемы "INTEGER"
                else if (elem == 'N' && lexeme == "IN") {
                    inputFile.get(elem);
                    lexeme += elem;
                    if (isdigit(elem) || isWrongSymbol(elem)) {
                        currentState = State::ERROR_STATE;
                        break;
                    }
                    else if (isalpha(elem)) {
                        if (elem != 'T') {
                            currentState = State::ID_NAME_STATE;
                        }
                        else if (elem == 'T') {
                            inputFile.get(elem);
                            lexeme += elem;
                            if (isdigit(elem) || isWrongSymbol(elem)) {
                                currentState = State::ERROR_STATE;
                                break;
                            }
                            else if (isalpha(elem)) {
                                if (elem != 'E') {
                                    currentState = State::ID_NAME_STATE;
                                }
                                else if (elem == 'E') {
                                    inputFile.get(elem);
                                    lexeme += elem;
                                    if (isdigit(elem) || isWrongSymbol(elem)) {
                                        currentState = State::ERROR_STATE;
                                        break;
                                    }
                                    else if (isalpha(elem)) {
                                        if (elem != 'G') {
                                            currentState = State::ID_NAME_STATE;
                                        }
                                        else if (elem == 'G') {
                                            inputFile.get(elem);
                                            lexeme += elem;
                                            if (isdigit(elem) || isWrongSymbol(elem)) {
                                                currentState = State::ERROR_STATE;
                                                break;
                                            }
                                            else if (isalpha(elem)) {
                                                if (elem != 'E') {
                                                    currentState = State::ID_NAME_STATE;
                                                }
                                                else if (elem == 'E') {
                                                    inputFile.get(elem);
                                                    lexeme += elem;
                                                    if (isdigit(elem) || isWrongSymbol(elem)) {
                                                        currentState = State::ERROR_STATE;
                                                        break;
                                                    }
                                                    else if (isalpha(elem)) {
                                                        if (elem != 'R') {
                                                            currentState = State::ID_NAME_STATE;
                                                        }
                                                        else if (elem == 'R') {
                                                            inputFile.get(elem);
                                                            lexeme += elem;
                                                            if (isdigit(elem) || isWrongSymbol(elem) || isOperator(elem) || isDelimiter(elem)) {
                                                                currentState = State::ERROR_STATE;
                                                                break;
                                                            }
                                                            else if (isalpha(elem)) {
                                                                currentState = State::ID_NAME_STATE;
                                                            }
                                                            else if (elem == ' ') {
                                                                inputFile.unget();
                                                                lexeme.erase(lexeme.end() - 1);
                                                                return Token(TokenType::TYPE, lexeme, index, 0);
                                                            }
                                                        }
                                                    }
                                                    else if (isDelimiter(elem) || isOperator(elem) || elem == ' ') {
                                                        inputFile.unget();
                                                        return Token(TokenType::ID_NAME, lexeme, index, 0);
                                                    }
                                                }
                                            }
                                            else if (isDelimiter(elem) || isOperator(elem) || elem == ' ') {
                                                inputFile.unget();
                                                return Token(TokenType::ID_NAME, lexeme, index, 0);
                                            }
                                        }
                                    }
                                    else if (isDelimiter(elem) || isOperator(elem) || elem == ' ') {
                                        inputFile.unget();
                                        return Token(TokenType::ID_NAME, lexeme, index, 0);
                                    }
                                }
                            }
                            else if (isDelimiter(elem) || isOperator(elem) || elem == ' ') {
                                inputFile.unget();
                                return Token(TokenType::ID_NAME, lexeme, index, 0);
                            }
                        }
                        else if (isDelimiter(elem) || isOperator(elem) || elem == ' ') {
                            inputFile.unget();
                            return Token(TokenType::ID_NAME, lexeme, index, 0);
                        }
                    }
                }
                //Распознавание лексемы ITOR
                else if (elem == 'T' && lexeme == "IT") {
                    inputFile.get(elem);
                    lexeme += elem;
                    if (isdigit(elem) || isWrongSymbol(elem)) {
                        currentState = State::ERROR_STATE;
                        break;
                    }
                    else if (isalpha(elem)) {
                        if (elem != 'O') {
                            currentState = State::ID_NAME_STATE;
                        }
                        else if (elem == 'O') {
                            inputFile.get(elem);
                            lexeme += elem;
                            if (isdigit(elem) || isWrongSymbol(elem)) {
                                currentState = State::ERROR_STATE;
                                break;
                            }
                            else if (isalpha(elem)) {
                                if (elem != 'R') {
                                    currentState = State::ID_NAME_STATE;
                                }
                                else if (elem == 'R') {
                                    inputFile.get(elem);
                                    lexeme += elem;
                                    if (isdigit(elem) || isWrongSymbol(elem)) {
                                        currentState = State::ERROR_STATE;
                                        break;
                                    }
                                    else if (isalpha(elem)) {
                                        currentState = State::ID_NAME_STATE;
                                    }
                                    else if (isDelimiter(elem) || isOperator(elem) || elem == ' ') {
                                        inputFile.unget();
                                        lexeme.erase(lexeme.end() - 1);
                                        return Token(TokenType::FUNC, lexeme, index, 0);
                                    }
                                }
                                
                            }
                            else if (isDelimiter(elem) || isOperator(elem) || elem == ' ') {
                                inputFile.unget();
                                return Token(TokenType::ID_NAME, lexeme, index, 0);
                            }
                        }
                    }
                    else if (isDelimiter(elem) || isOperator(elem) || elem == ' ') {
                        inputFile.unget();
                        return Token(TokenType::ID_NAME, lexeme, index, 0);
                    }
                }
                //Распознавание лексеммы REAL
                else if (elem == 'E' && lexeme == "RE") {
                    inputFile.get(elem);
                    lexeme += elem;
                    if (isdigit(elem) || isWrongSymbol(elem)) {
                        currentState = State::ERROR_STATE;
                        break;
                    }
                    else if (isalpha(elem)) {
                        if (elem != 'A') {
                            currentState = State::ID_NAME_STATE;
                        }
                        else if (elem == 'A') {
                            inputFile.get(elem);
                            lexeme += elem;
                            if (isdigit(elem) || isWrongSymbol(elem)) {
                                currentState = State::ERROR_STATE;
                                break;
                            }
                            else if (isalpha(elem)) {
                                if (elem != 'L') {
                                    currentState = State::ID_NAME_STATE;
                                }
                                else if (elem == 'L') {
                                    inputFile.get(elem);
                                    lexeme += elem;
                                    if (isdigit(elem) || isWrongSymbol(elem) || isOperator(elem) || isDelimiter(elem)) {
                                        currentState = State::ERROR_STATE;
                                        break;
                                    }
                                    else if (isalpha(elem)) {
                                        currentState = State::ID_NAME_STATE;
                                    }
                                    else if (elem == ' ') {
                                        inputFile.unget();
                                        lexeme.erase(lexeme.end() - 1);
                                        return Token(TokenType::TYPE, lexeme, index, 0);
                                    }
                                }
                            }
                            else if (isDelimiter(elem) || isOperator(elem) || elem == ' ') {
                                inputFile.unget();
                                return Token(TokenType::ID_NAME, lexeme, index, 0);
                            }
                        }
                    }
                    else if (isDelimiter(elem) || isOperator(elem) || elem == ' ') {
                        inputFile.unget();
                        return Token(TokenType::ID_NAME, lexeme, index, 0);
                    }
                }
                //РАСПОЗНАВАНИЕ RTOI
                else if (elem == 'T' && lexeme == "RT") {
                    inputFile.get(elem);
                    lexeme += elem;
                    if (isdigit(elem) || isWrongSymbol(elem)) {
                        currentState = State::ERROR_STATE;
                        break;
                    }
                    else if (isalpha(elem)) {
                        if (elem != 'O') {
                            currentState = State::ID_NAME_STATE;
                        }
                        else if (elem == 'O') {
                            inputFile.get(elem);
                            lexeme += elem;
                            if (isdigit(elem) || isWrongSymbol(elem)) {
                                currentState = State::ERROR_STATE;
                                break;
                            }
                            else if (isalpha(elem)) {
                                if (elem != 'I') {
                                    currentState = State::ID_NAME_STATE;
                                }
                                else if (elem == 'I') {
                                    inputFile.get(elem);
                                    lexeme += elem;
                                    if (isdigit(elem) || isWrongSymbol(elem)) {
                                        currentState = State::ERROR_STATE;
                                        break;
                                    }
                                    else if (isalpha(elem)) {
                                        currentState = State::ID_NAME_STATE;
                                    }
                                    else if (isDelimiter(elem) || isOperator(elem) || elem == ' ') {
                                        inputFile.unget();
                                        lexeme = "RTOI";
                                        return Token(TokenType::FUNC, lexeme, index, 0);
                                    }
                                }
                            }
                            else if (isDelimiter(elem) || isOperator(elem) || elem == ' ') {
                                inputFile.unget();
                                return Token(TokenType::ID_NAME, lexeme, index, 0);
                            }
                        }
                    }
                    else if (isDelimiter(elem) || isOperator(elem) || elem == ' ') {
                        inputFile.unget();
                        return Token(TokenType::ID_NAME, lexeme, index, 0);
                    }
                    }
                //Распознавание лексемы END
                else if (elem == 'N' && lexeme == "EN") {
                    inputFile.get(elem);
                    lexeme += elem;
                    if (isdigit(elem) || isWrongSymbol(elem)) {
                        currentState = State::ERROR_STATE;
                        break;
                    }
                    else if (isalpha(elem)) {
                        if (elem != 'D') {
                            currentState = State::ID_NAME_STATE; 
                        }
                        else if (elem == 'D') {
                            inputFile.get(elem);
                            lexeme += elem;
                            if (isdigit(elem) || isWrongSymbol(elem)) { 
                                currentState = State::ERROR_STATE;
                                break;
                            }
                            else if (isalpha(elem)) {
                                currentState = State::ID_NAME_STATE;
                            }
                            else if (isDelimiter(elem) || isOperator(elem) || elem == ' ') {
                                inputFile.unget();
                                lexeme = "END";
                                return Token(TokenType::END, lexeme, index, 0);
                            }
                        }
                    }
                    else if (isDelimiter(elem) || isOperator(elem) || elem == ' ') {
                        inputFile.unget();
                        return Token(TokenType::ID_NAME, lexeme, index, 0);
                    }
                }
                //Распознавание любых других буквенных лексем 
                else {
                    while (inputFile.get(elem) && isalpha(elem)) {
                        lexeme += elem;
                    }
                    if (isdigit(elem) || isWrongSymbol(elem)) {
                        currentState = State::ERROR_STATE;
                        lexeme += elem;
                    }
                    else if (isDelimiter(elem) || isOperator(elem) || elem == ' ') {
                        inputFile.unget();
                        //lexeme.erase(lexeme.end() - 1);
                        return Token(TokenType::ID_NAME, lexeme, index, 0);
                    }
                }
            }
            else if (isdigit(elem) || isWrongSymbol(elem)) {
                currentState = State::ERROR_STATE;
                lexeme += elem;
            }
            else if (isDelimiter(elem) || isOperator(elem) || elem == ' ') {
                inputFile.unget();
                //lexeme.erase(lexeme.end() - 1);
                return Token(TokenType::ID_NAME, lexeme, index, 0);
            }
            break;

        case State::NUMBER_STATE:
            if (isdigit(elem)) {
                lexeme += elem;
            }
            else if (elem == '.') {
                lexeme += elem;
            }
            else if (isalpha(elem)) {
                lexeme += elem;
                currentState = State::ERROR_STATE;
            }
            else {
                inputFile.unget();
                if (lexeme.find('.') != -1) {
                    return Token(TokenType::REAL_NUM, lexeme, index, 0);
                }
                else {
                    return Token(TokenType::INT_NUM, lexeme, index, 0);
                }
            }
            break;

        case State::OPERATOR_STATE:
            inputFile.unget();
            return Token(TokenType::OPERATOR, lexeme, index, 0);

        case State::DELIMITER_STATE:
            inputFile.unget();
            return Token(TokenType::DELIMITER, lexeme, index, 0);

        case State::ERROR_STATE:
            if (isspace(elem) || isDelimiter(elem) || isOperator(elem)) {
                inputFile.unget();
                return Token(TokenType::ERROR, lexeme, index, 0);
            }
            else {
                lexeme += elem;
            }
            break;
        }
    }

    return Token(TokenType::UNKNOWN, "", index, 0);
}

void LexicalAnalyzer::analyzer() {
    Token token;
    while ((token = getNextLexeme()).type != TokenType::UNKNOWN) {
        tokenList.newToken(token);
    }

    tokenList.outTable(outputFile);
}

