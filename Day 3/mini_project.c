#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct student
{
  char name[50];
  int roll;
  float marks;
};

// Function declarations
int is_duplicate_roll(int roll);
void add_students();
void display_students();
void search_student();
void update_student();
void delete_student();

void add_students()
{
  struct student s;
  FILE *fp = fopen("new.txt", "a");
  if (!fp)
  {
    printf("Error opening file.\n");
    return;
  }

  printf("Enter student's name: ");
  fgets(s.name, sizeof(s.name), stdin);
  s.name[strcspn(s.name, "\n")] = '\0';

  printf("Enter student's roll number: ");
  scanf("%d", &s.roll);
  getchar();

  // Check for duplicate roll number
  if (is_duplicate_roll(s.roll))
  {
    printf("Error: Roll number %d already exists. Student not added.\n", s.roll);
    fclose(fp);
    return;
  }

  printf("Enter student's marks: ");
  scanf("%f", &s.marks);
  getchar();

  fprintf(fp, "%s %d %.2f\n", s.name, s.roll, s.marks);
  fclose(fp);
  printf("Student added successfully.\n");
}

void display_students()
{
  char line[200];
  struct student s;
  FILE *fp = fopen("new.txt", "r");
  if (!fp)
  {
    printf("Error opening File.\n");
    return;
  }

  printf("Students List\n");
  printf("%-20s %-10s %-10s\n", "Name", "Roll No", "Marks");
  printf("-----------------------------------------------\n");

  while (fgets(line, sizeof(line), fp))
  {
    // Find the last two spaces to separate name from roll and marks
    char *last_space = strrchr(line, ' ');
    if (last_space)
    {
      *last_space = '\0';
      s.marks = atof(last_space + 1);

      char *second_last_space = strrchr(line, ' ');
      if (second_last_space)
      {
        *second_last_space = '\0';
        s.roll = atoi(second_last_space + 1);
        strcpy(s.name, line);

        printf("%-20s %-10d %-10.2f\n", s.name, s.roll, s.marks);
      }
    }
  }
  fclose(fp);
}

void search_student()
{
  char line[200];
  struct student s;
  char name[50];
  int found = 0;

  FILE *fp = fopen("new.txt", "r");
  if (!fp)
  {
    printf("Error opening file.\n");
    return;
  }

  printf("Enter student's name to search: ");
  fgets(name, sizeof(name), stdin);
  name[strcspn(name, "\n")] = '\0';

  while (fgets(line, sizeof(line), fp))
  {
    // Find the last two spaces to separate name from roll and marks
    char *last_space = strrchr(line, ' ');
    if (last_space)
    {
      *last_space = '\0';
      s.marks = atof(last_space + 1);

      char *second_last_space = strrchr(line, ' ');
      if (second_last_space)
      {
        *second_last_space = '\0';
        s.roll = atoi(second_last_space + 1);
        strcpy(s.name, line);

        if (strcmp(s.name, name) == 0)
        {
          printf("Student found!\n");
          printf("Name: %s\n", s.name);
          printf("Roll No: %d\n", s.roll);
          printf("Marks: %.2f\n", s.marks);
          found = 1;
          break;
        }
      }
    }
  }
  if (!found)
  {
    printf("Student not found.\n");
  }
  fclose(fp);
}

