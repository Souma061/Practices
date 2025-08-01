// Hospital Management System (HMS) in C

/*
1. Modules to Include
Add Patient Record

View All Patients

Search Patient by ID

Delete Patient Record

Update Patient Info

Discharge Patient

Exit Program*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct patient
{
  int id;
  char name[50];
  int age;
  char gender[10];
  char disease[100];
  char contact[15];
  char admittedDate[20];
};

void addPatient()
{
  struct patient p;
  FILE *fp = fopen("patients.dat", "ab+");
  if (fp == NULL)
  {
    printf("Error opening file!\n");
    return;
  }

  printf("Enter patient ID: ");
  scanf("%d", &p.id);
  getchar(); // to consume newline character left by scanf

  printf("Enter patient Name: ");
  fgets(p.name, sizeof(p.name), stdin);
  p.name[strcspn(p.name, "\n")] = '\0';

  printf("Enter patient age: ");
  scanf("%d", &p.age);
  getchar(); // to consume newline character left by scanf

  printf("Enter your Gender: ");
  fgets(p.gender, sizeof(p.gender), stdin);
  p.gender[strcspn(p.gender, "\n")] = '\0';

  printf("Enter the Disease: ");
  fgets(p.disease, sizeof(p.disease), stdin);
  p.disease[strcspn(p.disease, "\n")] = '\0';

  printf("Enter Contact Number: ");
  fgets(p.contact, sizeof(p.contact), stdin);
  p.contact[strcspn(p.contact, "\n")] = '\0';

  printf("Enter Admitted Date (DD/MM/YYYY): ");
  fgets(p.admittedDate, sizeof(p.admittedDate), stdin);
  p.admittedDate[strcspn(p.admittedDate, "\n")] = '\0';

  fwrite(&p, sizeof(p), 1, fp);
  fclose(fp);
  printf("Patient record added successfully!\n");
}

void viewAllPatients()
{
  struct patient p;
  printf("\033[1;32m=== View All Patient's List ===\033[0m\n");
  FILE *fp = fopen("patients.dat", "rb");

  if (fp == NULL)
  {
    printf("No patient records found. Please add patients first using option 1.\n");
    return;
  }
  printf("---------------------------------------------------------------\n");

  int patientCount = 0;
  while (fread(&p, sizeof(p), 1, fp))
  {
    printf("Patient ID: %d\n", p.id);
    printf("Name: %s\n", p.name);
    printf("Age: %d\n", p.age);
    printf("Gender: %s\n", p.gender);
    printf("Disease: %s\n", p.disease);
    printf("Contact: %s\n", p.contact);
    printf("Admitted Date: %s\n", p.admittedDate);
    printf("---------------------------------------------------------------\n");
    patientCount++;
  }

  if (patientCount == 0)
  {
    printf("No patients found.\n");
  }
  else
  {
    printf("Total patients: %d\n", patientCount);
  }
  fclose(fp);
}

void searchByID()
{
  int id;
  struct patient p;
  int found = 0;

  FILE *fp = fopen("patients.dat", "rb");
  if (fp == NULL)
  {
    printf("Error opening file!\n");
    return;
  }

  printf("=== Search Account ===\n");
  printf("Enter patient ID to search: ");
  scanf("%d", &id);
  getchar(); // to consume newline character left by scanf

  while (fread(&p, sizeof(p), 1, fp))
  {
    if (p.id == id)
    {
      printf("Patient ID: %d\n", p.id);
      printf("Name: %s\n", p.name);
      printf("Age: %d\n", p.age);
      printf("Gender: %s\n", p.gender);
      printf("Disease: %s\n", p.disease);
      printf("Contact: %s\n", p.contact);
      printf("Admitted Date: %s\n", p.admittedDate);
      found = 1;
      break;
    }
  }

  if (!found)
  {
    printf("Patient with ID %d not found.\n", id);
  }

  fclose(fp);
}

void deletePatientRecord()
{
  int id;
  struct patient p;
  int found = 0;

  FILE *fp = fopen("patients.dat", "rb");
  FILE *temp = fopen("temp.dat", "wb");

  if (fp == NULL || temp == NULL)
  {
    printf("Error opening file!\n");
    return;
  }
  printf("Enter patient ID to delete: ");
  scanf("%d", &id);
  getchar(); // to consume newline character left by scanf
  while (fread(&p, sizeof(p), 1, fp))
  {
    if (p.id == id)
    {
      printf("Account with ID %d found. Deleting...\n", id);
      printf("Are you sure you want to delete this record? (y/n): ");
      char choice;
      scanf(" %c", &choice);
      if (choice == 'Y' || choice == 'y')
      {
        printf("Record deleted successfully.\n");
        found = 1;
        continue;
      }
    }
    fwrite(&p, sizeof(p), 1, temp);
  }
  fclose(fp);
  fclose(temp);

  if (found)
  {
    remove("patients.dat");
    rename("temp.dat", "patients.dat");
  }
  else
  {
    remove("temp.dat");
    printf("Record not found.\n");
  }
}

void updatepatientInfo()
{
}

void menu()
{
  int choice;
  do
  {
    printf("\nHospital Management System Menu:\n");
    printf("1. Add Patient Record\n");
    printf("2. View All Patients\n");
    printf("3. Search Patient by ID\n");
    printf("4. Delete Patient Record\n");
    printf("5. Update Patient Info\n");
    printf("6. Discharge Patient\n");
    printf("7. Exit Program\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    getchar(); // to consume newline character left by scanf

    switch (choice)
    {
    case 1:
      addPatient();
      break;
    case 2:
      // viewAllPatients(); // Function to be implemented
      viewAllPatients();
      break;
    case 3:
      // searchPatientByID(); // Function to be implemented
      searchByID();
      break;
    case 4:
      // deletePatientRecord(); // Function to be implemented
      deletePatientRecord();
      break;
    case 5:
      // updatePatientInfo(); // Function to be implemented
      break;
    case 6:
      // dischargePatient(); // Function to be implemented
      break;
    case 7:
      printf("Exiting program...\n");
      break;
    default:
      printf("Invalid choice! Please try again.\n");
    }
  } while (choice != 7);
}

int main()
{
  printf("\033[1;32m======================================\033[0m\n");
  printf("\033[1;33m  Welcome to Hospital Management System  \033[0m\n");
  printf("\033[1;32m======================================\033[0m\n");

  menu();
  return 0;
}
