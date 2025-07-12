#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP

#include <vector>

#include "token.hpp"

class Tokenizer {
    private:
        std::vector< Token > tokens;
        std::string inS;

        void tokenizeHelper(char& c, std::string& inS, std::string& tokenString, bool isDigit);
    public:
        Tokenizer();
        Tokenizer(std::string& inS);

        void tokenize();
        void tokenize(std::string& inS);
        void setInS(std::string& inS);
        std::vector< Token > getTokens() const;
        std::string toString() const;
};

#endif // TOKENIZER_HPP