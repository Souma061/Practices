#include <stdio.h>
#include <ctype.h>
#include <string.h>

int my_strlen(char *str)
{
  int len = 0;
  int vowel_cnt = 0;
  int consonant_cnt = 0;
  while (*str != '\0')
  {
    int ch = tolower(*str);
    printf("characters: %c\n", *str);
    printf("length: %d\n", len);
    if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u')
    {
      vowel_cnt++;
    }
    else if (ch >= 'a' && ch <= 'z')
    {
      consonant_cnt++;
    }
    len++;
    str++;
  }
  printf("Vowels: %d\n", vowel_cnt);
  printf("Consonants: %d\n", consonant_cnt);
  return len;
}

int main()
{
  char name[100];
  printf("Enter a string: ");
  fgets(name, sizeof(name), stdin);
  name[strcspn(name, "\n")] = '\0';
  if (name[0] == '\0')
  {
    printf("You entered an empty string.\n");
    return 1;
  }
  printf("The length of the string is: %d\n", my_strlen(name));
  return 0;
}
