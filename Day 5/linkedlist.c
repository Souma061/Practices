#include <stdio.h>
#include <stdlib.h>

// Define the structure for a linked list node
struct Node
{
  int data;          // data field to store integer values
  struct Node *next; // pointer to the next node in the list
};

void display(struct Node *head)
{
  struct Node *temp = head;
  while (temp != NULL)
  {
    printf("%d -> ", temp->data);
    temp = temp->next;
  }
  printf("NULL\n"); // indicate the end of the list
}

void insertAtBeginning(struct Node **head_ref, int newData)
{
  struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
  new_node->data = newData;
  new_node->next = (*head_ref);
  *head_ref = new_node;
}

void insertAtEnd(struct Node *head, int newData)
{
  struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
  new_node->data = newData;
  new_node->next = NULL;

  struct Node *temp = head;
  while (temp->next != NULL)
  {
    temp = temp->next;
  }
  temp->next = new_node; // link the new node at the end of the list
}

int main()
{
  struct Node *head = NULL;

  // creating first node

  head = (struct Node *)malloc(sizeof(struct Node));
  head->data = 10;   // assign data to the first node
  head->next = NULL; // set the next pointer to NULL

  // second node
  struct Node *second = (struct Node *)malloc(sizeof(struct Node));
  second->data = 20;   // assign data to the second node
  second->next = NULL; // set the next pointer to NULL

  head->next = second; // link the first node to the second node

  // third node

  struct Node *third = (struct Node *)malloc(sizeof(struct Node));
  third->data = 30;
  third->next = NULL;

  second->next = third;

  insertAtBeginning(&head, 5);
  insertAtEnd(head, 50);

  display(head); // display the linked list

  printf("First node created with data: %d\n", head->data);
  printf("Second node created with data: %d\n", second->data);
  printf("Third node created with data: %d\n", third->data);
}
