#include<stdio.h>

struct student {
  char name[50];
  int roll;
  float marks;
};

int main() {
  struct student s[50];
  FILE *fp;
  int i, n;

  printf("Enter number of students: ");
  if (scanf("%d", &n) != 1 || n <= 0 || n > 50) {
    printf("Invalid input! Please enter a number between 1-50.\n");
    return 1;
  }

  fp = fopen("students.txt", "a");
  if (fp == NULL) {
    printf("Error opening file.\n");
    return 1;
  }

  for (i = 0; i < n; i++) {
    printf("Enter name, roll and marks for student %d: ", i + 1);
    if (scanf("%s %d %f", s[i].name, &s[i].roll, &s[i].marks) != 3) {
      printf("Invalid input.\n");
      fclose(fp);
      return 1;
    }
    fprintf(fp, "%s %d %.2f\n", s[i].name, s[i].roll, s[i].marks);
  }
  fclose(fp);

  // Open for classification
  fp = fopen("students.txt", "r");
  if (fp == NULL) {
    printf("Error opening file.\n");
    return 1;
  }

  FILE *odd_fp = fopen("odd_students.txt", "w");
  FILE *even_fp = fopen("even_students.txt", "w");
  if (odd_fp == NULL || even_fp == NULL) {
    printf("Error opening output files.\n");
    fclose(fp);  // Proper cleanup
    return 1;
  }

  struct student temp;
  while (fscanf(fp, "%s %d %f", temp.name, &temp.roll, &temp.marks) == 3) {
    if (temp.roll % 2 == 0) {
      fprintf(even_fp, "%s %d %.2f\n", temp.name, temp.roll, temp.marks);
    } else {
      fprintf(odd_fp, "%s %d %.2f\n", temp.name, temp.roll, temp.marks);
    }
  }

  fclose(fp);
  fclose(odd_fp);
  fclose(even_fp);

  printf("Data has been written to odd_students.txt and even_students.txt.\n");

  return 0;
}
