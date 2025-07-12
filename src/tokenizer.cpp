#include "../include/tokenizer.hpp"

// Constructors
Tokenizer::Tokenizer() {
    this->inS = "";
}

Tokenizer::Tokenizer(std::string& inS) : inS(inS) {
    tokenize();
}

// Private methods
void Tokenizer::tokenizeHelper(char& c, std::string& inS, std::string& tokenString, bool isDigit) {
    while ( (!inS.empty() ) && ( (isDigit) ? std::isdigit(c) : std::isalpha(c) )) {
        tokenString.push_back(c);
        inS.erase(inS.begin());
        if (!inS.empty()) {
            c = inS.at(0);
        }
    }
}

// Public methods
void Tokenizer::tokenize() {
    while(inS.length() > 0) {
        char c = inS.at(0);
        std::string tokenString = "";

        if (std::isalpha(c)) {
            tokenizeHelper(c, inS, tokenString, false);

            if (tokenString == "return") {
                tokens.push_back({TokenType::_return, tokenString});
            }   else { // NOTE: Is not a keyword (variables or strings)
                // Not implemented yet
                std::string error("Invalid token: ");
                error += tokenString;

                throw TokenException(error.c_str());
            }
        }   else if (std::isdigit(c)) {
            tokenizeHelper(c, inS, tokenString, true);
            tokens.push_back({TokenType::int_l, tokenString});
        }   else if (c == ';') {
            tokenString.push_back(c);
            tokens.push_back({TokenType::semicolon, tokenString});
            inS.erase(inS.begin());
        }   else if (c == ' ' || c == '\n') {
            inS.erase(inS.begin());
        }   else {
            std::string error("The character ");
            error += c;
            error += " is not currently accepted by the compiler.";

            throw TokenException(error.c_str());
        }
    }
}

void Tokenizer::tokenize(std::string& inS) {
    setInS(inS);
    tokenize();
}

void Tokenizer::setInS(std::string& inS) {
    this->inS = inS;
}

std::string Tokenizer::getInS() const {
    return inS;
}

std::vector< Token > Tokenizer::getTokens() const {
    return tokens;
}

std::vector< Token >& Tokenizer::getTokens() { // reference accessor
    return tokens;
}

std::string Tokenizer::toString() const {
    std::string result = "";

    for (const Token& token : tokens) {
        result += "[" + token.getTypeString() + ", " + token.getData() + "]\n";
    }

    return result;
}