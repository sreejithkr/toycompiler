#include <stdio.h>
#include "helpers/vector.h"
#include "compiler.h"

int main() {
    int res = compile_file("./test.c","./test",0);

    if (res == COMPILER_FILE_COMPILED_OK)
    {
        printf("Compilation successful");
        
    }
    else if(res == COMPILER_FAILED_WITH_ERRORS) 
    {
        printf("Compilation failed");

    }
    else 
    {
         printf("Compilation failed with unknow error");

    }

    // printf("hello world");
    // struct vector* vec = vector_create(sizeof(int));
    // int x = 50;
    // vector_push(vec,&x);
    // x = 20;
    // vector_push(vec,&x);
    // vector_set_peek_pointer(vec,0);
    // int* ptr = vector_peek(vec);
    // while (ptr)
    // {
    //     printf("%i\n",*ptr);
    //     ptr = vector_peek(vec);
    // }
    return 0;
}