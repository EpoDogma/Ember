#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP

#include <vector>

#include "token.hpp"

class TokenException : public std::exception {
    private:
        const char* message;
    
    public:
        TokenException() {}
        TokenException(const char* message) : message(message) {}

        const char* what() const noexcept override{
            return message;
        }
};

class Tokenizer {
    private:
        std::vector< Token > tokens;
        std::string inS;

        void tokenizeHelper(char& c, std::string& inS, std::string& tokenString, bool isDigit);
        void tokenizeAlphaHelper(std::string& tokenString);
    public:
        Tokenizer();
        Tokenizer(std::string& inS);

        void tokenize();
        void tokenize(std::string& inS);
        void setInS(std::string& inS);
        std::string getInS() const;
        std::vector< Token > getTokens() const;
        std::vector< Token >& getTokens();
        std::string toString() const;
};

#endif // TOKENIZER_HPP