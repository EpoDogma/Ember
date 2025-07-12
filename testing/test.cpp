#include <gtest/gtest.h>

#include <token.hpp>
#include "../src/tokenizer.cpp"

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(Token, TokenContructorsValid) {
    Token token;
    std::string data = token.getData();
    ASSERT_STREQ(data.c_str(), "");

    ASSERT_NO_THROW(token = Token(TokenType::_return, "return"));
    ASSERT_STREQ(data.c_str(), "return");
    ASSERT_EQ(token.getType(), TokenType::_return);

    ASSERT_NO_THROW(token = Token(TokenType::int_l, "4256"));
    ASSERT_STREQ(data.c_str(), "4256");
    ASSERT_EQ(token.getType(), TokenType::int_l);

    ASSERT_NO_THROW(token = Token(TokenType::int_l, "3"));
    ASSERT_STREQ(data.c_str(), "3");
    ASSERT_EQ(token.getType(), TokenType::int_l);

    ASSERT_NO_THROW(token = Token(TokenType::int_l, "0"));
    ASSERT_STREQ(data.c_str(), "0");
    ASSERT_EQ(token.getType(), TokenType::int_l);

    ASSERT_NO_THROW(token = Token(TokenType::int_l, "99999999999912098730982170985092310981274098127309872139999"));
    ASSERT_STREQ(data.c_str(), "99999999999912098730982170985092310981274098127309872139999");
    ASSERT_EQ(token.getType(), TokenType::int_l);

    ASSERT_NO_THROW(token = Token(TokenType::semicolon, ";"));
    ASSERT_STREQ(data.c_str(), ";");
    ASSERT_EQ(token.getType(), TokenType::semicolon);
}

TEST(Token, TokenContructorsInvalid) {
    Token token;
    /*
    ASSERT_ANY_THROW(token = Token(TokenType::int_l, "return"));
    ASSERT_ANY_THROW(token = Token(TokenType::int_l, ";"));
    ASSERT_ANY_THROW(token = Token(TokenType::int_l, ""));

    ASSERT_ANY_THROW(token = Token(TokenType::_return, "42"));
    ASSERT_ANY_THROW(token = Token(TokenType::_return, ";"));
    ASSERT_ANY_THROW(token = Token(TokenType::_return, ""));

    ASSERT_ANY_THROW(token = Token(TokenType::semicolon, "42"));
    ASSERT_ANY_THROW(token = Token(TokenType::semicolon, "return"));
    ASSERT_ANY_THROW(token = Token(TokenType::semicolon, ""));
    */
}

TEST(Tokenizer, Tokenizer) {
    Tokenizer tkzr;

    ASSERT_STREQ(tkzr.getInS().c_str(), "");

    std::string inS("return 42;\n");
    tkzr = Tokenizer(inS);
    std::vector< Token > tokens(tkzr.getTokens());

    ASSERT_STREQ(tkzr.getInS().c_str(), "");
    ASSERT_EQ(tokens.at(0).getType(), TokenType::_return);
    ASSERT_STREQ(tokens.at(0).getData().c_str(), "return");
    ASSERT_EQ(tokens.at(1).getType(), TokenType::int_l);
    ASSERT_STREQ(tokens.at(1).getData().c_str(), "42");
    ASSERT_EQ(tokens.at(2).getType(), TokenType::semicolon);
    ASSERT_STREQ(tokens.at(2).getData().c_str(), ";");

    inS = "return 998;\n";
    tkzr.setInS(inS);
    tkzr.tokenize();
    tokens = std::vector< Token >(tkzr.getTokens());

    ASSERT_STREQ(tkzr.getInS().c_str(), "");
    ASSERT_EQ(tokens.at(0).getType(), TokenType::_return);
    ASSERT_STREQ(tokens.at(0).getData().c_str(), "return");
    ASSERT_EQ(tokens.at(1).getType(), TokenType::int_l);
    ASSERT_STREQ(tokens.at(1).getData().c_str(), "998");
    ASSERT_EQ(tokens.at(2).getType(), TokenType::semicolon);
    ASSERT_STREQ(tokens.at(2).getData().c_str(), ";");

    inS = "return 35;\n";
    tkzr.setInS(inS);
    tkzr.tokenize();
    tokens = tkzr.getTokens();

    ASSERT_STREQ(tkzr.getInS().c_str(), "");
    ASSERT_EQ(tokens.at(0).getType(), TokenType::_return);
    ASSERT_STREQ(tokens.at(0).getData().c_str(), "return");
    ASSERT_EQ(tokens.at(1).getType(), TokenType::int_l);
    ASSERT_STREQ(tokens.at(1).getData().c_str(), "35");
    ASSERT_EQ(tokens.at(2).getType(), TokenType::semicolon);
    ASSERT_STREQ(tokens.at(2).getData().c_str(), ";");

    ASSERT_STREQ(tkzr.toString().c_str(), "[_return, return]\n[int_l, 35]\n[semicolon, ;]\n");
}
