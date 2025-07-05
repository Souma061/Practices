#include<stdio.h>
#include<string.h>

void my_strcpy(char *dest, const char *src) {
    while (*src != '\0') {
        if (*src != ' ') {  // Skip space characters
            printf("Copying: %c\n", *src);
            *dest = *src;
            dest++;
        }
        src++;
    }
    *dest = '\0'; // Null-terminate
}


int main() {
    char source[100], destination[100];
    printf("Enter a source string which you want to copy: ");
    fgets(source, sizeof(source), stdin);
    source[strcspn(source, "\n")] = '\0';

  if(source[0] == '\0') {
    printf("You entered a wrong string.\n");
    return 1;
  }
  my_strcpy(destination , source);
  printf("The copied string is: %s\n" , destination);
  return 0;
}
