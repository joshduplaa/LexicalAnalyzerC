# LexicalAnalyzerC
A lexical analyzer in C that can identify lexemes and tokens found in a source code(Dcooke) file provided by the user. Once the analyzer has identified the lexemes of the language and matched them to a token group, the program should print each lexeme / token pair to the screen. 
The source code file(test.dc) is written in a language I called "Dcooke".
Dcooke follows these BNF grammar rules

P ::= S __
S ::= V:=E | read(V) | write(V) | while (C) do S od | O | S;S   __
C ::= E < E | E > E | E = E | E != E | E <= E | E >= E  __
E ::= T | E + T | E - T __
T ::= F | T * F | T / F __
F ::= (E) | O | N | V   __
O ::= V++ | V-- | ++V | --V __
V ::= a | b | ... | y | z | aV | bV | ... | yV | zV __
N ::= 0 | 1 | ... | 8 | 9 | 0 N | 1N | ... | 8N | 9N    __