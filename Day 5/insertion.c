#include <stdio.h>
#include <stdlib.h>

struct Node
{
  int data;
  struct Node *next;
};

void traversal(struct Node *ptr)
{
  while (ptr != NULL)
  {

    printf("%d\n", ptr->data);
    ptr = ptr->next;
  }
}

struct Node *insertAtBeginning(struct Node *head, int newData)
{
  struct Node *ptr = (struct Node *)malloc(sizeof(struct Node));

  ptr->data = newData;
  ptr->next = head;
  return ptr;
}

struct Node *insertInBetween(struct Node *head, int newData, int index)
{
  struct Node *ptr = (struct Node *)malloc(sizeof(struct Node));
  struct Node *p = head;
  int i = 0;

  while (i != index - 1 && p != NULL)
  {
    p = p->next;
    i++;
  }
  ptr->data = newData;
  ptr->next = p->next;
  p->next = ptr;
  return head;
}

struct Node *insertAtEnd(struct Node *head, int newData)
{
  struct Node *ptr = (struct Node *)malloc(sizeof(struct Node));
  struct Node *p = head;

  ptr->data = newData;
  ptr->next = NULL;

  if (head == NULL)
  {
    return ptr;
  }

  while (p->next != NULL)
  {
    p = p->next;
  }
  p->next = ptr;
  ptr->next = NULL;
  return head;
}

struct Node *insertAfterNode(struct Node *head, struct Node *prevNode, int newData)
{
  // Check if prevNode is NULL
  if (prevNode == NULL)
  {
    printf("Error: prevNode is NULL\n");
    return head;
  }

  struct Node *ptr = (struct Node *)malloc(sizeof(struct Node));
  ptr->data = newData;

  ptr->next = prevNode->next;
  prevNode->next = ptr;
  return head;
}

int main()
{
  struct Node *head = (struct Node *)malloc(sizeof(struct Node));
  struct Node *second = (struct Node *)malloc(sizeof(struct Node));
  struct Node *third = (struct Node *)malloc(sizeof(struct Node));

  head->data = 5;
  head->next = second;

  second->data = 10;
  second->next = third;

  third->data = 15;
  third->next = NULL;
  traversal(head);
  head = insertAtBeginning(head, 100);
  printf("After insertion at beginning:\n");
  traversal(head);
  head = insertInBetween(head, 50, 1);
  printf("After insertion in between:\n");
  traversal(head);
  head = insertAtEnd(head, 516546);
  printf("After insertion at end:\n");
  traversal(head);

  // Alternative: Using the original third pointer directly
  // Note: This works because 'third' still points to the same node
  // even after other insertions, but it's generally safer to search by value
  head = insertAfterNode(head, third, 999);
  printf("After insertion after original third pointer:\n");
  traversal(head);

  // Find the node with value 15 (which is the third node) and insert after it
  struct Node *nodeToInsertAfter = head;
  while (nodeToInsertAfter != NULL && nodeToInsertAfter->data != 15)
  {
    nodeToInsertAfter = nodeToInsertAfter->next;
  }

  if (nodeToInsertAfter != NULL)
  {
    head = insertAfterNode(head, nodeToInsertAfter, 789);
    printf("After insertion after node with value 15 (third node):\n");
    traversal(head);
  }
  else
  {
    printf("Node with value 15 not found\n");
  }

  return 0;
}
/*#include<stdio.h>
#include<stdlib.h>

struct Node{
    int data;
    struct Node * next;
};

void linkedListTraversal(struct Node *ptr)
{
    while (ptr != NULL)
    {
        printf("Element: %d\n", ptr->data);
        ptr = ptr->next;
    }
}

// Case 1
struct Node * insertAtFirst(struct Node *head, int data){
    struct Node * ptr = (struct Node *) malloc(sizeof(struct Node));
    ptr->data = data;

    ptr->next = head;
    return ptr;
}

// Case 2
struct Node * insertAtIndex(struct Node *head, int data, int index){
    struct Node * ptr = (struct Node *) malloc(sizeof(struct Node));
    struct Node * p = head;
    int i = 0;

    while (i!=index-1)
    {
        p = p->next;
        i++;
    }
    ptr->data = data;
    ptr->next = p->next;
    p->next = ptr;
    return head;
}

// Case 3
struct Node * insertAtEnd(struct Node *head, int data){
    struct Node * ptr = (struct Node *) malloc(sizeof(struct Node));
    ptr->data = data;
    struct Node * p = head;

    while(p->next!=NULL){
        p = p->next;
    }
    p->next = ptr;
    ptr->next = NULL;
    return head;
}

// Case 4
struct Node * insertAfterNode(struct Node *head, struct Node *prevNode, int data){
    struct Node * ptr = (struct Node *) malloc(sizeof(struct Node));
    ptr->data = data;

    ptr->next = prevNode->next;
    prevNode->next = ptr;


    return head;
}


int main(){
    struct Node *head;
    struct Node *second;
    struct Node *third;
    struct Node *fourth;

    // Allocate memory for nodes in the linked list in Heap
    head = (struct Node *)malloc(sizeof(struct Node));
    second = (struct Node *)malloc(sizeof(struct Node));
    third = (struct Node *)malloc(sizeof(struct Node));
    fourth = (struct Node *)malloc(sizeof(struct Node));

    // Link first and second nodes
    head->data = 7;
    head->next = second;

    // Link second and third nodes
    second->data = 11;
    second->next = third;

    // Link third and fourth nodes
    third->data = 41;
    third->next = fourth;

    // Terminate the list at the third node
    fourth->data = 66;
    fourth->next = NULL;

    printf("Linked list before insertion\n");
    linkedListTraversal(head);
    // head = insertAtFirst(head, 56);
    // head = insertAtIndex(head, 56, 1);
    // head = insertAtEnd(head, 56);
    head = insertAfterNode(head, third, 45);
    printf("\nLinked list after insertion\n");
    linkedListTraversal(head);


    return 0;
}*/
