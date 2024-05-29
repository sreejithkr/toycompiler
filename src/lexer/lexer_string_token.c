#include "lexer_internal.h"
#include "../helpers/buffer.h"
#include "compiler.h"
#include "assert.h"

struct token* generate_string_token(char start_delimit,char end_delimit){
    struct buffer* buf = buffer_create();
    assert(nextc() == start_delimit);
    char c = nextc();
    for(; c != end_delimit && c != EOF; c = nextc()){
        if (c == '\\'){
            //to be handled later section
            continue;
        }
        buffer_write(buf,c);
    }

    buffer_write(buf,0x00);

    return token_create(&(struct token){.type=TOKEN_TYPE_STRING,.sval=buffer_ptr(buf)});
}

struct token* generate_include_string_token(){
                printf("\n before op in generate_include_string_token");

    char op = peekc();

    if(op == '<') {
        struct token* last_token = lexer_last_token();
        if(is_token_a_keyword(last_token,"include")){
            return generate_string_token('<','>');
        }
    }
                printf("\n after if generate_include_string_token");

    return NULL;

}
