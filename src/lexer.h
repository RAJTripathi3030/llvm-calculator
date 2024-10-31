#include <cstring>
#include <iostream>
#include <optional>
#include <string>
#include <vector>
namespace calculator {

namespace lexer {

enum TokenKind {
  TOKEN_NUMBER,

  // Operators
  TOKEN_PLUS,
  TOKEN_MINUS,
  TOKEN_DIV,
  TOKEN_MULT,

  // Error
  TOKEN_ERROR,

  // EOF
  TOKEN_EOF
};

struct Token {
  TokenKind tt_;
  char *starts_at_;
  int length_;
  std::optional<double> tt_value_;

  Token(TokenKind tt, char *sa, int length, std::optional<double> tt_value)
      : tt_(tt), starts_at_(sa), length_(length), tt_value_(tt_value) {}

  void DumpToken() {
    char *substr = reinterpret_cast<char *>(calloc(length_ + 2 , sizeof(char)));
    memcpy(substr, starts_at_, length_);
    const char *tok_t_str = [&]() -> const char * {
      switch (tt_) {
      case TOKEN_MULT:
        return "Mult";
      case TOKEN_DIV:
        return "Div";
      case TOKEN_PLUS:
        return "Plus";
      case TOKEN_MINUS:
        return "Minus";
      case TOKEN_EOF:
        return "EOF";
      case TOKEN_ERROR:
        return "ERROR";
      case TOKEN_NUMBER:
        return "Number";
      }
      return nullptr;
    }();

    fprintf(stderr, "TT: %s, contents: %s, value: %lf\n", tok_t_str, substr,
            tt_value_.has_value() ? tt_value_.value() : -69.6969);
    free(substr);
  }
};

class Lexer {
public:
  Lexer(std::string src);
  void lex_all();

  std::vector<struct Token> get_tokens() { return token_list_; }

private:
  const char *src_;
  char *curr_pos_;
  char *start_pos_;
  void lex_one_token();
  char advance_();
  char peek_();
  char peekNext_();
  bool atEnd();
  void makeNumberToken();
  std::vector<struct Token> token_list_;
  void skipWS();
};

} // namespace lexer

} // namespace calculator
