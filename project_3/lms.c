// Library Management System (LMS) in C11

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct library
{
  int ID;
  char bookName[50];
  char author[50];
  int quantity;
};

void addBook()
{
  FILE *fp;
  struct library book;

  fp = fopen("library.txt", "ab");
  if (fp == NULL)
  {
    printf("Error opening file;\n");
    return;
  }

  printf("Enter Book ID: ");
  scanf("%d", &book.ID);
  getchar();

  printf("Enter Book name: ");
  fgets(book.bookName, sizeof(book.bookName), stdin);
  book.bookName[strcspn(book.bookName, "\n")] = '\0';

  printf("Enter Author name: ");
  fgets(book.author, sizeof(book.author), stdin);
  book.author[strcspn(book.author, "\n")] = '\0';

  printf("Enter Quantity: ");
  scanf("%d", &book.quantity);
  getchar();

  fwrite(&book, sizeof(book), 1, fp);
  fclose(fp);

  printf("\n✅ Book added successfully!\n");
}

void displayBooks()
{
  FILE *fp;
  struct library book;
  int found = 0;

  fp = fopen("library.txt", "rb");
  if (fp == NULL)
  {
    printf("Error opening file.\n");
    return;
  }

  printf("\n📚 List of Books:\n");
  while (fread(&book, sizeof(book), 1, fp))
  {
    found = 1;
    printf("-------------------------\n");
    printf("ID: %d\n", book.ID);
    printf("Book Name: %s\n", book.bookName);
    printf("Author: %s\n", book.author);
    printf("Quantity: %d\n", book.quantity);
    printf("-------------------------\n");
  }
  if (!found)
  {
    printf("📭 No books found in the library.\n");
  }
  fclose(fp);
}

void searchBook()
{
  FILE *fp;
  struct library book;
  int found = 0, searchID;

  fp = fopen("library.txt", "rb");
  if (fp == NULL)
  {
    printf("Error opening file.\n");
    return;
  }
  printf("Enter Book ID to search: ");
  scanf("%d", &searchID);

  while (fread(&book, sizeof(book), 1, fp))
  {
    if (book.ID == searchID)
    {
      found = 1;
      printf("\n📖 Book Found:\n");
      printf("-------------------------\n");
      printf("ID: %d\n", book.ID);
      printf("Book Name: %s\n", book.bookName);
      printf("Author: %s\n", book.author);
      printf("Quantity: %d\n", book.quantity);
      printf("-------------------------\n");
      break;
    }
  }
  if (!found)
  {
    printf("❌ Book with ID %d not found.\n", searchID);
  }
  fclose(fp);
}

void deleteBook()
{
  FILE *fp, *temp;
  struct library book;
  int found = 0, deleteID;

  fp = fopen("library.txt", "rb");
  temp = fopen("temp.txt", "wb");

  if (fp == NULL || temp == NULL)
  {
    printf("Error opening file.\n");
    return;
  }

  printf("Enter Book ID to delete: ");
  scanf("%d", &deleteID);

  while (fread(&book, sizeof(book), 1, fp))
  {
    if (book.ID == deleteID)
    {
      found = 1;
      printf("Book with ID %d deleted successfully.\n", deleteID);
      continue;
      ;
    }
    fwrite(&book, sizeof(book), 1, temp);
  }
  fclose(fp);
  fclose(temp);

  remove("library.txt");
  rename("temp.txt", "library.txt");

  if (!found)
  {
    printf("❌ Book with ID %d not found.\n", deleteID);
  }
  else
  {
    printf("✅ Book deleted successfully!\n");
  }
}

void updateBook()
{
  FILE *fp, *temp;
  struct library book;
  int found = 0, updateID;

  fp = fopen("library.txt", "rb");
  temp = fopen("temp.txt", "wb");

  if (fp == NULL || temp == NULL)
  {
    printf("Error opening file.\n");
    return;
  }

  printf("Enter Book ID to update: ");
  scanf("%d", &updateID);

  while (fread(&book, sizeof(book), 1, fp))
  {
    if (book.ID == updateID)
    {
      found = 1;
      printf("Enter new Book Name: ");
      getchar();
      fgets(book.bookName, sizeof(book.bookName), stdin);
      book.bookName[strcspn(book.bookName, "\n")] = '\0';

      printf("Enter new Author Name: ");
      fgets(book.author, sizeof(book.author), stdin);
      book.author[strcspn(book.author, "\n")] = '\0';

      printf("Enter new Quantity: ");
      scanf("%d", &book.quantity);
      getchar();
      printf("Book with ID %d updated successfully.\n", updateID);
    }
    fwrite(&book, sizeof(book), 1, temp);
  }
  fclose(fp);
  fclose(temp);
  remove("library.txt");
  rename("temp.txt", "library.txt");

  if (!found)
  {
    printf("❌ Book with ID %d not found.\n", updateID);
  }
  else
  {
    printf("✅ Book updated successfully!\n");
  }
}

void menu()
{
  int choice;

  do
  {
    printf("\n📘 Library Management Menu:\n");
    printf("1. Add Book\n");
    printf("2. Display All Books\n");
    printf("3. Search Book by ID\n");
    printf("4. Delete Book by ID\n");
    printf("5. Update Book by ID\n");
    printf("6. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    getchar(); // clear newline

    switch (choice)
    {
    case 1:
      addBook();
      break;
    case 2:
      displayBooks();
      break;
    case 3:
      searchBook();
      break;
    case 4:
      deleteBook();
      break;
    case 5:
      updateBook();
      break;
    case 6:
      printf("👋 Exiting program. Goodbye!\n");
      break;
    default:
      printf("❌ Invalid choice! Please try again.\n");
    }

  } while (choice != 6);
}

int main()
{
  printf("=========================================\n");
  printf("   📚 Welcome to Library Management System! 📚\n");
  printf("=========================================\n");

  menu();

  return 0;
}
