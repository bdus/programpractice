#include <stdlib.h>
#include <stdio.h>

#include "clist.h"

#define DEBUG(x) putchar("123456789"[x%10]);

/*
typedef struct data_{
int x;
struct data_ * next;
}Node;
typedef Node* List;


void printList(List head)
{
    if(head == NULL)
        printf("List is empty\n");

    while(head != NULL)
    {
        //putchar('a'+head->x);
        printf("num %d\n",head->x);
        head = head->next;
    }
}
void freePrintList(List head)
{
    List last;
    while(head != NULL)
    {
        last = head;
        printf("num %d\n",head->x);
        head = head->next;
        free(last);
    }
}

List newNode(int x)
{
    List node = (List)malloc(sizeof(Node));
    node->x = x;
    node->next = NULL;
    return node;
}

List appendTail(List ptr,int x)
{
    if(ptr == NULL)
        return newNode(x);
    List head = ptr;
    while(ptr->next != NULL)
    {
       ptr = ptr->next;    
    }     
    ptr->next = newNode(x);
    return head;
}
List appendHead(List ptr, int x)
{
    List tmp = NULL;
    tmp = ptr;
    ptr = newNode(x);
    ptr->next = tmp;
    return ptr;
}*/

int main()
{
    int var[] = {1,2,3,4,5,6,7};

    //DEBUG(0)
    //new a empty list
    List ptr = NULL;
    //
    ptr = appendTail(ptr,1);
    ptr = appendHead(ptr,3);
    ptr = appendHead(ptr,2);
    
    //printList(head);
    freePrintList(ptr);
    
    return 0;
}
