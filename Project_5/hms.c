// Hospital Management System (HMS) in C



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<ctype.h>

struct patient
{
  int id;
  char name[50];
  int age;
  char gender[10];
  char disease[100];
  char contact[15];
  char admittedDate[20];
  char dischargeDate[20];
  char prescription[200];
};

struct dischargedPatient
{
  int id;
  char name[50];
  int age;
  char gender[10];
  char disease[100];
  char contact[15];
  char admittedDate[20];
  char dischargeDate[20];
  char prescription[200];
};

int idExists(int id)
{
  struct patient p;
  FILE *fp = fopen("patients.dat", "rb");
  if (fp == NULL)
  {
    printf("Error opening file!\n");
    return 0;
  }
  while (fread(&p, sizeof(p), 1, fp))
  {
    if (p.id == id)
    {
      fclose(fp);
      return 1; // ID exists
    }
  }
  fclose(fp);
  return 0; // ID does not exist
}

int isValidAge(int age) {
  return (age > 0 && age < 120);
}

int isValidContact(const char *contact) {
  if(strlen(contact) != 10) {
    return 0;
  }
  for(int i = 0; contact[i] != '\0'; i++) {
    if(!isdigit(contact[i])) {
      return 0; // Contact must be numeric
    }
  }
  return 1; // Valid contact
}

int isValidDate(const char *date) {
  int day, month, year;
  if(sscanf(date, "%d/%d/%d", &day, &month, &year) != 3) {
    return 0;
  }
  if(day < 1 || day > 31 || month < 1 || month > 12 || year < 1900 || year > 2100) {
    return 0;
  }
  return 1; // Valid date
}

