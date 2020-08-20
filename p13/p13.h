#ifndef P13_H_
#define P13_H_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "../DBG_PRINT.h"

#define MAX_TEXT_SIZE 16384
#define EXIT 0
#define OPEN_FILE 1
#define WRITE_AT_POSITION 2
#define DELETE_FROM_POSITION 3
#define UNDO 4
#define REDO 5

FILE* open_file(char file_name[]);
void print_file_content(FILE* file);
void write_text_at_position(char text[], int position, FILE* file, char *file_name);
void delete_text_from_position(int position, int nr_of_deleted_characters, FILE *file, char *file_name);
void undo_last_operation(char what_was_before[], FILE* file, char *file_name);

#endif