#include "compiler.h"
#include "lexer_internal.h"

struct token* generate_newline_token() {
    char c = nextc();
    return token_create(&(struct token){.type=TOKEN_TYPE_NEWLINE});
}