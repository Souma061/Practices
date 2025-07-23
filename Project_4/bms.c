// Banking Management System (BMS) in C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RESET "\033[0m"
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define BLUE "\033[1;34m"
#define CYAN "\033[1;36m"

// struct declaration
// menu()
// createAccount()
// viewAccounts()
// viewBalance()        ✅ ← Add here (after viewAccounts for logical grouping)
// deposit()
// withdraw()
// searchAccount()
// deleteAccount()
// updateAccount()
// file I/O helpers
// main()

struct account
{
  int accountNumber;
  char name[50];
  char email[50];
  char phone[15];
  float balance;
};

void createAccount()
{
  FILE *fp;
  struct account acc;

  printf("\033[1;32m=== Create New Account ===\033[0m\n");

  printf("Enter Account Number: ");
  scanf("%d", &acc.accountNumber);
  getchar(); // clear newline

  printf("Enter Name: ");
  fgets(acc.name, sizeof(acc.name), stdin);
  acc.name[strcspn(acc.name, "\n")] = '\0';

  printf("Enter Email:");
  fgets(acc.email, sizeof(acc.email), stdin);
  acc.email[strcspn(acc.email, "\n")] = '\0';

  printf("Enter Phone Number: ");
  fgets(acc.phone, sizeof(acc.phone), stdin);
  acc.phone[strcspn(acc.phone, "\n")] = '\0';

  printf("Enter Initial Balance: ");
  scanf("%f", &acc.balance);

  if (acc.accountNumber <= 0 || acc.balance < 0)
  {
    printf("\033[1;31m❌ Invalid input! Account number and balance must be non-negative.\033[0m\n");
    return;
  }
  int exists = 0;
  struct account temp;
  fp = fopen("accounts.dat", "rb");
  if (fp == NULL)
  {
    printf("\033[1;31m❌ Error opening file.\033[0m\n");
    return;
  }

  while (fp && fread(&temp, sizeof(struct account), 1, fp))
  {
    if (temp.accountNumber == acc.accountNumber)
    {
      exists = 1;
      break;
    }
  }

  if (fp)
    fclose(fp);

  if (exists)
  {
    printf("\033[1;31m❌ Account with this number already exists.\033[0m\n");
    return;
  }

  fp = fopen("accounts.dat", "ab");
  if (fp == NULL)
  {
    printf("\033[1;31m❌ Error opening file.\033[0m\n");
    return;
  }

  fwrite(&acc, sizeof(struct account), 1, fp);
  fclose(fp);

  printf("\033[1;32m✅ Account created successfully!\033[0m\n");
}

void viewAccounts()
{
  FILE *fp;
  struct account acc;
  printf("\033[1;32m=== View All Accounts ===\033[0m\n");
  fp = fopen("accounts.dat", "rb");

  if (fp == NULL)
  {
    printf("\033[1;31m❌ Error opening file.\033[0m\n");
    return;
  }


  printf("---------------------------------------------------------------\n");

  while (fread(&acc, sizeof(struct account), 1, fp))
  {
    printf(YELLOW "Account Number: %d\n" RESET, acc.accountNumber);
    printf("Name: %s\n", acc.name);
    printf("Email: %s\n", acc.email);
    printf("Phone: %s\n", acc.phone);
    printf("Balance: %.2f\n", acc.balance);
    printf("---------------------------------------------------------------\n");
  }
  fclose(fp);
}



void menu()
{
  int choice;
  do
  {
    printf("\033[1;34m\n🏦 Bank Management Menu:\033[0m\n");
    printf("1. Create Account\n");
    printf("2. View All Accounts\n");
    printf("3. Deposit Money\n");
    printf("4. Withdraw Money\n");
    printf("5. Search Account by ID\n");
    printf("6. Delete Account\n");
    printf("7. Update Account\n");
    printf("8. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
      createAccount();
      break;
    case 2: viewAccounts(); break;
    // case 3: deposit(); break;
    // case 4: withdraw(); break;
    // case 5: searchAccount(); break;
    // case 6: deleteAccount(); break;
    // case 7: updateAccount(); break;
    // case 8: printf("👋 Exiting. Goodbye!\n"); break;
    default:
      printf("❌ Invalid choice.\n");
    }
  } while (choice != 8);
}

int main()
{
  printf("\033[1;32m======================================\033[0m\n");
  printf("\033[1;33m  Welcome to Bank Management System  \033[0m\n");
  printf("\033[1;32m======================================\033[0m\n");

  menu();
  return 0;
}
