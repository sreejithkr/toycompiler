#include "compiler.h"
#include "helpers/buffer.h"
#include <string.h>
#include "helpers/vector.h"
#include "lexer_internal.h"


static struct lex_process lex_process;
static struct token tmp_token;
struct token* read_next_token();

static struct pos lex_file_position() {
    return lex_process.pos;
}

char nextc() {
    char c = lex_process.function->next_char(&lex_process);
    lex_process.pos.col += 1;    
     if (c == '\n') {
         lex_process.pos.col = 1;
         lex_process.pos.line += 1;
     }
    return c;
}
char peekc(){
    return lex_process.function->peek_char(&lex_process);
}

void pushc(char c){
    lex_process.function->push_char(&lex_process,c);
}


struct token* token_create(struct token* _token){
    memcpy(&tmp_token,_token,sizeof(struct token));
    tmp_token.pos = lex_file_position();
    return &tmp_token;
}


static struct token* lexer_last_token(){
    return vector_back_or_null(lex_process.tocken_vec);
}
static struct token* handle_whitespace() {
    struct token* last_token = lexer_last_token();
    if(last_token)
        last_token->whitespaces = true;
    nextc();
    return read_next_token();
}




struct token* read_next_token() {

    struct token* token = NULL;

    char c = peekc();
    switch (c)  
    {
    NUMERIC_CASE:
     token = token_make_number();
    break;

    case ' ':
    case '\t':
        token = handle_whitespace();
    break;

    case EOF:
        //finished lexical analysis on the file 
        break;
    
    default:
        compiler_error(lex_process.compiler,"Unexpected token\n");
        break;
    }

    return token;
}

int lex(struct lex_process* process) {
   
    process->current_expression_count = 0;
    process->parentheses_buffer = NULL;
    lex_process = *process;
    process->pos.filename = process->compiler->cfile.abs_path;
   
    struct token* token = read_next_token();
    while (token)
    {
        vector_push(process->tocken_vec,token);
        token = read_next_token();
    }

    printf("\n process %i \n", process->tocken_vec->count);
       printf("Printing contents of the vector:\n");
    for (int i = 0; i < vector_count(process->tocken_vec); i++) {
        struct token *token = vector_at(process->tocken_vec, i);
        printf("\ntoken %llu:\n", token->llnum);
      
    }
    
    return LEXICAL_ANALYSIS_ALL_OK;
}