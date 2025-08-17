#include<stdio.h>
int main() {
  int arr[10], n, i,j, choice;

  printf("Enter your choice(1 for Average of even numbers & 2 for  Find minimum numbers from the array)");
  scanf("%d", &choice);

  printf("Enter the number of elements in the array (max 10): ");
  scanf("%d", &n);

  printf("Enter %d elements:\n", n);
  for(i = 0; i < n; i++) {
    scanf("%d", &arr[i]);
  }

  switch(choice) {
    case 1: {
      double sum = 0.0;
      int cnt = 0;
      for(i = 0; i<n; i++) {
        if(arr[i] % 2 == 0) {
          sum += arr[i];
          cnt++;
        }
      }
      if(cnt > 0) {
        printf("Average of even numbers: %.2f\n", sum / cnt);
      } else {
        printf("No even numbers found.\n");
      }
    }
    break;
    case 2: {
      int min = arr[0];
      for(i = 1; i < n; i++) {
        if(arr[i] < min) {
          min = arr[i];
        }
      }
      printf("Minimum number: %d\n", min);
    }
    break;
  }
  return 0;
}