void update_student()
{
  char line[200];
  struct student s;
  int roll;
  int found = 0;
  FILE *fp = fopen("new.txt", "r");
  FILE *temp = fopen("temp.txt", "w");
  if (!fp || !temp)
  {
    printf("Error opening file.\n");
    return;
  }
  printf("Enter student's roll number to update: ");
  scanf("%d", &roll);
  getchar();

  while (fgets(line, sizeof(line), fp))
  {
    // Find the last two spaces to separate name from roll and marks
    char *last_space = strrchr(line, ' ');
    if (last_space)
    {
      *last_space = '\0';
      s.marks = atof(last_space + 1);

      char *second_last_space = strrchr(line, ' ');
      if (second_last_space)
      {
        *second_last_space = '\0';
        s.roll = atoi(second_last_space + 1);
        strcpy(s.name, line);

        if (s.roll == roll)
        {
          found = 1;
          printf("Current details:\n");
          printf("name: %s\n", s.name);
          printf("Roll No: %d\n", s.roll);
          printf("Marks: %.2f\n", s.marks);

          printf("Enter new name: ");
          fgets(s.name, sizeof(s.name), stdin);
          s.name[strcspn(s.name, "\n")] = '\0';
          printf("Enter new roll number: ");
          scanf("%d", &s.roll);
          getchar();
          printf("Enter new marks: ");
          scanf("%f", &s.marks);
          getchar();
        }
      }
    }
    fprintf(temp, "%s %d %.2f\n", s.name, s.roll, s.marks);
  }
  if (!found)
  {
    printf("Student with roll number %d not found.\n", roll);
  }
  else
  {
    printf("Student details updated successfully.\n");
  }
  fclose(fp);
  fclose(temp);
  remove("new.txt");
  rename("temp.txt", "new.txt");
}

void delete_student()
{
  char line[200];
  struct student s;
  int roll;
  int found = 0;
  FILE *fp = fopen("new.txt", "r");
  FILE *temp = fopen("temp.txt", "w");
  if (!fp || !temp)
  {
    printf("Error opening file.\n");
    return;
  }

  printf("Enter student's roll number to delete: ");
  scanf("%d", &roll);
  getchar();

  while (fgets(line, sizeof(line), fp))
  {
    // Find the last two spaces to separate name from roll and marks
    char *last_space = strrchr(line, ' ');
    if (last_space)
    {
      *last_space = '\0';
      s.marks = atof(last_space + 1);

      char *second_last_space = strrchr(line, ' ');
      if (second_last_space)
      {
        *second_last_space = '\0';
        s.roll = atoi(second_last_space + 1);
        strcpy(s.name, line);

        if (s.roll == roll)
        {
          found = 1;
          printf("Student with roll number %d deleted successfully.\n", roll);
        }
        else
        {
          fprintf(temp, "%s %d %.2f\n", s.name, s.roll, s.marks);
        }
      }
    }
  }
  if (!found)
  {
    printf("Student with roll number %d not found.\n", roll);
  }
  fclose(fp);
  fclose(temp);
  remove("new.txt");
  rename("temp.txt", "new.txt");
}

// Function to check if roll number already exists
int is_duplicate_roll(int roll)
{
  char line[200];
  struct student s;
  FILE *fp = fopen("new.txt", "r");

  if (!fp)
  {
    return 0; // If file doesn't exist, no duplicates
  }

  while (fgets(line, sizeof(line), fp))
  {
    char *last_space = strrchr(line, ' ');
    if (last_space)
    {
      *last_space = '\0';
      s.marks = atof(last_space + 1);

      char *second_last_space = strrchr(line, ' ');
      if (second_last_space)
      {
        *second_last_space = '\0';
        s.roll = atoi(second_last_space + 1);

        if (s.roll == roll)
        {
          fclose(fp);
          return 1; // Duplicate found
        }
      }
    }
  }
  fclose(fp);
  return 0; // No duplicate found
}

int main()
{
  int choice;
  do
  {
    printf("\n==== Student Record System ====\n");
    printf("1. Add Student\n");
    printf("2. Display All\n");
    printf("3. Search by Name\n");
    printf("4. Update by Roll\n");
    printf("5. Delete by Roll\n");
    printf("0. Exit\n");
    printf("Choose: ");
    scanf("%d", &choice);
    getchar();

    switch (choice)
    {
    case 1:
      add_students();
      break;
    case 2:
      display_students();
      break;
    case 3:
      search_student();
      break;
    case 4:
      update_student();
      break;
    case 5:
      delete_student();
      break;
    case 0:
      printf("Exiting...\n");
      break;
    default:
      printf("Invalid choice. Please try again.\n");
    }
  } while (choice != 0);
  return 0;
}
