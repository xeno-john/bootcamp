#include "p13.h"

int main(void)
{
    FILE                              *input_file = NULL;
    int                                 flag_in_menu = 1;
    int                                       option = 0;
    char                               file_name[256]={};
    unsigned int                     modify_position = 0;
    char                             *temp_buffer = NULL;
    unsigned int                     nr_deleted_char = 0;
    char *what_was_before = (char*)malloc(MAX_TEXT_SIZE);
    char *in_case_of_redo = (char*)malloc(MAX_TEXT_SIZE);


    do
    {
        printf("\nOptions:");
        printf("\n1.Open file.");
        printf("\n2.Write text at position.");
        printf("\n3.Delete text from position");
        printf("\n5.Undo last operation.");
        printf("\n5.Redo last undone operation.");
        printf("\n0.Exit.\n>");

        scanf("%d",&option); /* remains to be validated */
        
        switch(option)
        {
            case 1:
            {
                clearScreen();
                printf("Give the name of the file you want to open.\n>");
                
                getchar();

                if( NULL != fgets(file_name,256,stdin))
                {
                    
                    if('\n' == file_name[strlen(file_name)-1])
                    {
                        file_name[strlen(file_name)-1]='\0';
                    }

                    input_file = open_file(file_name);

                    if (NULL == input_file)
                    {
                        fprintf(stderr,"Failed to open file with given name.\n");
                        flag_in_menu = 0;
                    }
                    else
                    {
                        clearScreen();
                        printf("\n******************************************");
                        printf("\n*Succesfully opened file with given name.*\n");
                        printf("******************************************");
                    }
                    
                }

                break;
            }
            case 2:
            {
                if( NULL != input_file)
                {
                    fgets(what_was_before,MAX_TEXT_SIZE,input_file);
                    rewind(input_file);

                    clearScreen();
                    printf("What is the position where you want to modify the text at?\n>");
                    scanf("%u",&modify_position);

                    getchar();
                    clearScreen();
                    printf("\nWhat is the text you want to introduce?\n>");
                    
                    temp_buffer = (char*)malloc(MAX_TEXT_SIZE);

                    if( NULL != fgets(temp_buffer,MAX_TEXT_SIZE,stdin))
                    {
                        temp_buffer[strlen(temp_buffer)-1]='\0';
                        write_text_at_position(temp_buffer,modify_position,input_file,file_name);
                        clearScreen();
                        printf("\n****************************");
                        printf("\n*Succesfully modified file.*\n");
                        printf("****************************");

                        free(temp_buffer);
                        temp_buffer = NULL;
                    }

                }
                else
                {
                    fprintf(stderr,"File not open.\n");
                    flag_in_menu = 0;
                }
                
                break;
            }

            case 3:
            {
                if( NULL != input_file)
                {
                    fgets(what_was_before,MAX_TEXT_SIZE,input_file);
                    rewind(input_file);

                    clearScreen();
                    printf("What is the position where you want to delete the text at?\n>");
                    scanf("%u",&modify_position);

                    clearScreen();
                    printf("How many characters you want to delete?\n>");
                    scanf("%u",&nr_deleted_char);

                    delete_text_from_position(modify_position,nr_deleted_char,input_file,file_name);
                    
                    clearScreen();
                    printf("\n****************************");
                    printf("\n*Succesfully modified file.*\n");
                    printf("****************************");

                }
                else
                {
                    fprintf(stderr,"File not open.\n");
                    flag_in_menu = 0;
                }
                
                break;
            }

            case 4:
            {
                if( NULL != input_file)
                {
                    fgets(in_case_of_redo,MAX_TEXT_SIZE,input_file);
                    rewind(input_file);

                    undo_last_operation(what_was_before,input_file,file_name);
                    
                    clearScreen();
                    printf("\n****************************");
                    printf("\n*Succesfully modified file.*\n");
                    printf("****************************");

                }
                else
                {
                    fprintf(stderr,"File not open.\n");
                    flag_in_menu = 0;
                }
                
                break;
            }

            case 5:
            {
                if( NULL != input_file)
                {
                    fgets(what_was_before,MAX_TEXT_SIZE,input_file);
                    rewind(input_file);

                    undo_last_operation(in_case_of_redo,input_file,file_name);
                    
                    clearScreen();
                    printf("\n****************************");
                    printf("\n*Succesfully modified file.*\n");
                    printf("****************************");

                }
                else
                {
                    fprintf(stderr,"File not open.\n");
                    flag_in_menu = 0;
                }
                
                break;
            }

            case 0:
            {
                flag_in_menu = 0;
                break;
            }

            default:
            {
                fprintf(stderr,"Selected option doesn't actually exist.\n");
                flag_in_menu = 0;
                break;
            }
        }
        
    } while (1 == flag_in_menu);

    free(what_was_before);
    free(in_case_of_redo);
    free(input_file);

    what_was_before = NULL;
    in_case_of_redo = NULL;
    input_file = NULL;
    

    return 0;    
}