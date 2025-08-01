#include <stdio.h>
int main()
{
  int x = 10;
  printf("Before: x = %d\n", x);

  // The problematic line
  printf("Result: %d\n", x = x++);

  printf("After: x = %d\n", x);

  // Let's see what happens step by step
  x = 10;         // reset
  int temp = x++; // temp = 10, x = 11
  x = temp;       // x = 10
  printf("Step by step result: x = %d\n", x);

  return 0;
}
