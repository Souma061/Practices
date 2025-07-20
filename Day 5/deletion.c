#include <stdio.h>
#include <stdlib.h>

struct Node
{
  int data;
  struct Node *next;
};

// delete a node at the beginning

struct Node *deleteAtBeginning(struct Node *head)
{
  if (head == NULL)
  {
    printf("List is empty\n");
    return NULL;
  }

  struct Node *ptr = head;
  head = head->next;
  free(ptr);
  return head;
}

// delete a node at a given index
struct Node *deleteAtIndex(struct Node *head, int index)
{
  if (head == NULL)
  {
    printf("List is empty\n");
    return NULL;
  }

  if (index < 0)
  {
    printf("Invalid index\n");
    return head;
  }

  if (index == 0)
  {
    return deleteAtBeginning(head);
  }

  struct Node *p = head;
  struct Node *q = head->next;
  int i = 0;

  while (i != index - 1 && q != NULL)
  {
    p = p->next;
    q = q->next;
    i++;
  }

  if (q != NULL)
  {
    p->next = q->next;
    free(q);
  }
  else
  {
    printf("Index out of bounds\n");
  }

  return head;
}
// delet athe last node
 struct Node *deleteAtEnd(struct Node *head) {
  if(head == NULL) {
    printf("List is empty\n");
    return NULL;
  }
  if(head->next == NULL) {
    free(head);
    return NULL;
  }
  struct Node *p = head;
  while(p->next->next != NULL) {
    p = p->next;
  }
  free(p->next);
  p->next = NULL;
  return head;
}

void traversal(struct Node *ptr)
{
  while (ptr != NULL)
  {

    printf("%d\n", ptr->data);
    ptr = ptr->next;
  }
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

  // printf("Testing deletion at index 1:\n");
  // head = deleteAtIndex(head, 1);
  // printf("After deletion at index 1:\n");
  // traversal(head);

  // printf("\nTesting deletion at index 0:\n");
  // head = deleteAtIndex(head, 0);
  // printf("After deletion at index 0:\n");
  // traversal(head);

  // printf("\nTesting deletion at invalid index:\n");
  // head = deleteAtIndex(head, 5);
  // printf("After attempting deletion at index 5:\n");
  // traversal(head);

  head = deleteAtEnd(head);
  printf("\nAfter deleting the last node:\n");
  traversal(head);

  return 0;
}
