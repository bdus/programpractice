/*
    bdus @ 2018.9.29
    gcc -o out -std=c99 singly_linked_list.c
    还是参考git上
    https://github.com/chenyufeng1991/LinkedList_HeadNode/blob/master/LinkedList_HeadNode/main.c
    https://algorithm.yuanbin.me/zh-hans/basics_data_structure/linked_list.html
*/
#include <stdio.h>
#include <stdlib.h>
typedef struct ListNode {
    int val;
    struct ListNode *next;
}list;

list * newNode(int val)
{
    list * aNode = malloc(sizeof(list));
    aNode->val = val;
    aNode->next = NULL;
    return aNode;
}

void print(list * head)
{
    if(NULL == head)
        printf("empty\n");
    while(head != NULL)
    {
        printf("%d\n",head->val);
        head = head->next;
    }
}
void destroy(list * head)// problems
{
    if(NULL == head)
        return;
    list * bk;

    while(head != NULL)
    {
        bk = head;
        head = head->next;
        free(bk);
    }
    head = NULL;
}
struct ListNode* reverseList(struct ListNode* head) {
    list * op = NULL;
    list * ans = NULL;

    if(NULL == head)
        return NULL;
    
    while(head != NULL)
    {
        op = ans;
        ans = head;

        head = head->next;
        ans->next = op;
    }
    return ans;
}
int main()
{
    int list_init[] = {0,1,2,3,4,5,6,7,8,9};

    //new list
    list * head = NULL;//= newNode(-1); "没有"头节点
    list * op = NULL;

    int len = sizeof(list_init)/sizeof(int);  
    for(int i = 0; i < len; i++ )
    {
        //头插 ...都没有头节点 hh        
        op = head;//->next;        
        head = newNode(list_init[i]);
        head->next = op;                                
    }
    print(head);

    print(reverseList(head));
    
    destroy(head);
    // print(head);

    return 0;
}
