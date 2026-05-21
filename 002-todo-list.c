#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char title[20];
  int status;
} Todo;

void list_todo(Todo *todo, int size) {
  printf("List of Tasks\n");
  for (int i = 0; i < size; i++) {
    printf("%d %s status: %d\n", i, todo[i].title, todo[i].status);
  }
}

int add_todo(Todo *todo, int size, int max_size) {
  Todo temp;
  printf("Enter title: ");

  while (getchar() != '\n')
    ;

  fgets(temp.title, sizeof(temp.title), stdin);

  temp.title[strcspn(temp.title, "\n")] = '\0';

  temp.status = 0;
  if (size >= max_size) {
    printf("Todo list is full\n");
    return size;
  }
  todo[size] = temp;
  return ++size;
}

int delete_todo(Todo *todo, int size) {
  int id;

  list_todo(todo, size);
  printf("Enter id for the task: ");
  scanf("%d", &id);

  if (id < 0 || id >= size) {
    printf("Invalid id\n");
    return size;
  }

  for (int i = id; i < size - 1; i++) {
    todo[i] = todo[i + 1];
  }
  return --size;
}

void edit_todo(Todo *todo, int size) {
  int id;

  list_todo(todo, size);
  printf("Enter id for the task: ");
  scanf("%d", &id);

  if (id >= 0 && id < size) {
    Todo temp;
    char temp_title[20];
    printf("Update title: ");

    while (getchar() != '\n')
      ;

    fgets(temp_title, sizeof(temp_title), stdin);

    temp_title[strcspn(temp_title, "\n")] = '\0';

    fgets(temp_title, sizeof(temp.title), stdin);
    if (strlen(temp_title) > 0) {
      strcpy(temp.title, temp_title);
    }

    printf("Update status: ");
    scanf("%d", &temp.status);
    todo[id] = temp;

    printf("Todo updated");
  }
}

int main() {
  Todo *todo;
  int size_of_todo = 0;
  int option = 0;
  int filled_array = 0;
  // accespt intiger to specify the size of array
  printf("How many todos you want to list: ");
  scanf("%d", &size_of_todo);

  // size of todo * with size of the todo value accepted from the user
  // this means if user enter 4 and it calculates the size of Todo struct which
  // is 20 + (4/2) = 22/24 22/24 * 4 = 88/96 bite will be alocated for the array
  todo = (Todo *)malloc(size_of_todo * sizeof(Todo));

  if (todo == NULL) {
    printf("Memory is not allocated\nRestaring the app...");
    return 1;
  }

  do {

    printf("Select an option\n");
    printf("1. add todo\n");
    printf("2. edit todo\n");
    printf("3. delete todo\n");
    printf("4. list todo\n");
    printf("0. exit\n");
    printf(":> ");
    scanf("%d", &option);

    switch (option) {
    case 1:
      filled_array = add_todo(todo, filled_array, size_of_todo);
      break;
    case 2:
      edit_todo(todo, filled_array);
      break;
    case 3:
      filled_array = delete_todo(todo, filled_array);
      break;
    case 4:
      list_todo(todo, filled_array);
      break;
    case 0:
      free(todo);
      return 0;
    default:
      printf("Unkown option\n");
    }
  } while (1);

  free(todo);
}
