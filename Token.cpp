#include "Token.h"

// ¬озвращаем индекс токена
int Token::getIndex() {
    return index;
}

// ¬озвращаем строковое представление типа токена
string Token::getType() {
    switch (type) {
    case TokenType::PROGRAM:     
        return "PROGRAM";
    case TokenType::TYPE:        
        return "TYPE";
    case TokenType::BEGIN:       
        return "BEGIN";
    case TokenType::END:         
        return "END";
    case TokenType::ID_NAME:     
        return "ID_NAME";
    case TokenType::INT_NUM:     
        return "INT_NUM";
    case TokenType::REAL_NUM:    
        return "REAL_NUM";
    case TokenType::OPERATOR:    
        return "OPERATOR";
    case TokenType::DELIMITER:   
        return "DELIMITER";
    case TokenType::FUNC:        
        return "FUNC";
    case TokenType::ERROR:       
        return "ERROR";
    default:                     
        return "UNKNOWN";
    }
} 