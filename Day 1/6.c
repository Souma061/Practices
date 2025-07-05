#include<stdio.h>

char *words[] = {"zero", "one", "two", "three", "four",
                 "five", "six", "seven", "eight", "nine"};

void printWords(int n) {
  if(n == 0) {
    return ;

  }
   printWords(n / 10);
  printf("%s " , words[n % 10]);

}

int main() {
  int num;

  printf("Enter a number: ");
  scanf("%d" , &num);

  if(num == 0) {
    printf("zero.");
  } else {
    if(num < 0) {
      printf("minus ");
      num = -num;
    }
    printWords(num);
  }

  return 0;
}
