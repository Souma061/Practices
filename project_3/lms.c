// Library Management System (LMS) in C11

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct library{
  int ID;
  char bookName[50];
  char author[50];
  int quantity;
};

void addBook() {
  FILE *fp;
  struct library book;

  fp = fopen("library.txt" , "ab");
  if(fp == NULL) {
    printf("Error opening file;\n");
    return;
  }

  printf("Enter Book ID: ");
  scanf("%d" , &book.ID);
  getchar();

  printf("Enter Book name: ");
  fgets(book.bookName, sizeof(book.bookName), stdin);
  book.bookName[strcspn(book.bookName, "\n")] = '\0';

  printf("Enter Author name: ");
  fgets(book.author, sizeof(book.author) , stdin);
  book.author[strcspn(book.author, "\n")] = '\0';

  printf("Enter Quantity: ");
  scanf("%d" , &book.quantity);
  getchar();

  fwrite(&book, sizeof(book) , 1 , fp);
  fclose(fp);

  printf("\n✅ Book added successfully!\n");
}

void displayBooks() {
  FILE *fp;
  struct library book;
  int found = 0;

  fp = fopen("library.txt" , "rb");
  if(fp == NULL) {
    printf("Error opening file.\n");
    return;
  }

  printf("\n📚 List of Books:\n");
  while(fread(&book, sizeof(book) , 1 , fp)) {
    found = 1;
    printf("-------------------------\n");
    printf("ID: %d\n" , book.ID);
    printf("Book Name: %s\n" , book.bookName);
    printf("Author: %s\n" , book.author);
    printf("Quantity: %d\n" , book.quantity);
    printf("-------------------------\n");
  }
  if(!found) {
    printf("📭 No books found in the library.\n");
  }
  fclose(fp);

}

void searchBook() {
  FILE *fp;
  struct library book;
  int found = 0, searchID;

  fp = fopen("library.txt" , "rb");
  if(fp == NULL) {
    printf("Error opening file.\n");
    return;
  }
   printf("Enter Book ID to search: ");
   scanf("%d" , &searchID);

   while(fread(&book, sizeof(book) , 1 , fp)) {
    if(book.ID == searchID) {
      found = 1;
      printf("\n📖 Book Found:\n");
      printf("-------------------------\n");
      printf("ID: %d\n" , book.ID);
      printf("Book Name: %s\n" , book.bookName);
      printf("Author: %s\n" , book.author);
      printf("Quantity: %d\n" , book.quantity);
      printf("-------------------------\n");
      break;
    }
   }
   if(!found) {
    printf("❌ Book with ID %d not found.\n", searchID);
   }
   fclose(fp);
}

void deleteBook() {
  FILE *fp, *temp;
  struct library book;
  int found = 0, deleteID;

  fp = fopen("library.txt" , "rb");
  temp = fopen("temp.txt" , "wb");

  if(fp == NULL || temp == NULL) {
    printf("Error opening file.\n");
    return;
  }

  printf("Enter Book ID to delete: ");
  scanf("%d" , &deleteID);

  while(fread(&book, sizeof(book) , 1 , fp)) {
    if(book.ID == deleteID) {
      found = 1;
      printf("Book with ID %d deleted successfully.\n", deleteID);
      continue;;
    }
    fwrite(&book , sizeof(book) , 1 , temp);
  }
  fclose(fp);
  fclose(temp);

  remove("library.txt");
  rename("temp.txt" , "library.txt");

  if(!found) {
    printf("❌ Book with ID %d not found.\n", deleteID);
  } else {
    printf("✅ Book deleted successfully!\n");
  }
}

void updateBook() {
  
}


int main() {
  addBook();
  displayBooks();
  searchBook();
  deleteBook();
  return 0;
}

