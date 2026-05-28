#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// address struct
typedef struct {
  char name[50];
  char phone[15];
  char email[25];
  char address[200];
} ContactInformation;

typedef struct {
  ContactInformation *contact;
  int count;
  int capacity;
} ContactInformationArray;

void array_push(ContactInformationArray *array, ContactInformation *contact) {
  if (array->count >= array->capacity) {
    int new_capacity = (array->capacity == 0) ? 256 : array->capacity * 2;

    ContactInformation *tmp =
        realloc(array->contact, new_capacity * sizeof(*array->contact));

    if (tmp == NULL) {
      return;
    }

    array->contact = tmp;
    array->capacity = new_capacity;
  }

  array->contact[array->count++] = *contact;
}

void create_contact(ContactInformationArray *array) {
  ContactInformation contact_info;

  printf("Name: ");
  fgets(contact_info.name, sizeof(contact_info.name), stdin);
  contact_info.name[strcspn(contact_info.name, "\n")] = '\0';

  printf("Phone number: ");
  fgets(contact_info.phone, sizeof(contact_info.phone), stdin);
  contact_info.phone[strcspn(contact_info.phone, "\n")] = '\0';

  printf("Email: ");
  fgets(contact_info.email, sizeof(contact_info.email), stdin);
  contact_info.email[strcspn(contact_info.email, "\n")] = '\0';

  printf("Address: ");
  fgets(contact_info.address, sizeof(contact_info.address), stdin);
  contact_info.address[strcspn(contact_info.address, "\n")] = '\0';

  array_push(array, &contact_info);
  printf("Contact added successfully\n");
}

void list_contact_information(ContactInformationArray *array) {
  printf("List of Contact information saved on the system\n");
  printf("%-3s %-50s %-14s %-24s %-200s\n", "ID", "Name", "Phone Number",
         "Email", "Address");
  for (int i = 0; i < array->count; i++) {
    printf("%-3d: %-49s %-14s %-24s %-199s\n", i, array->contact[i].name,
           array->contact[i].phone, array->contact[i].email,
           array->contact[i].address);
  }
  printf("\n");
}

void edit_contact_information(ContactInformationArray *array) {
  list_contact_information(array);

  char buffer[5];
  char *clear_buffer;
  int index;
  printf("Enter index of the contact: ");
  fgets(buffer, sizeof(buffer), stdin);
  index = strtol(buffer, &clear_buffer, 10);

  if (array == NULL || index < 0 || index >= array->count) {
    printf("Their is no contact found\n");
    return;
  }

  printf("Name: ");
  fgets(array->contact[index].name, sizeof(array->contact[index].name), stdin);
  array->contact[index].name[strcspn(array->contact[index].name, "\n")] = '\0';

  printf("Phone number: ");
  fgets(array->contact[index].phone, sizeof(array->contact[index].phone),
        stdin);
  array->contact[index].phone[strcspn(array->contact[index].phone, "\n")] =
      '\0';

  printf("Email: ");
  fgets(array->contact[index].email, sizeof(array->contact[index].email),
        stdin);
  array->contact[index].email[strcspn(array->contact[index].email, "\n")] =
      '\0';

  printf("Address: ");
  fgets(array->contact[index].address, sizeof(array->contact[index].address),
        stdin);
  array->contact[index].address[strcspn(array->contact[index].address, "\n")] =
      '\0';
}

void delete_contact_information(ContactInformationArray *array) {
  list_contact_information(array);

  char buffer[5];
  char *clear_buffer;
  int index;
  printf("Enter index of the contact: ");
  fgets(buffer, sizeof(buffer), stdin);
  index = strtol(buffer, &clear_buffer, 10);

  if (array == NULL || index < 0 || index >= array->count) {
    printf("Their is no contact found\n");
    return;
  }

  for (int i = index; i < array->count - 1; i++) {
    array->contact[i] = array->contact[i + 1];
  }

  (array->count)--;
  printf("Contact deleted!\n");
}

void sort_contact_information(ContactInformationArray *array) {
  for (int i = 1; i < array->count; i++) {
    ContactInformation temp = array->contact[i];
    int j = i - 1;
    while (j >= 0 && strcmp(array->contact[j].name, temp.name) > 0) {
      array->contact[j + 1] = array->contact[j];
      j--;
    }
    array->contact[j + 1] = temp;
  }

  list_contact_information(array);
}

void search_contact_information(ContactInformationArray *array) {
  // using linear search
  char name[50];
  int result = -1;
  printf("Type name for search: ");
  fgets(name, sizeof(name), stdin);
  name[strcspn(name, "\n")] = '\0';

  for (int i = 0; i < array->count; i++) {
    if (strcmp(array->contact[i].name, name) == 0) {
      result = i;
      break;
    }
  }
  if (result != -1) {
    printf("Contact information\n");
    printf("Name: %s\n", array->contact[result].name);
    printf("Address: %s\n", array->contact[result].address);
    printf("Phone No: %s\n", array->contact[result].phone);
    printf("Email: %s\n", array->contact[result].email);
  } else {
    printf("No Result found\n");
  }
}

int main() {
  ContactInformationArray contact_array = {0};
  char buffer[5];
  char *clear_buffer;
  int option = 0;

  do {
    printf("Contact information\n");
    printf("1. Create contact\n");
    printf("2. Read contacts\n");
    printf("3. Edit contact\n");
    printf("4. Delete contact\n");
    printf("5. Search contact\n");
    printf("6. Sort contact\n");
    printf("7. Exit\n");
    printf("Select an option: ");
    fgets(buffer, sizeof(buffer), stdin);

    errno = 0;
    option = strtol(buffer, &clear_buffer, 10);

    switch (option) {
    case 1:
      create_contact(&contact_array);
      break;
    case 2:
      list_contact_information(&contact_array);
      break;
    case 3:
      edit_contact_information(&contact_array);
      break;
    case 4:
      delete_contact_information(&contact_array);
      break;
    case 5:
      search_contact_information(&contact_array);
      break;
    case 6:
      sort_contact_information(&contact_array);
      break;
    case 7:
      free(contact_array.contact);
      return 0;
    default:
      printf("Unknown option please check the menu again\n");
    }
  } while (1);

  free(contact_array.contact);
  return 0;
}
