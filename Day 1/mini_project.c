#include <stdio.h>
#include <math.h>

// ---------- Function Definitions ----------

int cnt_digits(int n) {
  if (n == 0) return 0;
  return 1 + cnt_digits(n / 10);
}

int rec_rev(int n, int digits) {
  if (n == 0) return 0;
  return (n % 10) * pow(10 , digits - 1) + rec_rev(n / 10 , digits - 1);
}

int reverse(int n) {
  int isNegative = n < 0;
  if (isNegative) n = -n;
  int digits = cnt_digits(n);
  int result = rec_rev(n , digits);
  return isNegative ? -result : result;
}

int ispalindrome(int n) {
  return n == reverse(n);
}

int SumofDigits(int n) {
  if (n < 0) n = -n;
  if (n == 0) return 0;
  return (n % 10) + SumofDigits(n / 10);
}

void digitofWord(int n) {
  char *words[] = {"zero", "one", "two", "three", "four",
                   "five", "six", "seven", "eight", "nine"};

  if (n == 0) return;
  digitofWord(n / 10);
  printf("%s ", words[n % 10]);
}

int fibonacci(int n) {
  if (n == 0) return 0;
  if (n == 1) return 1;
  return fibonacci(n - 1) + fibonacci(n - 2);
}

void showMenu() {
  printf("\n=== Number Toolbox ===\n");
  printf("1. Count Digits\n");
  printf("2. Reverse Number\n");
  printf("3. Check Palindrome\n");
  printf("4. Sum of Digits\n");
  printf("5. Print Digits in Words\n");
  printf("6. Fibonacci Number\n");
  printf("7. Exit\n");
}

// ---------- Main Program ----------

int main() {
  int choice, n1;

  do {
    showMenu();
    printf("Enter choice: ");
    if (scanf("%d", &choice) != 1) {
      while (getchar() != '\n');
      printf("Invalid input!\n");
      continue;
    }

    switch (choice) {
      case 1:
        printf("Enter a number: ");
        scanf("%d", &n1);
        printf("Total number of digits: %d\n", cnt_digits(n1));
        break;

      case 2:
        printf("Enter a number: ");
        scanf("%d", &n1);
        printf("Reversed: %d\n", reverse(n1));
        break;

      case 3:
        printf("Enter a number: ");
        scanf("%d", &n1);
        if (ispalindrome(n1))
          printf("%d is a palindrome number.\n", n1);
        else
          printf("%d is not a palindrome number.\n", n1);
        break;

      case 4:
        printf("Enter a number: ");
        scanf("%d", &n1);
        printf("Sum of digits: %d\n", SumofDigits(n1));
        break;

      case 5:
        printf("Enter a number: ");
        scanf("%d", &n1);
        if (n1 == 0) printf("zero");
        else {
          if (n1 < 0) {
            printf("minus ");
            n1 = -n1;
          }
          digitofWord(n1);
        }
        printf("\n");
        break;

      case 6:
        printf("Enter position: ");
        scanf("%d", &n1);
        if (n1 < 0)
          printf("Fibonacci not defined for negatives.\n");
        else
          printf("Fibonacci at position %d: %d\n", n1, fibonacci(n1));
        break;

      case 7:
        printf("Exiting...\n");
        break;

      default:
        printf("Invalid choice!\n");
    }
  } while (choice != 7);

  return 0;
}
