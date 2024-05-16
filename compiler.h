#ifndef TOYCOMPILER_H
#define TOYCOMPILER_H

#include <stdio.h>

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