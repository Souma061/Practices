// Banking Management System (BMS) in C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<termios.h>
#include<unistd.h>

#define ADMIN_PASS "admin123"

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


void getPassword(char *password, int maxLen) {
    struct termios oldt, newt;
    int i = 0;
    char ch;

    // Turn off echoing
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ECHO); // Disable echo
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    printf("🔐 Enter admin password: ");
    fflush(stdout);
    


    while (i < maxLen - 1) {
        ch = getchar();
        if (ch == '\n') break;
        if (ch == 127 || ch == '\b') { // Handle backspace
            if (i > 0) {
                i--;
                printf("\b \b");
                fflush(stdout);
            }
        } else {
            password[i++] = ch;
            printf("*");
            fflush(stdout);
        }
    }
    password[i] = '\0';

    // Restore echoing
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    printf("\n");
}
int verifyAdminPassword() {
    char input[50];

    int c;
    while ((c = getchar()) != '\n' && c != EOF);  // Clear buffer

    getPassword(input, sizeof(input));

    if (strcmp(input, ADMIN_PASS) == 0) {
        printf(GREEN "✅ Access granted.\n" RESET);
        return 1;
    } else {
        printf(RED "❌ Incorrect password.\n" RESET);
        return 0;
    }
}

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

void depositMoney()
{
  int accNumber;
  float amount;
  int found = 0;
  struct account acc;

  FILE *fp = fopen("accounts.dat", "rb+");
  if (fp == NULL)
  {
    printf("\033[1;31m❌ Error opening file.\033[0m\n");
    return;
  }
  printf("\033[1;32m=== Deposit Money ===\033[0m\n");
  printf("Enter account number: ");
  scanf("%d", &accNumber);

  while (fread(&acc, sizeof(acc), 1, fp))
  {
    if (acc.accountNumber == accNumber)
    {
      printf(GREEN "✅ Account found: %s\n" RESET, acc.name);
      printf("Current Balance: %.2f\n", acc.balance);
      printf("Enter ammount to deposit: ");
      scanf("%f", &amount);

      if (amount <= 0)
      {
        printf(RED "❌ Invalid amount! Deposit amount must be positive.\n" RESET);
        fclose(fp);
        return;
      }

      acc.balance += amount;
      fseek(fp, -sizeof(acc), SEEK_CUR);
      fwrite(&acc, sizeof(acc), 1, fp);
      printf(GREEN "✅ Deposit successful! New balance: %.2f\n" RESET, acc.balance);
      found = 1;
      break;
    }
  }

  if (!found)
  {
    printf(RED "❌ Account not found.\n" RESET);
  }
  fclose(fp);
}

void withdrawMoney()
{
  int accNumber;
  float amount;
  int found = 0;
  struct account acc;

  FILE *fp = fopen("accounts.dat", "rb+");
  if (fp == NULL)
  {
    printf("\033[1;31m❌ Error opening file.\033[0m\n");
    return;
  }

  printf("\033[1;32m=== Withdraw Money ===\033[0m\n");
  printf("Enter account number: ");
  scanf("%d", &accNumber);

  while (fread(&acc, sizeof(acc), 1, fp))
  {
    if (acc.accountNumber == accNumber)
    {
      printf(GREEN "✅ Account found: %s\n" RESET, acc.name);
      printf("Current Balance: %.2f\n", acc.balance);
      printf("Enter amount to withdraw: ");
      scanf("%f", &amount);

      if (amount <= 0 || amount > acc.balance)
      {
        printf(RED "❌ Invalid amount! Withdrawal amount must be positive and less than or equal to current balance.\n" RESET);
        fclose(fp);
        return;
      }

      acc.balance -= amount;
      fseek(fp, -sizeof(acc), SEEK_CUR);
      fwrite(&acc, sizeof(acc), 1, fp);
      printf(GREEN "✅ Withdrawal successful! New balance: %.2f\n" RESET, acc.balance);
      found = 1;
      break;
    }
  }

  if (!found)
  {
    printf(RED "❌ Account not found.\n" RESET);
  }
  fclose(fp);
}

