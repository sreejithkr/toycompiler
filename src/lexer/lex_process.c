#include "compiler.h"
#include "helpers/vector.h"
#include <stdlib.h>

struct lex_process* lex_process_create(struct compiler_process* compiler, struct lex_process_functions* functions, void* private){
    struct lex_process* process = calloc(1, sizeof(struct lex_process));
    process->function = functions;
    process->compiler = compiler;
    process->tocken_vec = vector_create(sizeof(struct token));
    process->private = private;
    process->pos.line = 1;
    process->pos.col = 1;
    return process;
}

void lex_process_free(struct lex_process* process) {
    vector_free(process->tocken_vec);
    free(process);
}

void* lex_process_private(struct lex_process* lex_process) {
    return lex_process->private;
}

struct vector* lex_process_tockens(struct lex_process* lex_process){
    return lex_process->tocken_vec;
}


