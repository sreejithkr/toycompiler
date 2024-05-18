#ifndef TOYCOMPILER_H
#define TOYCOMPILER_H

#include <stdio.h>
#include <stdbool.h>


struct pos {
    int line;
    int col;
    const char* filename;
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

struct token {
    int type;
    int flags;

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

enum {
    COMPILER_FILE_COMPILED_OK,
    COMPILER_FAILED_WITH_ERRORS
};

struct compiler_process 
{
    //this define how a file is compiled
    int flags;

    struct compile_process_input_file 
    {
        FILE* fp;
        const char* abs_path;
    } cfile;

    FILE *ofile;
};

int compile_file(const char* filename, const char* out_filename, int flags);
struct compiler_process *complier_process_create(const char *filename, const char *filename_out, int flags);

#endif