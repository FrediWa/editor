#include <unistd.h>

#include "includes/io.h"

char read_key() 
{
    char c;
    read(STDIN_FILENO, &c, 1);
    return c;
}

int open_file(char* filename, EditorContext* ctx)
{
    // fopen
    // if no file, create a blank editor context
    ctx->file_name_given = 0;
    return(0);
}

int write_file(EditorContext* ctx) 
{

    if (ctx->file_name_given == 0)
    {
        // write_error("You must name the newly created file")
        return(1);
    }
    
    //fwrite
    // handle errors
    return(0);
}