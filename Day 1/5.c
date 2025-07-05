/*sumOfDigits(1234)
= 4 + sumOfDigits(123)
= 3 + sumOfDigits(12)
= 2 + sumOfDigits(1)
= 1 + sumOfDigits(0)
= 0  → base case*/

#include<stdio.h>

int SumofDigits(int n) {
  
  if(n < 0) {
     n = -n;
  }

  if(n == 0) {
    return 0;
  }


  return (n % 10) + SumofDigits(n / 10);
}

int main() {
  int num;

  printf("Enter a number: ");
  scanf("%d" , &num);

  printf("Sum of the digist of %d is : %d" , num , SumofDigits(num));

  return 0;

}