void searchAccount()
{
  int accNumber;
  int found = 0;
  struct account acc;

  FILE *fp = fopen("accounts.dat", "rb");
  if (fp == NULL)
  {
    printf("\033[1;31m❌ Error opening file.\033[0m\n");
    return;
  }

  printf("\033[1;32m=== Search Account ===\033[0m\n");
  printf("Enter your account number: ");
  scanf("%d", &accNumber);

  while (fread(&acc, sizeof(acc), 1, fp))
  {
    if (acc.accountNumber == accNumber)
    {
      printf(GREEN "✅ Account found:\n" RESET);
      printf("Account Number: %d\n", acc.accountNumber);
      printf("Name: %s\n", acc.name);
      printf("Email: %s\n", acc.email);
      printf("Phone: %s\n", acc.phone);
      printf("Balance: %.2f\n", acc.balance);
      found = 1;
      break;
    }
  }

  if (!found)
  {
    printf(RED "❌ Account not found.\n" RESET);
  }
  fclose(fp);
}

void deleteAccount()
{
  if(!verifyAdminPassword()) {
    return;
  }
  int accNumber;
  int found = 0;
  struct account acc;

  FILE *fp = fopen("accounts.dat", "rb");
  FILE *temp = fopen("temp.dat", "wb");
  if (fp == NULL || temp == NULL)
  {
    printf(RED "❌ Error opening file.\n" RESET);
    return;
  }

  printf(GREEN "=== Delete Account ===\n" RESET);
  printf("Enter the account number to delete: ");
  scanf("%d", &accNumber);

  while (fread(&acc, sizeof(acc), 1, fp))
  {
    if (acc.accountNumber == accNumber)
    {
      printf(GREEN "✅ Account found: %s\n" RESET, acc.name);
      printf("Are you sure you want to delete this account? (y/n): ");
      char choice;
      getchar(); // flush newline
      scanf("%c", &choice);

      if (choice == 'Y' || choice == 'y')
      {
        printf(GREEN "✅ Account deleted successfully.\n" RESET);
        found = 1;
        // Skip writing this record to temp — means deleted
        continue;
      }
    }
    // Write all other records, including when user chooses NOT to delete
    fwrite(&acc, sizeof(acc), 1, temp);
  }

  fclose(fp);
  fclose(temp);

  if (found)
  {
    remove("accounts.dat");
    rename("temp.dat", "accounts.dat");
  }
  else
  {
    remove("temp.dat");
    printf(RED "❌ Account not found or deletion cancelled.\n" RESET);
  }
}

void updateAccount()
{
  int accNumber;
  int found = 0;
  struct account acc;

  FILE *fp = fopen("accounts.dat", "rb+");
  if (fp == NULL)
  {
    printf("\033[1;31m❌ Error opening file.\033[0m\n");
    return;
  }
  printf("\033[1;32m=== Update Account ===\033[0m\n");
  printf("Enter account number to update: ");
  scanf("%d", &accNumber);
  getchar(); // clear newline

  while (fread(&acc, sizeof(acc), 1, fp))
  {
    if (acc.accountNumber == accNumber)
    {
      found = 1;
      printf(GREEN "✅ Account found: %s\n" RESET, acc.name);
      printf("Current Balance: %.2f\n", acc.balance);
      printf("Enter new Name: ");
      fgets(acc.name, sizeof(acc.name), stdin);
      acc.name[strcspn(acc.name, "\n")] = '\0';

      printf("Enter new Email: ");
      fgets(acc.email, sizeof(acc.email), stdin);
      acc.email[strcspn(acc.email, "\n")] = '\0';

      printf("Enter new Phone Number: ");
      fgets(acc.phone, sizeof(acc.phone), stdin);
      acc.phone[strcspn(acc.phone, "\n")] = '\0';

      printf("Enter new Balance: ");
      scanf("%f", &acc.balance);

      if (acc.accountNumber <= 0 || acc.balance < 0)
      {
        printf(RED "❌ Invalid input! Account number and balance must be non-negative.\033[0m\n");
        fclose(fp);
        return;
      }
      fseek(fp, -sizeof(acc), SEEK_CUR);
      fwrite(&acc, sizeof(acc), 1, fp);
      printf(GREEN "✅ Account updated successfully!\n" RESET);
      break;
    }
  }

  if (!found)
  {
    printf(RED "❌ Account with number %d not found.\n" RESET, accNumber);
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
    case 2:
      viewAccounts();
      break;
    case 3:
      depositMoney();
      break;
    case 4:
      withdrawMoney();
      break;
    case 5:
      searchAccount();
      break;
    case 6:
      deleteAccount();
      break;
    case 7:
      updateAccount();
      break;
    case 8:
      printf(CYAN "👋 Exiting program. Goodbye!\n" RESET);
      break;
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
