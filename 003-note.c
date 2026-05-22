#include <stdio.h>
#define FILENAME "notes.txt"

FILE *file_pointer;

/*
 * Create note
 * List notes
 * Edit note
 * Delete note
 * Save to file
 * Load from file
 */
void create_file() { file_pointer = fopen(FILENAME, "w"); }
void list_note() { file_pointer = fopen(FILENAME, "r"); }
void edit_note() {}
void delete_note() {}

int main() {}
