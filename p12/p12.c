#include "p12.h"
#include<string.h>

/**
 * @fn NODE* insert_in_list(NODE* list_head, char to_be_inserted[])
 * @brief the function that inserts words in the list. 
 * @param list_head[in] - pointer to the first element of the list
 * @param to_be_inserted[in] - static char array in which we stock the word we're to introduce
 * @return NODE* the new first element of the list, as insertion is made in the FRONT 
 **/
NODE* insert_in_list(NODE* list_head, char to_be_inserted[])
{
    int                    continuation_flag = 1;
    NODE *node_to_be_inserted = init_list_node();

    if (NULL != node_to_be_inserted)
    {
        strcpy(node_to_be_inserted->content.word,to_be_inserted);

        if (NULL != list_head)
        {
            NODE* temporary = list_head;

            while (NULL != temporary)
            {
                
                if (0 == strcmp(node_to_be_inserted->content.word,temporary->content.word))
                {
                    continuation_flag = 0; /* we found the inserted word in the list */
                    temporary->content.nr_of_occurences++; /* therefore, we increment the number of occurences */
                    break; /* we stop here since a word is unique in the list */
                }

                temporary=temporary->next;
            }
            
            if (1 == continuation_flag)
            {
                node_to_be_inserted->next = list_head;
                list_head = node_to_be_inserted;
            }

        }
        else
        {
            node_to_be_inserted->next = list_head;
            list_head = node_to_be_inserted;
        }

    }
    else
    {
        fprintf(stderr,"Failed to allocate memory for the node that follows to be inserted.\n");
    }

    return list_head;
     
}

/**
 * @fn void traverse(NODE* list_head)
 * @brief traverses the list and prints the words it contains with their number of occurences
 * @param list_head[in] pointer to the first element of the list
 * @return void
 **/
void traverse(NODE* list_head)
{
    NODE* temporary = list_head;

    while (NULL != temporary)
    {
        if (1 != temporary->content.nr_of_occurences)
        {
            DBG_PRINT(5,"%d occurences of '%s'\n",temporary->content.nr_of_occurences,temporary->content.word);
        }
        else
        {
            DBG_PRINT(5,"%d occurence of '%s'\n",temporary->content.nr_of_occurences,temporary->content.word);
        }
        temporary=temporary->next;
    }

    free(temporary);
    temporary = NULL;

    printf("\n");
}

/**
 * @fn NODE* init_list_node()
 * @brief returns a freshly allocated&initialised list node
 * @return NODE* the list node that is allocated and semi-initialised
 **/
NODE* init_list_node()
{
    NODE *node_to_be_inserted = (NODE*)malloc(sizeof(NODE));

    if(NULL != node_to_be_inserted)
    {
        node_to_be_inserted->content.nr_of_occurences = 1;
    }
    
    /* returns null and is verified in caller function if it fails to allocate */
    return node_to_be_inserted;
}