
#include "lexer.h"
#include <cctype>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

namespace calculator::lexer {

char Lexer::advance_() {
  curr_pos_++;
  return *(curr_pos_ - 1);
}

char Lexer::peek_() { return *curr_pos_; }

char Lexer::peekNext_() {
  if (atEnd())
    return '\0';
  return *(curr_pos_ + 1);
}

Lexer::Lexer(std::string src) {
  src_ = src.c_str();
  curr_pos_ = const_cast<char *>(src_);
  start_pos_ = const_cast<char *>(src_);
}

bool Lexer::atEnd() { return *curr_pos_ == '\0'; }

void Lexer::lex_all() {
  while (!atEnd()) {
    // skipWS();
    lex_one_token();
  }
}

void Lexer::skipWS() {
  for (;;) {
    char cur = peek_();
    switch (cur) {
    case ' ':
    case '\r':
    case '\t':
      advance_();
      break;
    default:
      return;
    }
  }
}

void Lexer::lex_one_token() {
  if (atEnd()) {
    return;
  }
  start_pos_ = curr_pos_;
  char ch = advance_();
  if (std::isdigit(ch)) {
    makeNumberToken();
    return;
  }
  switch (ch) {
  case '/': {
    const auto tok = Token(TOKEN_DIV, start_pos_, 1, std::nullopt);
    token_list_.push_back(tok);
    return;
  }
  case '+': {
    const auto tok = Token(TOKEN_PLUS, start_pos_, 1, std::nullopt);
    token_list_.push_back(tok);
    return;
  }
  case '-': {
    const auto tok = Token(TOKEN_MINUS, start_pos_, 1, std::nullopt);
    token_list_.push_back(tok);
    return;
  }
  case '*': {
    const auto tok = Token(TOKEN_MULT, start_pos_, 1, std::nullopt);
    token_list_.push_back(tok);
    return;
  }
  case ' ':
  case '\r':
  case '\t':
    break;
  default: {
    token_list_.push_back(Token(TOKEN_ERROR, start_pos_, 0, std::nullopt));
  }
  }
}

void Lexer::makeNumberToken() {
  while (std::isdigit(peek_()) && !atEnd()) {
    advance_();
  }
  if (peek_() == '.' && std::isdigit(peekNext_())) {
    advance_();
    while (isdigit(peek_()) && !atEnd()) {
      advance_();
    }
  }

  int length = static_cast<int>(curr_pos_ - start_pos_);
  char *substr = reinterpret_cast<char *>(calloc(length + 2, sizeof(char)));
  memcpy(substr, start_pos_, length + 1);
  double number = strtod(start_pos_, nullptr);

  free(substr);
  token_list_.push_back(
      Token(TOKEN_NUMBER, start_pos_, length, std::optional<double>{number}));
}

} // namespace calculator::lexer
