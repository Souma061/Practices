// reverese numbers

#include<stdio.h>
#include<math.h>

int cnt_digits(int n) {
  if(n == 0) {
    return 0;
  }
  return 1 + cnt_digits(n / 10);
}

int rec_rev(int n , int digits) {
  if(n == 0) {
    return 0;
  }
  return(n % 10) * pow(10 , digits - 1) + rec_rev(n / 10 , digits - 1);
}

int reverse(int n) {
  int isNegative = n < 0;
  if(isNegative) n = -n;

  int digits = cnt_digits(n);
  int result = rec_rev(n , digits);

  return isNegative ? -result : result;
}


int main() {
  int num;

  printf("Enter a number: ");
  scanf("%d" , &num);

  printf("The reverse of the number is: %d" , reverse(num));
  return 0;
}
