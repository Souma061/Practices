// S = 1 - 1/2 + 1/3 - 1/4 + ... up to n terms
#include<stdio.h>
int main() {
  int n,i;
  double sum = 0.0;

  printf("Enter the number of terms: ");
  scanf("%d", &n);


  for(i = 1; i <=n ; i++) {
    if(i % 2 == 1) {
      sum += 1.0/i;
      if(i == 1) {
        printf("1.0");
      } else {
        printf(" + 1/%d", i);
      }
    } else {
      sum -= 1.0 / i;
      printf("- 1.0/%d", i);
    }
  }
  printf("= %.6f\n", sum);
  printf("Sum of the series up to %d terms is: %.6f\n", n, sum);
  return 0;
}
