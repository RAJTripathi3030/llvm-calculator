#include <iostream>
#include "lexer.h"

using namespace calculator::lexer;
int32_t main() {
  std::string source = "1.11+11-21/";
  Lexer lexer = Lexer(source);
  lexer.lex_all();

  auto tl = lexer.get_tokens();

  for (auto &t: tl) {
    t.DumpToken();
  }

  return 0;

}
