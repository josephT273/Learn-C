#include "string.h"
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/types.h>
/*
 * Create note
 * List notes
 * Edit note
 * Delete note
 * Save to file
 * Load from file
 */

typedef struct {
  int id;
  char note[1000];
} Note;

typedef struct {
  Note *notes;
  int count;
  int capacity;
} NoteArray;

void array_push(NoteArray *array, Note *note) {
  if (array->count >= array->capacity) {
    int new_capacity = (array->capacity == 0) ? 256 : array->capacity * 2;
    Note *tmp = realloc(array->notes, new_capacity * sizeof(*array->notes));
    if (tmp == NULL)
      return;
    array->notes = tmp;
    array->capacity = new_capacity;
  }
  array->notes[array->count++] = *note;
}

void list_notes(NoteArray *array) {
  printf("List of notes\n");
  for (int i = 0; i < array.count; i++) {
    printf("%d. %s \n", i, (array.notes[i]).note);
  }
  printf("\n");
}

void delete_note(NoteArray *array) {
  int index = 0;
  printf("Enter id to delete note: ");
  scanf("%d", &index);

  if (array == NULL || index < 0 || index >= array->count) {
    printf("Their is no notes found\n");
    return;
  }

  for (int i = index; i < array->count; i++) {
    array->notes[i] = array->notes[i + 1];
  }
  (array->count)--;
}

void edit_note(NoteArray *array) {
  list_notes(array);
  int index;
  printf("Enter index of the note to edit: ");
  scanf("%d", &index);
  char note[1000] = {0};
  if (array == NULL || index < 0 || index >= array->count) {
    printf("Their is no notes found\n");
    return;
  }

  printf("Type you new note here: ");
  while (getchar() != '\n')
    ;
  fgets(note, sizeof(note), stdin);

  note[strcspn(note, "\n")] = '\0';
  strcpy(array->notes[id].note, note);
}

void create_note(NoteArray *array) {
  int id = array->count + 1;
  printf("Type your note: ");
  char note[1000];
  while (getchar() != '\n')
    ;
  fgets(note, sizeof(note), stdin);

  note[strcspn(note, "\n")] = '\0';

  Note temp_note = {0};
  temp_note.id = id;
  strcpy(temp_note.note, note);
  array_push(array, &temp_note);
  printf("\nNote added successfully\n\n");
}

int main() {
  NoteArray array = {0};
  int key = 0;
  int option = 0;
  do {
    printf("Select an option\n");
    printf("1. List notes\n");
    printf("2. Create note\n");
    printf("3. Edit note\n");
    printf("4. Delete note\n");
    printf("0. Exit\n");
    printf(":> ");
    scanf("%d", &option);

    switch (option) {
    case 1:
      list_notes(&array);
      break;
    case 2:
      create_note(&array);
      break;
    case 3:
      edit_note(&array);
      break;
    case 4:
      delete_note(&array);
      break;
    case 0:
      return 0;
    default:
      printf("Please check your option selection\n");
    }
  } while (1);
}
