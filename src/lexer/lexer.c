#include "compiler.h"
#include "helpers/buffer.h"
#include <string.h>
#include "helpers/vector.h"
#include "lexer_internal.h"
#include <stdarg.h>


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

void lexer_error(const char* msg,...) {
    va_list args;
    va_start(args,msg);
    compiler_error(lex_process.compiler,msg,args);    
    va_end(args);
}

void print_token(struct token token){
    printf("\ntoken type %i ", token.type);

    switch (token.type)
    {
    case TOKEN_TYPE_NUMBER:
         printf("\ntoken %llu:\n", token.llnum);
        break;


    case TOKEN_TYPE_KEYWORD:
    case TOKEN_TYPE_IDENTIFIER:
    case TOKEN_TYPE_OPERATOR:
    case TOKEN_TYPE_STRING:
         printf("\ntoken %s:\n", token.sval);
        break;
    case TOKEN_TYPE_SYMBOL:
         printf("\ntoken %c:\n", token.cval);
         break;
    case TOKEN_TYPE_NEWLINE:
     printf("\ntoken newline \n");
         break;
    default:
        break;
    }
}

struct token* token_create(struct token* _token){
    memcpy(&tmp_token,_token,sizeof(struct token));
    tmp_token.pos = lex_file_position();
    return &tmp_token;
}


struct token* lexer_last_token(){
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
    struct token* temp = NULL;
    struct token* token = NULL;

    char c = peekc();
        printf("\n INSIDE read_next_token %c \n",c);

    switch (c)  
    {
    NUMERIC_CASE:
     token = generate_number_token();
    break;

    OPERATOR_CASE_EXCLUDING_DIVISION:
    printf("\n INSIDE OPERATOR_CASE_EXCLUDING_DIVISION %c",c);
        temp = generate_include_string_token();
        if (temp == NULL) {
            token = generate_operator_token();
        } else {
             token = temp;
        }   
    break;

    SYMBOL_CASE:
        token = generage_symbol_token();
    break;

    case '"':
     token = generate_string_token('\"','\"');
    break;

    case '\n':
     token = generate_newline_token();
    break;
    
    case ' ':
    case '\t':
        token = handle_whitespace();
    break;

    case EOF:
        //finished lexical analysis on the file 
        break;
    
    default:
        token = generate_identifier_token();
        if (!token) {
             compiler_error(lex_process.compiler,"Unexpected token\n");
        }
        break;
    }

    return token;
}

void lex_intiate_expresession_processing() {
    lex_process.current_expression_count++;
    if (lex_process.current_expression_count == 1) {
        lex_process.parentheses_buffer = buffer_create();
    }
}

void lex_conclude_expresession_processing() {
    lex_process.current_expression_count--;
    if (lex_process.current_expression_count < 0) {
        lex_process.parentheses_buffer = buffer_create();
    }
}
bool is_lex_expression_being_processed() {
    return lex_process.current_expression_count > 0;
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
       print_token(*token);
      
    }
    
    return LEXICAL_ANALYSIS_ALL_OK;
}


/**
 * 
 *     TOKEN_TYPE_IDENTIFIER,
    TOKEN_TYPE_KEYWORD,
    TOKEN_TYPE_OPERATOR,
    TOKEN_TYPE_SYMBOL,
    TOKEN_TYPE_NUMBER,
    TOKEN_TYPE_STRING,
    TOKEN_TYPE_COMMENT,
    TOKEN_TYPE_NEWLINE
*/