#include "compiler.h"
#include "helpers/buffer.h"
#include <string.h>
#include "helpers/vector.h"
#include "lexer_internal.h"

struct token* generate_number_token_for_value(unsigned long number) {
    return token_create(&(struct token){.type=TOKEN_TYPE_NUMBER,.llnum=number });
}

struct token* generate_number_token() {
    return generate_number_token_for_value(read_number());
}

const char* read_number_str() {
    const char* num = NULL;
    struct buffer* buffer = buffer_create();
    char c = peekc();
    LEX_GET_IF(buffer,c,c >= '0' && c <= '9');
    buffer_write(buffer,0x00);
    return buffer_ptr(buffer);
}

unsigned long long read_number(){
    const char* s = read_number_str();
    return atoll(s);
}