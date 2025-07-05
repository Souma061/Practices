#include<stdio.h>
#include<string.h>

int my_strcmp(const char *str1 , const char *str2) {
  while(*str1 && *str2) {
    printf("Comparing: %c vs %c\n", *str1, *str2);
    if(*str1 != *str2) {
      return *str1 - *str2;

    }
   str1++;
   str2++;


  }
  return *str1 - *str2;
}

int main() {
  char s1[100] , s2[100];
  printf("Enter first string: ");
  fgets(s1 , sizeof(s1) , stdin);
  s1[strcspn(s1 , "\n")] = '\0';
  if(s1[0] == '\0') {
    printf("You entered a wrong string.\n");
    return 1;
  }
    printf("Enter second string: ");
  fgets(s2 , sizeof(s2) , stdin);
  s2[strcspn(s2 , "\n")] = '\0';
  if(s2[0] == '\0') {
    printf("You entered a wrong string.\n");
    return 1;
  }
  int result = my_strcmp(s1 , s2);
  if(result == 0) {
    printf("The strings are equal.\n");
  } else if(result < 0) {
    printf("The first string is smaller.\n");
  } else {
    printf("The second string is smaller.\n");
  }
  return 0;

}
