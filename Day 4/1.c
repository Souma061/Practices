#include<stdio.h>

int main() {
  int arr[] = {1,2,3,4};
  for(int i = 3; i>=0;i--) {
    printf("%d", &arr[i]);
    return 0;
  }
}
