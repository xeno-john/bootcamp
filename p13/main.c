#include "p13.h"

int main(void)
{
    unsigned int                        flag_in_menu = 1;
    unsigned int                   entered_file_flag = 0;
    unsigned int    performed_at_least_one_operation = 0;
    unsigned int                      performed_undo = 0;
    unsigned int                     modify_position = 0;
    unsigned int                              option = 0;
    unsigned int                     nr_deleted_char = 0;
    char                               file_name[256]={};
    char                             *temp_buffer = NULL;
    char *previous_content = (char*)malloc(MAX_TEXT_SIZE);
    char *in_case_of_redo = (char*)malloc(MAX_TEXT_SIZE);
    FILE                              *input_file = NULL;

    if (NULL == previous_content || NULL == in_case_of_redo)
    {
        fprintf(stderr,"Failed to allocated previous_content | in_case_of_redo.\n");
    }
    else
    {
    
        do
        {
            printf("\nOptions:");
            printf("\n1.Open file.");
            printf("\n2.Write text at position.");
            printf("\n3.Delete text from position");
            printf("\n4.Undo last operation.");
            printf("\n5.Redo last undone operation.");
            printf("\n0.Exit.\n>");

            if (1 == scanf("%d",&option))
            {        
                switch(option)
                {
                    case OPEN_FILE:
                    {

                        if (0 == entered_file_flag)
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
                                    entered_file_flag = 1;
                                }
                                
                            }

                        }
                        else
                        {
                            printf("\n**********");
                            printf("\n*WARNING.*\n");
                            printf("**********");
                            printf("\nYou've already entered a file.\n");
                        }
                        
                        break;
                    }
                    case WRITE_AT_POSITION:
                    {
                        input_file = freopen(file_name,"r+",input_file);

                        if( NULL != input_file)
                        {

                            if( NULL != fgets(previous_content,MAX_TEXT_SIZE,input_file))
                            {
                                rewind(input_file);
                            }
                            else
                            {
                                fprintf(stderr,"Failed to read input at line %d from file %s.\n",__LINE__,__FILE__);
                            }
                            

                            clearScreen();
                            printf("What is the position where you want to modify the text at?\n>");
                            scanf("%u",&modify_position);

                            getchar();
                            clearScreen();
                            printf("\nWhat is the text you want to introduce?\n>");
                            
                            temp_buffer = (char*)malloc(MAX_TEXT_SIZE);

                            if( NULL != fgets(temp_buffer,MAX_TEXT_SIZE,stdin))
                            {

                                if ('\n' == temp_buffer[strlen(temp_buffer)-1])
                                {
                                    temp_buffer[strlen(temp_buffer)-1]='\0';
                                }
                                
                                write_text_at_position(temp_buffer,modify_position,input_file,file_name);
                                performed_at_least_one_operation = 1;
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
                            fprintf(stderr,"Error when reopening file or file was not given.\nLine:%d, file:%s.\n",__LINE__,__FILE__);
                            flag_in_menu = 0;
                        }
                        
                        break;
                    }

                    case DELETE_FROM_POSITION:
                    {
                        input_file = freopen(file_name,"r+",input_file);

                        if( NULL != input_file)
                        {

                            if( NULL != fgets(previous_content,MAX_TEXT_SIZE,input_file))
                            {
                                rewind(input_file);
                            }
                            else
                            {
                                fprintf(stderr,"Failed to read input at line %d from file %s.\n",__LINE__,__FILE__);
                            }

                            clearScreen();
                            printf("What is the position where you want to delete the text at?\n>");
                            scanf("%u",&modify_position);

                            clearScreen();
                            printf("How many characters you want to delete?\n>");
                            scanf("%u",&nr_deleted_char);

                            delete_text_from_position(modify_position,nr_deleted_char,input_file,file_name);

                            performed_at_least_one_operation = 1;
                            
                            clearScreen();
                            printf("\n****************************");
                            printf("\n*Succesfully modified file.*\n");
                            printf("****************************");

                        }
                        else
                        {
                            fprintf(stderr,"Error when reopening file or file was not given.\nLine:%d, file:%s.\n",__LINE__,__FILE__);
                            flag_in_menu = 0;
                        }
                        
                        break;
                    }

                    case UNDO:
                    {
                        if( NULL != input_file)
                        {
                            
                            if (1 == performed_at_least_one_operation && 0 == performed_undo)
                            {
                                
                                input_file = freopen(file_name,"r+",input_file);
                                /* the undo function reopens the file in write mode in order to delete all of its content
                                * and to print what is in a buffer in the file
                                * so, added freopen in read+ mode to make possible the use of fgets
                                * following if statements we're used to diagnose why fgets was not reading anything
                                */                                           
                                
                                if( NULL == fgets(in_case_of_redo,MAX_TEXT_SIZE,input_file))
                                {

                                    if (ferror(input_file))
                                    {
                                        perror("Following error occured:");
                                    }

                                    fprintf(stderr,"Failed to read in_case_of_redo from input_file.\n");
                                }

                                rewind(input_file);
                                undo_last_operation(previous_content,input_file,file_name);
                                clearScreen();
                                printf("\n****************************");
                                printf("\n*Succesfully modified file.*\n");
                                printf("****************************");

                                performed_undo = 1;
                                
                            }
                            else
                            {
                                printf("\n**********");
                                printf("\n*WARNING.*\n");
                                printf("**********");
                                printf("\nYou have to perform at least one operation before opting to undo.\n");
                            }
                            

                        }
                        else
                        {
                            fprintf(stderr,"Error when reopening file or file was not given.\nLine:%d, file:%s.\n",__LINE__,__FILE__);
                            flag_in_menu = 0;
                        }
                        
                        break;
                    }

                    case REDO:
                    {
                        input_file = freopen(file_name,"r+",input_file);

                        if( NULL != input_file)
                        {
                            
                            if (1 == performed_undo)
                            {

                                if( NULL == fgets(previous_content,MAX_TEXT_SIZE,input_file))
                                {

                                    if (ferror(input_file))
                                    {
                                        perror("Following error occured:");
                                    }

                                    fprintf(stderr,"Failed to read previous_content when redo-ing from input_file.\n");
                                }
                                
                                rewind(input_file);

                                undo_last_operation(in_case_of_redo,input_file,file_name);
                                    
                                clearScreen();
                                printf("\n****************************");
                                printf("\n*Succesfully modified file.*\n");
                                printf("****************************");
                                performed_undo = 0;

                            }
                            else
                            {
                                printf("\n**********");
                                printf("\n*WARNING.*\n");
                                printf("**********");
                                printf("\nYou have to undo before trying to redo.\n");
                            }
                            

                        }
                        else
                        {
                            fprintf(stderr,"Error when reopening file or file was not given.\nLine:%d, file:%s.\n",__LINE__,__FILE__);
                            flag_in_menu = 0;
                        }
                        
                        break;
                    }

                    case EXIT:
                    {
                        flag_in_menu = 0;

                        if (NULL != input_file)
                        {
                            fclose(input_file);
                        }

                        break;
                    }

                    default:
                    {
                        fprintf(stderr,"Selected option doesn't actually exist.\n");
                        flag_in_menu = 0;
                        
                        if (NULL != input_file)
                        {
                            fclose(input_file);
                        }

                        break;
                    }
                }
            }
            else
            {
                fprintf(stderr,"Please make sure that what you enter as an option is actually an integer.\n");
                flag_in_menu = 0;
            }
            
            
        } while (1 == flag_in_menu);

    }

    free(previous_content);
    free(in_case_of_redo);

    previous_content = NULL;
    in_case_of_redo = NULL;
    input_file = NULL;
    
    if (NULL != input_file)
    {
        fclose(input_file);
        input_file = NULL;
    }
    
    return 0;    
}