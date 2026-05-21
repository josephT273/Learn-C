#include <stdio.h>

// basic calculator cli

int main() {
  double first_number = 0;
  double second_number = 0;
  int oprator;
  double result;
  // get first number from user
  printf("Enter first number: ");
  scanf("%lf", &first_number);

  //
  printf("Enter second number: ");
  scanf("%lf", &second_number);

  printf("Select oprator\n");
  printf("1. Addition\n");
  printf("2. Subtraction\n");
  printf("3. Devision\n");
  printf("4. Multiplication\n");
  scanf("%d", &oprator);

  switch (oprator) {
  case 1:
    result = first_number + second_number;
    break;
  case 2:
    result = first_number - second_number;
    break;
  case 3:
    if (second_number == 0) {
      printf("Undefined number\n");
      break;
    }
    result = first_number / second_number;
    break;
  case 4:
    result = first_number * second_number;
    break;
  default:
    printf("uknown oprator\n");
  }

  printf("%lf \n", result);
}
