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

  fp = fopen("library.txt" , "a");
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


int main() {
  addBook();
  return 0;
}

