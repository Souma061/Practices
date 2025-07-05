#include <stdio.h>

struct student {
    char name[50];
    int roll;
    float marks;
};

int main() {
    struct student s;
    FILE *fp;
    int i, n;

    printf("Enter number of students: ");
    if (scanf("%d", &n) != 1 || n <= 0 || n > 50) {
        printf("Invalid input. Please enter a number between 1-50.\n");
        return 1;
    }

    // Clear input buffer after scanf
    getchar();

    // Open file in append mode
    fp = fopen("students.txt", "a");
    if (fp == NULL) {
        printf("Error opening file for writing.\n");
        return 1;
    }

    for (i = 0; i < n; i++) {
        printf("Enter name for student %d: ", i + 1);
        fgets(s.name, sizeof(s.name), stdin);
        s.name[strcspn(s.name, "\n")] = '\0'; // remove newline

        printf("Enter roll: ");
        if (scanf("%d", &s.roll) != 1) {
            printf("Invalid roll number.\n");
            fclose(fp);
            return 1;
        }

        printf("Enter marks: ");
        if (scanf("%f", &s.marks) != 1) {
            printf("Invalid marks.\n");
            fclose(fp);
            return 1;
        }

        // Clear buffer again before next fgets
        getchar();

        fprintf(fp, "%s %d %.2f\n", s.name, s.roll, s.marks);
    }
    fclose(fp);

    // Read and display data
    fp = fopen("students.txt", "r");
    if (fp == NULL) {
        printf("Error opening file for reading.\n");
        return 1;
    }

    struct student temp;
    printf("\nStudent Records:\n");
    printf("%-20s %-10s %-10s\n", "Name", "Roll", "Marks");
    printf("----------------------------------------------\n");

    while (fscanf(fp, " %[^\n] %d %f", temp.name, &temp.roll, &temp.marks) == 3) {
        printf("%-20s %-10d %-10.2f\n", temp.name, temp.roll, temp.marks);
    }

    fclose(fp);
    return 0;
}
