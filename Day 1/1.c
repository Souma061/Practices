#include<stdio.h>

int max(int a , int b) {
  return (a > b) ? a : b;

}

int min(int a , int b) {
  return (a < b) ? a : b;
}

float average(int a , int b , int c)
 {
  return (a + b + c) / 3.0;
 }

 int main() {
  int a , b , c;

  printf("Enter three integers: ");
  scanf("%d %d %d" , &a, &b, &c);

  printf("The maximum of %d and %d is:  %d\n", a ,b , max(a,b));
   printf("The minimum of %d and %d is:  %d\n", a ,b , min(a,b));
    printf("The average of %d, %d and %d is:  %.2f\n", a ,b, c , average(a,b,c));

    return 0;
}
