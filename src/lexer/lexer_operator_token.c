#include <stdbool.h>
#include "./helpers/buffer.h"
#include "lexer_internal.h"
#include "compiler.h"
#include <string.h>


bool is_single_character_operator(char op) {
    return op == '(' || \
           op == '[' || \ 
           op == ',' || \
           op == '.' || \
           op == '*' || \
           op == '?';
}

bool is_single_character_pair_operator(char op) {
    return op == '+' || \
           op == '-' || \ 
           op == '/' || \
           op == '*' || \
           op == '=' || \
           op == '>' || \ 
           op == '<' || \
           op == '|' || \
           op == '&' || \           
           op == '^' || \ 
           op == '%' || \
           op == '!' || \
           op == '(' || \
           op == '[' || \ 
           op == ',' || \
           op == '.' || \
           op == '~' || \
           op == '?';
}

bool is_valid_op(const char* op) {
    if (!op) {
        return false;
    }
    return IF_STRING_EQUAL(op, "+") ||
           IF_STRING_EQUAL(op, "-") ||
           IF_STRING_EQUAL(op, "*") ||
           IF_STRING_EQUAL(op, "/") ||
           IF_STRING_EQUAL(op, "!") ||
           IF_STRING_EQUAL(op, "^") ||
           IF_STRING_EQUAL(op, "+=") ||
           IF_STRING_EQUAL(op, "-=") ||
           IF_STRING_EQUAL(op, "*=") ||
           IF_STRING_EQUAL(op, "/=") ||
           IF_STRING_EQUAL(op, ">>") ||
           IF_STRING_EQUAL(op, "<<") ||
           IF_STRING_EQUAL(op, ">=") ||
           IF_STRING_EQUAL(op, "<=") ||
           IF_STRING_EQUAL(op, ">") ||
           IF_STRING_EQUAL(op, "<") ||
           IF_STRING_EQUAL(op, "||") ||
           IF_STRING_EQUAL(op, "&&") ||
           IF_STRING_EQUAL(op, "|") ||
           IF_STRING_EQUAL(op, "++") ||
           IF_STRING_EQUAL(op, "=") ||
           IF_STRING_EQUAL(op, "!=") ||
           IF_STRING_EQUAL(op, "==") ||
           IF_STRING_EQUAL(op, "->") ||
           IF_STRING_EQUAL(op, "(") ||
           IF_STRING_EQUAL(op, "[") ||
           IF_STRING_EQUAL(op, ",") ||
           IF_STRING_EQUAL(op, ".") ||
           IF_STRING_EQUAL(op, "...") ||
           IF_STRING_EQUAL(op, "~") ||
           IF_STRING_EQUAL(op, "?") ||
           IF_STRING_EQUAL(op, "%");
}

void step_back_character_for_operator_token_being_processed(struct buffer* buffer){
    const char* data = buffer_ptr(buffer);
    int len = buffer->len;
    for(int i= len-1; i>=1; i--){
        const char c = data[i];
        if(c == 0x00) {
            continue;
        }
        pushc(c);
    }


}

const char* read_op() {
    char op = nextc();

    printf("reached read_op");
    bool single_operator = true;
    struct buffer* buffer = buffer_create();
    buffer_write(buffer,op);
    if (!is_single_character_operator(op)){
        op = peekc();
        if (is_single_character_pair_operator(op)){
            buffer_write(buffer,op);
            nextc();
            single_operator = false;
        }
    }
 
    buffer_write(buffer,0x00);
      
    char* ptr = buffer_ptr(buffer);
    if(!single_operator) {
       
        if(!is_valid_op(ptr)) {
            step_back_character_for_operator_token_being_processed(buffer);
            ptr[1] = 0x00; 
        }

    } 
    else if(!is_valid_op(ptr)) {
        lexer_error("The operator %s is not valid", ptr);
    }
    return ptr;
}

struct token* generate_operator_token() {
    char op = peekc();
    char*  c = read_op();
    printf("\n char value %s ",c);
    struct token* token =  token_create(&(struct token){.type=TOKEN_TYPE_OPERATOR,.sval=c});
    if (op == '('){
        lex_intiate_expresession_processing();
    }
    return token;
}