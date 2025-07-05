#include<stdio.h>

void swap(int *a , int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

int main()
{
  int x = 12 , y = 2;
  printf("Before swapping: x = %d, y = %d\n\n" , x , y);
  swap(&x , &y);
  printf("After swapping: x = %d, y = %d" , x , y);
  return 0;
}
