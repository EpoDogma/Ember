#include <iostream>
#include <fstream>
#include <vector>

enum class TokenType {
    exit,
    semicolon,
    int_l
};

struct Token {
    public:
        TokenType type;
        std::string data;
        Token() {};
        Token(TokenType type, std::string data) {
            this->type = type;
            this->data = data;
        };
        std::string getTypeString() {
            std::string result;

            if (type == TokenType::exit) {
                result = "return";
            }   else if (type == TokenType::semicolon) {
                result = "semicolon";
            }   else if (type == TokenType::int_l) {
                result = "int_l";
            }

            return result;
        }
};


bool isSyntaxValid(int&, char* argv[]);
bool isint(std::string&);
void extractUntilDiff(char&, std::string&, std::string&, bool);

int main(int argc, char* argv[]) {
    // Confirm executable syntax is being followed : ./compiler [program.em]
    if (!isSyntaxValid(argc, argv)) {
        return EXIT_FAILURE;
    }

    // Pull program.em file stream (FS)
    std::ifstream inFS(argv[1]);
    std::string inS;

    inFS.seekg(0, std::ios::end);
    inS.resize(inFS.tellg());
    inFS.seekg(0, std::ios::beg);
    inFS.read(&inS[0], inS.size());
    inFS.close();

    // Tokenize FS
    std::vector< Token > tokens;
    std::string tokenString;

    while(inS.length() > 0) {
        char c = inS.at(0);
        tokenString = "";

        if (std::isalpha(c)) {
            extractUntilDiff(c, inS, tokenString, false);

            if (tokenString == "return") {
                tokens.push_back({TokenType::exit, tokenString});
            }   else { // NOTE: Is not a keyword (variables or strings)
                continue; // Not implemented yet.
            }
        }   else if (std::isdigit(c)) {
            extractUntilDiff(c, inS, tokenString, true);
            tokens.push_back({TokenType::int_l, tokenString});
        }   else if (c == ';') {
            tokenString.push_back(c);
            tokens.push_back({TokenType::semicolon, tokenString});
            inS.erase(inS.begin());
        }   else if (c == ' ' || c == '\n') {
            inS.erase(inS.begin());
        }
    }

    // Display tokenized FS
    for (Token token : tokens) {
        std::cout << "[" << token.getTypeString() << ", " << token.data << "]" << std::endl;
    }

    // Translate into Assembly

    // Write to file

    // NOTE: Currently handling program assembling and linking externally.
    return EXIT_SUCCESS;
}

bool isSyntaxValid(int& argc, char* argv[]) {
    if (argc == 2) {
        return true;
    }

    std::cout << "Invalid usage. Please follow the syntax: ./compiler [program.em]" << std::endl;
    return false;
}

bool isint(std::string& string) {
    if (string.empty()) {
        return false;
    }

    int start = 0;

    if (string[0] == '-' || string[0] == '+') { // Explicit positie or negative number
        if (string.length() == 1) { // Must have at least one digit
            return false;
        }

        start++;
    }

    for (int i = start; i < string.length(); i++) {
        if (!std::isdigit(string[i])) {
            return false;
        }
    }

    return true;  
}

void extractUntilDiff(char& c, std::string& inS, std::string& tokenString, bool isDigit) {
    while (!inS.empty() && (isDigit) ? std::isdigit(c) : std::isalpha(c)) {
        tokenString.push_back(c);
        inS.erase(inS.begin());
        if (!inS.empty()) {
            c = inS.at(0);
        }
    }
}

