#include "compiler.h"

int compile_file(const char* filename, const char* out_filename, int flags)
{
    struct compiler_process* process =  complier_process_create(filename,out_filename,flags);
    if (!process)
        return COMPILER_FAILED_WITH_ERRORS;

    //perform lexical analysys

    //perform parsing

    //perform code generation 

    return COMPILER_FILE_COMPILED_OK;
}