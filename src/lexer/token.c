#include "lexer_internal.h"
#include "compiler.h"
#include <stdbool.h>

bool is_token_a_keyword(struct token* token, const char* value){
    return token->type == TOKEN_TYPE_IDENTIFIER && IF_STRING_EQUAL(token->sval,value);
}