void addPatient()
{
  struct patient p;
  FILE *fp = fopen("patients.dat", "ab+");
  if (fp == NULL)
  {
    printf("Error opening file!\n");
    return;
  }
  do
  {
    printf("Enter Patient ID: ");
    scanf("%d", &p.id);
    getchar();

    if (p.id <= 0)
    {
      printf("Invalid input! ID must be positive.\n");
      continue;
    }
    if (idExists(p.id))
    {
      printf("Patient with ID %d already exists. Please enter a unique ID.\n", p.id);
    }
    else
    {
      break;
    }
  } while (1);

  printf("Enter patient Name: ");
  fgets(p.name, sizeof(p.name), stdin);
  p.name[strcspn(p.name, "\n")] = '\0';

  do {
    printf("Enter patient age: ");
    scanf("%d", &p.age);
    getchar();
    if(!isValidAge(p.age)) {
      printf("Invalid age! Please enter a valid age (1-119).\n");

    }
  } while (!isValidAge(p.age));

  printf("Enter Gender: ");
  fgets(p.gender, sizeof(p.gender), stdin);
  p.gender[strcspn(p.gender, "\n")] = '\0';

  printf("Enter the Disease: ");
  fgets(p.disease, sizeof(p.disease), stdin);
  p.disease[strcspn(p.disease, "\n")] = '\0';

 do {
  printf("Enter your contact number (10 digits): ");
  fgets(p.contact, sizeof(p.contact), stdin);
  p.contact[strcspn(p.contact, "\n")] = '\0';

  if(!isValidContact(p.contact)) {
    printf("Invalid contact number! Please enter a valid 10-digit number.\n");
  }
} while (!isValidContact(p.contact));

do {
  printf("Enter Admitted Date (DD/MM/YYYY): ");
  fgets(p.admittedDate, sizeof(p.admittedDate), stdin);
  p.admittedDate[strcspn(p.admittedDate, "\n")] = '\0';
  if(!isValidDate(p.admittedDate)) {
    printf("Invalid date format! Please enter a valid date (DD/MM/YYYY).\n");
  }
} while (!isValidDate(p.admittedDate));

  fwrite(&p, sizeof(p), 1, fp);
  fclose(fp);
  printf("✅ Patient record added successfully!\n");
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

void updatepatientInfo() {
    struct patient p;
    int id, found = 0, choice;

    FILE *fp = fopen("patients.dat", "rb+");
    if (!fp) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter patient ID to update: ");
    scanf("%d", &id);
    getchar();

    while (fread(&p, sizeof(p), 1, fp)) {
        if (p.id == id) {
            found = 1;
            printf("\n--- Current Patient Info ---\n");
            printf("Name: %s\n", p.name);
            printf("Age: %d\n", p.age);
            printf("Gender: %s\n", p.gender);
            printf("Disease: %s\n", p.disease);
            printf("Contact: %s\n", p.contact);
            printf("Admitted Date: %s\n", p.admittedDate);

            printf("\nWhich field do you want to update?\n");
            printf("1. Name\n2. Age\n3. Gender\n4. Disease\n5. Contact\n6. Admitted Date\n");
            printf("Enter choice: ");
            scanf("%d", &choice);
            getchar();

            switch (choice) {
                case 1:
                    printf("Enter new Name: ");
                    fgets(p.name, sizeof(p.name), stdin);
                    p.name[strcspn(p.name, "\n")] = '\0';
                    break;
                case 2:
                    do {
                        printf("Enter new Age: ");
                        scanf("%d", &p.age);
                        getchar();
                        if (!isValidAge(p.age))
                            printf("❌ Invalid age!\n");
                    } while (!isValidAge(p.age));
                    break;
                case 3:
                    printf("Enter new Gender: ");
                    fgets(p.gender, sizeof(p.gender), stdin);
                    p.gender[strcspn(p.gender, "\n")] = '\0';
                    break;
                case 4:
                    printf("Enter new Disease: ");
                    fgets(p.disease, sizeof(p.disease), stdin);
                    p.disease[strcspn(p.disease, "\n")] = '\0';
                    break;
                case 5:
                    do {
                        printf("Enter new Contact: ");
                        fgets(p.contact, sizeof(p.contact), stdin);
                        p.contact[strcspn(p.contact, "\n")] = '\0';
                        if (!isValidContact(p.contact))
                            printf("❌ Invalid contact number!\n");
                    } while (!isValidContact(p.contact));
                    break;
                case 6:
                    do {
                        printf("Enter new Admitted Date (DD/MM/YYYY): ");
                        fgets(p.admittedDate, sizeof(p.admittedDate), stdin);
                        p.admittedDate[strcspn(p.admittedDate, "\n")] = '\0';
                        if (!isValidDate(p.admittedDate))
                            printf("❌ Invalid date format!\n");
                    } while (!isValidDate(p.admittedDate));
                    break;
                default:
                    printf("Invalid choice!\n");
            }

            fseek(fp, -sizeof(p), SEEK_CUR);
            fwrite(&p, sizeof(p), 1, fp);
            printf("✅ Patient info updated successfully!\n");
            break;
        }
    }

    if (!found)
        printf("❌ Patient with ID %d not found.\n", id);

    fclose(fp);
}


void dischargePatient()
{
  int id;
  struct patient p;
  struct dischargedPatient dp;
  int found = 0;
  char dischargeDate[20];
  char prescription[200];

  FILE *fp = fopen("patients.dat", "rb");
  FILE *temp = fopen("temp.dat", "wb");
  FILE *discharged = fopen("discharged_patients.dat", "ab");

  if (fp == NULL || temp == NULL || discharged == NULL)
  {
    printf("Error opening file!\n");
    return;
  }
  printf("\033[1;32m=== Discharge Patient ===\033[0m\n");
  printf("Enter patient ID to discharge: ");
  scanf("%d", &id);
  getchar();

  while (fread(&p, sizeof(p), 1, fp))
  {
    if (p.id == id)
    {
      found = 1;
      printf("\n--- Patient Found ---\n");
      printf("Patient ID: %d\n", p.id);
      printf("Name: %s\n", p.name);
      printf("Age: %d\n", p.age);
      printf("Disease: %s\n", p.disease);
      printf("Admitted Date: %s\n", p.admittedDate);

      printf("Confirm discharge? (y/n): ");
      char choice;
      scanf(" %c", &choice);
      getchar();
      if (choice == 'Y' || choice == 'y')
      {
        printf("Enter Discharge Date (DD/MM/YYYY): ");
        fgets(dischargeDate, sizeof(dischargeDate), stdin);
        dischargeDate[strcspn(dischargeDate, "\n")] = '\0';

        printf("Enter Prescription: ");
        fgets(prescription, sizeof(prescription), stdin);
        prescription[strcspn(prescription, "\n")] = '\0';

        dp.id = p.id;
        strcpy(dp.name, p.name);
        dp.age = p.age;
        strcpy(dp.gender, p.gender);
        strcpy(dp.disease, p.disease);
        strcpy(dp.contact, p.contact);
        strcpy(dp.admittedDate, p.admittedDate);
        strcpy(dp.dischargeDate, dischargeDate);
        strcpy(dp.prescription, prescription);

        fwrite(&dp, sizeof(dp), 1, discharged);

        printf("\n✅ Patient %s discharged successfully on %s!\n", p.name, dischargeDate);
        printf("📝 Prescription: %s\n", prescription);
        printf("📁 Record saved to discharged patients database.\n");
        continue;
      }
      else
      {
        printf("Discharge cancelled.\n");
      }
    }
    fwrite(&p, sizeof(p), 1, temp);
  }
  fclose(fp);
  fclose(temp);
  fclose(discharged);

  if (found)
  {
    remove("patients.dat");
    rename("temp.dat", "patients.dat");
  }
  else
  {
    remove("temp.dat");
    printf("❌ Patient with ID %d not found.\n", id);
  }
}

void viewDischargedPatients()
{
  struct dischargedPatient dp;
  printf("\033[1;34m=== Discharged Patients List ===\033[0m\n");

  FILE *fp = fopen("discharged_patients.dat", "rb");
  if (fp == NULL)
  {
    printf("No discharged patients found.\n");
    return;
  }
  printf("---------------------------------------------------------------\n");
  int count = 0;
  while (fread(&dp, sizeof(dp), 1, fp))
  {
    printf("Patient ID: %d\n", dp.id);
    printf("Name: %s\n", dp.name);
    printf("Age: %d\n", dp.age);
    printf("Disease: %s\n", dp.disease);
    printf("Admitted Date: %s\n", dp.admittedDate);
    printf("Discharge Date: %s\n", dp.dischargeDate);
    printf("Prescription: %s\n", dp.prescription);
    printf("---------------------------------------------------------------\n");
    count++;
  }

  if (count == 0)
  {
    printf("No discharged patients found.\n");
  }
  else
  {
    printf("Total discharged patients: %d\n", count);
  }
  fclose(fp);
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
    printf("7. View Discharged Patients\n");
    printf("8. Exit Program\n");
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
      updatepatientInfo();
      break;
    case 6:
      // dischargePatient(); // Function to be implemented
      dischargePatient();
      break;
    case 7:
      viewDischargedPatients();
      break;
    case 8:
      printf("Exiting program...\n");
      break;
    default:
      printf("Invalid choice! Please try again.\n");
    }
  } while (choice != 8);
}

int main()
{
  printf("\033[1;32m======================================\033[0m\n");
  printf("\033[1;33m  Welcome to Hospital Management System  \033[0m\n");
  printf("\033[1;32m======================================\033[0m\n");

  menu();
  return 0;
}
