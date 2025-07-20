#include<stdio.h>
#include<stdlib.h>

struct Node{
  int data;
  struct Node *next;
};

int main() {
  struct Node *head = (struct Node *)malloc(sizeof(struct Node));
  struct Node *second = (struct Node *)malloc(sizeof(struct Node));
  struct Node *third = (struct Node *)malloc(sizeof(struct Node));
  struct Node *fourth = (struct Node *)malloc(sizeof(struct Node));

  head->data = 5;
  head->next = second;

  second->data = 10;
  second->next = third;

  third->data = 15;
  third->next = fourth;

  fourth->data = 1223;
  fourth->next = NULL;

  printf("Linked List: \n");
  struct Node *current = head;
  while (current != NULL) {
    printf("%d -> ", current->data);
    current = current->next;
  }
  printf("NULL\n");

  return 0;



}
