#include <stdio.h>
#include <string.h>

void my_strev(char *str)
{
  size_t len = strlen(str);
  size_t i;
  for (i = 0; i < len / 2; i++)
  {
    char temp = str[i];
    str[i] = str[len - i - 1];
    str[len - i - 1] = temp;
  }
  str[len] = '\0';
}

int main()
{
  char str[100];
  printf("Enter a string: ");
  fgets(str, sizeof(str), stdin);
  str[strcspn(str, "\n")] = '\0';
  my_strev(str);
  printf("the reversed string  is: %s\n", str);
  return 0;
}
