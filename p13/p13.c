#include "p13.h"
#include <errno.h>



/**
 * @fn open_file(char file_name[])
 * @brief opens a FILE* with the given name
 * @param file_name[] - an array that contains the name of the file wished to be open.
 * @return FILE* file_to_be_opened - pointer to the opened file of the given name
 **/
FILE* open_file(char file_name[])
{
    FILE* file_to_be_opened = fopen(file_name,"r+");
    /* w+ - Open for reading and writing. The file is created if it
     * does not exist, otherwise it is truncated. The stream 
     * is positioned at the beginning of the file. 
     */
    
    if(NULL == file_to_be_opened)
    {
        fprintf(stderr,"Failed to open given file.\n");
    }

    return file_to_be_opened;
}

/**
 * @fn void print_file_content(FILE* file)
 * @brief prints the content of a file
 * @param file pointer to the file of which the user wants to print the content
 * @return void
 **/
void print_file_content(FILE* file)
{
    char temporary_char = fgetc(file);

    while ( EOF !=  temporary_char )
    {
        printf("%c",temporary_char);
        temporary_char = fgetc(file);        
    }

    fseek(file, 0, SEEK_SET);
    printf("\n");

}

/**
 * @fn void write_text_at_position(char text[], int position, FILE* file, char* file_name)
 * @brief writes a given text at a user set position
 * @param text[] - the given text
 * @param position - the given position
 * @param file - the file to be modified
 * @param file_name - the file_name ( used for freopen )
 * @return void
 **/
void write_text_at_position(char text[], int position, FILE* file, char* file_name)
{
    char* file_content_buffer = (char*)malloc(MAX_TEXT_SIZE);

    file = freopen(file_name,"r+",file);

    if (NULL == file_content_buffer)
    {
        fprintf(stderr,"Failed to allocate memory for the file_content_buffer.\n");
    }
    else
    {
        fseek(file,position,SEEK_SET);
        fgets(file_content_buffer,MAX_TEXT_SIZE,file);
        fseek(file,position,SEEK_SET);
        fprintf(file,"%s",text);
        fseek(file,position+strlen(text),SEEK_SET);
        fprintf(file,"%s",file_content_buffer);
        rewind(file);
    }

    free(file_content_buffer);
    file_content_buffer = NULL;

}

/**
 * @fn void delete_text_from_position(int position, int nr_of_deleted_characters, FILE *file, char* file_name)
 * @brief deletes given number of characters from given position of the file
 * @param position - the given position
 * @param nr_of_deleted_characters - how many characters are to be deleted
 * @param file - the file to be modified
 * @param file_name - the file_name ( used for freopen )
 * @return void
 **/
void delete_text_from_position(int position, int nr_of_deleted_characters, FILE *file, char* file_name)
{
    char* file_content_buffer = (char*)malloc(MAX_TEXT_SIZE);

    file = freopen(file_name,"r+",file);

    if (NULL == file_content_buffer)
    {
        fprintf(stderr,"Failed to allocate memory for the file_content_buffer.\n");
    }
    else
    {

        fgets(file_content_buffer,MAX_TEXT_SIZE,file);
    
        if (strlen(file_content_buffer)>nr_of_deleted_characters + position)
        {
            strcpy(file_content_buffer + position, file_content_buffer + position + nr_of_deleted_characters);
        }
        else
        {
            file_content_buffer[position]='\0';
        }

        file = freopen(file_name,"w",file);

        fprintf(file,"%s",file_content_buffer);
        rewind(file);

        free(file_content_buffer);
        file_content_buffer = NULL;
    }

}


/**
 * @fn void undo_last_operation(char what_was_before[], FILE* file, char *file_name)
 * @brief undoes the last operation selected in the menu - also used for redo ( with a different given buffer )
 * @param what_was_before[] - a buffer that stocks what was before (what text) the last done operation in the menu.
 * @param file - the file to be modified
 * @param file_name - the file_name ( used for freopen )
 * @return void
 **/
void undo_last_operation(char what_was_before[], FILE* file, char *file_name)
{
    file = freopen(file_name,"w",file);

    fprintf(file,"%s",what_was_before);
    rewind(file);
}