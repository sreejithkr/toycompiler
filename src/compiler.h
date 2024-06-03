#ifndef TOYCOMPILER_H
#define TOYCOMPILER_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define IF_STRING_EQUAL(str1, str2) \
    ((str1 != NULL && str2 != NULL) ? (strcmp(str1, str2) == 0) : 0)

enum {
    LEXICAL_ANALYSIS_ALL_OK,
    LEXICAL_ANALYSIS_INPUT_ERROR
};

enum {
    TOKEN_TYPE_IDENTIFIER,
    TOKEN_TYPE_KEYWORD,
    TOKEN_TYPE_OPERATOR,
    TOKEN_TYPE_SYMBOL,
    TOKEN_TYPE_NUMBER,
    TOKEN_TYPE_STRING,
    TOKEN_TYPE_COMMENT,
    TOKEN_TYPE_NEWLINE
};

enum {
    COMPILER_FILE_COMPILED_OK,
    COMPILER_FAILED_WITH_ERRORS
};

struct pos {
    int line;
    int col;
    const char* filename;
};


struct token {
    int type;
    int flags;
    struct pos pos;
    union  
    {
        char cval;
        const char* sval;
        unsigned int inum;
        unsigned long lnum;
        unsigned long long llnum;
        void* any;
    };
    // represents the state which say if there is whitespace between the current and next tocken.
    bool whitespaces;
    const char* between_brackets;

};

struct lex_process;
typedef char (*LEX_PROCESS_NEXT_CHAR)(struct lex_process* process);
typedef char (*LEX_PROCESS_PEEK_CHAR)(struct lex_process* process);
typedef void (*LEX_PROCESS_PUSH_CHAR)(struct lex_process* process,char c);

struct lex_process_functions {
    LEX_PROCESS_NEXT_CHAR next_char;
    LEX_PROCESS_PEEK_CHAR peek_char;
    LEX_PROCESS_PUSH_CHAR push_char;
};

struct lex_process
{
    struct pos pos;
    struct vector* tocken_vec;
    struct compiler_process* compiler;

    int current_expression_count;
    struct buffer* parentheses_buffer;
    struct lex_process_functions* function;

    void* private;
};






struct lex_process* lex_process_create(struct compiler_process* compiler, struct lex_process_functions* functions, void* private);
void lex_process_free(struct lex_process* process) ;
void* lex_process_private(struct lex_process* lex_process) ;
struct vector* lex_process_tockens(struct lex_process* lex_process);
int lex(struct lex_process* process);

struct compiler_process {
    //this define how a file is compiled
    int flags;

    struct pos pos;
    struct compile_process_input_file 
    {
        FILE* fp;
        const char* abs_path;
    } cfile;

    FILE *ofile;
};

struct compiler_process *complier_process_create(const char *filename, const char *filename_out, int flags);
char compiler_process_next_char(struct lex_process* lex_process);
char compiler_process_peek_char(struct lex_process* lex_process);
void compiler_process_push_char(struct lex_process* lex_process, char c);

int compile_file(const char* filename, const char* out_filename, int flags);
void compiler_error(struct compiler_process* process, const char* msg,...);
void compiler_warning(struct compiler_process *process, const char *msg, ...);
#endif