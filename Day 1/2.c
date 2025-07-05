// Count digist

#include<stdio.h>

int cnt_digits(int n) {
    if (n == 0)
        return 0;
    return 1 + cnt_digits(n / 10);
}
  int main() {
  int num;

  printf("Enter a number: ");
  scanf("%d" , &num);

  if(num == 0) {
    printf("Number of digis: 1\n");
  } else {
    if(num < 0) num = -num;
    printf("The number of digis: %d" , cnt_digits(num));
  }
  return 0;


}
