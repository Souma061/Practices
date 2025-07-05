#include <stdio.h>

struct student
{
  char name[50];
  int roll;
  float marks;
};

int main()
{
  FILE *fp;
  struct student temp;

  fp = fopen("students.txt", "r");
  if (fp == NULL)
  {
    printf("Error opening file.\n");
    return 1;
  }

  printf("Name\t\tRoll\t\tMarks\n");
  printf("--------------------------------\n");
  while (fscanf(fp, "%s %d %f", temp.name, &temp.roll, &temp.marks) == 3)
  {
    printf("%-15s\t%d\t\t%.2f\n", temp.name, temp.roll, temp.marks);
  }
  fclose(fp);
  return 0;
}
