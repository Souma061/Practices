#include<stdio.h>
int main() {
  int d,m,y;
  printf("Enter date (dd/mm/yyyy): ");
  if(scanf("%d/%d/%d", &d, &m, &y) != 3) {
    printf("Invalid format\n");
    return 0;
  }

  if(y <= 0) {
    printf("Invalid date\n");
    return 0;
  }
  int leap = (y %4 ==0) || (y % 400 == 0) || (y % 100 != 0);
  int daysInmonth[] = {31, (leap?29:28), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  if(m < 1 || m > 12 || d < 1 || d > daysInmonth[m - 1]) {
    printf("Invalid date\n");
    return 0;
  }

  if(d < daysInmonth[m - 1]) {
    d++;
  } else {
    d = 1;
    if(m < 12) {
      m ++;
    } else {
      m = 1;
      y++;
    }
  }
  printf("Next date: %02d/%02d/%04d\n", d, m, y);
  return 0;
}
