/*
    bdus@Oct/2 2018

    g++ -o out -std=c++11 singly_linked_list.cpp

    https://en.wikipedia.org/wiki/Linked_list#Singly_linked_list

    https://leetcode.com/problems/middle-of-the-linked-list/description/


*/

#include<iostream>
#include<vector>
#include<stdlib.h>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
 };
 
 typedef struct ListNode * llist;

void print(llist head)
{
    if(NULL == head)
        std::cout << "empty" << std::endl;
    while(head != NULL)
    {
        cout <<  head->val << endl;
        head = head->next;
    }
}
ListNode* reverseList(ListNode* head) {
    
    if(NULL == head)
        return head;
    
    llist bk = NULL;
    llist ans = NULL;

    while(NULL != head)
    {
        bk = ans;
        ans = head;

        head = head->next;
        ans->next = bk;
    }
    return ans;
}
ListNode* middleNode(ListNode* head) {
    typedef struct ListNode * llist;
    vector<llist> a;
    int length = 0;

    if(NULL == head)
        return head;
    while(NULL != head)    
    {
        length++;
        a.push_back(head);
        head = head->next;
    }
    return a[(int)(length/2)];
}
void deleteNode(ListNode* node) {
    //*node = *node->next;
    ListNode* temp = node->next;
    node->val = node->next->val;
    node->next = temp->next;
    delete temp;
}

int main()
{
    int list_init[] = {0,1,2,3,4,5,6,7,8,9};

        //new list
    llist head = NULL;//= newNode(-1); "没有"头节点
    llist op = NULL;

    int len = sizeof(list_init)/sizeof(int);  
    for(int i = 0; i < len; i++ )
    {
        //头插 ...都没有头节点 hh        
        op = head;
        head = new ListNode(i);
        head->next = op;                                
    }
    print(head);
    //print(reverseList(head));
    //print(middleNode(head));
    deleteNode(head);
    cout << '\n';
    print(head);


    return 0;
}