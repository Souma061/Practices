#include<stdio.h>
#include<string.h>

void my_strcat(char *dest , const char *src) {
  while(*dest != '\0') {
    dest++;
  }
  while(*src != '\0') {
    *dest = *src;
    dest++;
    src++;
  }
  *dest = '\0';
}

int main() {
  char destination[100], source[100];


  printf("Enter the destination string: ");
  fgets(destination, sizeof(destination), stdin);
  destination[strcspn(destination, "\n")] = '\0';
   printf("Enter a string to concatenate: ");
   
  fgets(source , sizeof(source), stdin);
  source[strcspn(source, "\n")] = '\0';

  if(source[0] == '\0' || destination[0] == '\0') {
    printf("Error: One or both strings are empty.\n");
    return 1;
  }
  my_strcat(destination, source);
  printf("Concatenated string: %s\n" , destination);
  return 0;

}


