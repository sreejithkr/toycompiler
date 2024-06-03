#include "lexer_internal.h"
#include "./helpers/buffer.h"
#include "compiler.h"
#include <ctype.h>

struct token *create_identifier_token() {
    struct buffer* buffer = buffer_create();
    char c = 0;
    LEX_GET_IF(buffer,c, (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_' );
    buffer_write(buffer,0x00);
    //check if this is a keyword

    return token_create(&(struct token){.type=TOKEN_TYPE_IDENTIFIER,.sval=buffer_ptr(buffer)});
}

struct token* generate_identifier_token() {
    char c = peekc();
    if(isalpha(c) || c == '_'){
        return create_identifier_token();
    }
}