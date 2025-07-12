#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>

enum class TokenType {
    _return,
    semicolon,
    int_l,
    o_parenthesis,
    c_parenthesis,
    o_brace,
    c_brace,
    add,
    sub,
    eq
};

struct Token {
    private:
        TokenType type;
        std::string data;
    public:
        Token() : data("") {};
        Token(TokenType type, std::string data) : type(type), data(data) {};

        TokenType getType() const{
            return type;
        }

        std::string getData() const{
            return data;
        }

        std::string getTypeString() const {
            std::string result;

            if (type == TokenType::_return) {
                result = "_return";
            }   else if (type == TokenType::semicolon) {
                result = "semicolon";
            }   else if (type == TokenType::int_l) {
                result = "int_l";
            }

            return result;
        }

        void setType(TokenType type) {
            this->type = type;
        }
        
        void setData(std::string data) {
            this->data = data;
        }
};

#endif // TOKEN_HPP