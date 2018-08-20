#ifndef CLIST_H
#define CLIST_H

#include <stdlib.h>
#include <stdio.h>

typedef struct data_{
int x;
struct data_ * next;
}Node;
typedef Node* List;


void printList(List head);
void freePrintList(List head);

List newNode(int x);

List appendTail(List ptr,int x);
List appendHead(List ptr, int x);

#endif
