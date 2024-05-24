#ifndef LEXER_INTERNAL
#define LEXER_INTERNAL

#define LEX_GET_IF(buffer,c,exp)   \
    for(c = peekc(); exp ; c = peekc())\
    {                              \
        buffer_write(buffer,c);    \
        nextc();                   \
    }


char nextc();
char peekc();
void pushc(char c);

struct token* token_make_number_for_value(unsigned long number);
struct token* token_make_number();

const char* read_number_str();

unsigned long long read_number();

struct token* token_create(struct token* _token);

#endif