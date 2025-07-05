#include<stdio.h>


int main() {
  FILE *fp;
  char ch[500];

  fp = fopen("hello.txt" , "w");
  if(fp == NULL) {
    printf("Error opening file.\n");
    return 1;
  }
  printf("Enter text: \n");
  fgets(ch , sizeof(ch) , stdin);
  fputs(ch , fp);
  fclose(fp);

  fp = fopen("hello.txt" , "r");
   if(fp == NULL) {
    printf("Error opening file.\n");
    return 1;
  }
  
  while(fgets(ch , sizeof(ch) ,fp)) {
    printf("%s" , ch);
  }
  fclose(fp);
  return 0;

}
