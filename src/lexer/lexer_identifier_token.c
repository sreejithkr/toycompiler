#include "lexer_internal.h"
#include "./helpers/buffer.h"
#include "compiler.h"
#include <ctype.h>

bool is_keyword(const char* str);

struct token *create_identifier_token() {
    struct buffer* buffer = buffer_create();
    char c = 0;
    LEX_GET_IF(buffer,c, (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_' );
    buffer_write(buffer,0x00);
    //check if this is a keyword
    if(is_keyword(buffer_ptr(buffer))){
          return token_create(&(struct token){.type=TOKEN_TYPE_KEYWORD,.sval=buffer_ptr(buffer)});
    }

    return token_create(&(struct token){.type=TOKEN_TYPE_IDENTIFIER,.sval=buffer_ptr(buffer)});
}

struct token* generate_identifier_token() {
    char c = peekc();
    if(isalpha(c) || c == '_'){
        return create_identifier_token();
    }
}

bool is_keyword(const char* str) {
    return IF_STRING_EQUAL(str,"unsigned") ||
             IF_STRING_EQUAL(str,"signed") ||
             IF_STRING_EQUAL(str,"char") ||
             IF_STRING_EQUAL(str,"short") ||
             IF_STRING_EQUAL(str,"int") ||
             IF_STRING_EQUAL(str,"long") ||             
             IF_STRING_EQUAL(str,"float") ||
             IF_STRING_EQUAL(str,"double") ||
             IF_STRING_EQUAL(str,"void") ||
             IF_STRING_EQUAL(str,"struct") ||
             IF_STRING_EQUAL(str,"union") ||
             IF_STRING_EQUAL(str,"static") ||
             IF_STRING_EQUAL(str,"__ignore_typecheck") ||
             IF_STRING_EQUAL(str,"return") ||
             IF_STRING_EQUAL(str,"include") ||
             IF_STRING_EQUAL(str,"sizeof") ||
             IF_STRING_EQUAL(str,"if") ||
             IF_STRING_EQUAL(str,"else") ||
             IF_STRING_EQUAL(str,"while") ||
             IF_STRING_EQUAL(str,"for") ||
             IF_STRING_EQUAL(str,"do") ||
             IF_STRING_EQUAL(str,"break") ||
             IF_STRING_EQUAL(str,"continue") ||
             IF_STRING_EQUAL(str,"switch") ||
             IF_STRING_EQUAL(str,"case") ||
             IF_STRING_EQUAL(str,"default") ||
             IF_STRING_EQUAL(str,"goto") ||
             IF_STRING_EQUAL(str,"typedef") ||
             IF_STRING_EQUAL(str,"const") ||
             IF_STRING_EQUAL(str,"extern") ||
             IF_STRING_EQUAL(str,"restrict");          
             
}            