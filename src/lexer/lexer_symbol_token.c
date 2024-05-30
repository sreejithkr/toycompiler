#include "compiler.h"
#include "lexer_internal.h"

struct token* generage_symbol_token() {
    char c = nextc();
    if (c == ')'){
        lex_conclude_expresession_processing();
    }

    return token_create(&(struct token){.type=TOKEN_TYPE_SYMBOL,.cval=c});

}