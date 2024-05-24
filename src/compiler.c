#include "compiler.h"
#include <stdarg.h>
#include <stdlib.h>

struct lex_process_functions compiler_lex_functions = {
    .next_char = compiler_process_next_char,
    .peek_char = compiler_process_peek_char,
    .push_char = compiler_process_push_char
    };

int compile_file(const char *filename, const char *out_filename, int flags)
{

    struct compiler_process *process = complier_process_create(filename, out_filename, flags);
    
    if (!process)
        return COMPILER_FAILED_WITH_ERRORS;

    // perform lexical analysys
    printf("perform lexical analysys");

    struct lex_process *lex_process = lex_process_create(process, &compiler_lex_functions, NULL);
    if (!lex_process)
        return COMPILER_FAILED_WITH_ERRORS;

    printf("creating token list");

    if (lex(lex_process) != LEXICAL_ANALYSIS_ALL_OK)
        return COMPILER_FAILED_WITH_ERRORS;

    // perform parsing

    // perform code generation

    return COMPILER_FILE_COMPILED_OK;
}

void compiler_error(struct compiler_process *process, const char *msg, ...)
{
    va_list args;
    va_start(args, msg);
    vfprintf(stderr, msg, args);
    va_end(args);
    fprintf(stderr, "on line %i in col %i for the file %s", process->pos.line, process->pos.col, process->pos.filename);
    exit(-1);
}

void compiler_warning(struct compiler_process *process, const char *msg, ...)
{
    va_list args;
    va_start(args, msg);
    vfprintf(stderr, msg, args);
    va_end(args);
    fprintf(stderr, "on line %i in col %i for the file %s", process->pos.line, process->pos.col, process->pos.filename);
}