#ifndef LEXER_INTERNAL
#define LEXER_INTERNAL
#include <stdbool.h>

#define LEX_GET_IF(buffer, c, exp)      \
    for (c = peekc(); exp; c = peekc()) \
    {                                   \
        buffer_write(buffer, c);        \
        nextc();                        \
    }

#define NUMERIC_CASE \
    case '0':        \
    case '1':        \
    case '2':        \
    case '3':        \
    case '4':        \
    case '5':        \
    case '6':        \
    case '7':        \
    case '8':        \
    case '9'

#define OPERATOR_CASE_EXCLUDING_DIVISION \
    case '+':                            \
    case '-':                            \
    case '*':                            \
    case '>':                            \
    case '<':                            \
    case '^':                            \
    case '%':                            \
    case '!':                            \
    case '=':                            \
    case '~':                            \
    case '|':                            \
    case '&':                            \
    case '(':                            \
    case '[':                            \
    case ',':                            \
    case '.':                            \
    case '?'

#define SYMBOL_CASE \
    case '{':        \
    case '}':        \
    case ':':        \
    case ';':        \
    case '#':        \
    case '\\':        \
    case ')':        \
    case ']'        


char nextc();
char peekc();
void pushc(char c);

void lex_intiate_expresession_processing();
void lex_conclude_expresession_processing();
bool is_lex_expression_being_processed();
struct token* lexer_last_token();
struct token *generate_number_token_for_value(unsigned long number);
struct token *generate_number_token();
struct token *generate_identifier_token();

const char *read_number_str();
unsigned long long read_number();

struct token *generate_string_token(char start_delimit, char end_delimit);

struct token* generate_include_string_token();


struct token* generate_operator_token();
struct token* generage_symbol_token();


struct token *token_create(struct token *_token);

void lexer_error(const char* msg,...);

bool is_token_a_keyword(struct token* token, const char* value);

#endif