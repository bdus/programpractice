/*
    bdus@Oct/26 2018

    g++ -o out -std=c++11 21.cpp

    https://en.wikipedia.org/wiki/Linked_list#Singly_linked_list

    https://leetcode.com/problems/merge-two-sorted-lists/


*/
// #include<iostream>
// #include<vector>

// using namespace std;

// struct ListNode {
//     int val;
//     ListNode *next;
//     ListNode(int x) : val(x), next(NULL) {}
//  };

//  typedef struct ListNode * llist;


// void print(llist head)
// {
//     if(NULL == head)
//         std::cout << "empty" << std::endl;
//     while(head != NULL)
//     {
//         cout <<  head->val << endl;
//         head = head->next;
//     }
// }

// ListNode* reverseList(ListNode* head) {
    
//     if(NULL == head)
//         return head;
    
//     llist bk = NULL;
//     llist ans = NULL;

//     while(NULL != head)
//     {
//         bk = ans;
//         ans = head;

//         head = head->next;
//         ans->next = bk;
//     }
//     return ans;
// }

// void deleteNode(ListNode* node) {
//     //*node = *node->next;
//     ListNode* temp = node->next;
//     node->val = node->next->val;
//     node->next = temp->next;
//     delete temp;
// }


#include "linked_list.h"

template <class T>
int getLen(T& array)
{
   return (sizeof(array) / sizeof(array[0]));
}

void assignment(int list[], int len, llist & l_head)
{    
    llist op = NULL;    
    //int len = sizeof(list)/sizeof(list[0]); 
    for(int i = 0; i < len; i++ )
    {
        //头插 ...都没有头节点 hh        
        op = l_head;
        l_head = new ListNode(list[i]);
        l_head->next = op;                                
    }
    l_head = reverseList(l_head);
}
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if(!l1)
            return l2;
        if(!l2)
            return l1;
        
        ListNode* ls1 =l1;
        ListNode* ls2 = l2;
        ListNode* prev = ls1;
        ListNode* head = l1;
        
        // 有1个到了尾部就可以退出循环
        
        int i =0;
        while(ls1 && ls2)
        {

            if(ls1->val<=ls2->val) 
            {
                prev =ls1;
                ls1= ls1->next;              
            }
            else  // ls2 > ls1, 把ls2连接到 ls1之前的位置，然后ls1不往下移动，ls2指向原来的ls2->next
            {
                ListNode* tmp1 = ls1->next;
                ListNode* tmp2 = ls2->next;
                if(ls1 ==head)//说明ls1第一个值就比ls2大。这不能用prev,因为prev=头部有可能是，第一个ls1小，ls1移到
                {            // 第二个位置，prev 当时指在第一个位置
                    ls2->next = ls1;
                    if(ls2 == l2) // 这个时候ls2的第一个值，小于ls1的第一个值，所以ls2的第一个值肯定是头
                    {
                       head=ls2;
                    }
                    prev = ls2;
                    
                  //  cout<<ls1->val<<";"<<ls2->val<<";"<<prev->val<<"\n";
                }   
                else
                {
                    prev->next = ls2;
                    ls2->next =ls1;
                    prev = prev->next;  // 注意，prev 也要往下移动
                    
                }
                ls2 = tmp2;     
            }
         }
         
        if(ls2) // 如果ls2还有剩余的，这时候ls1应该到了null, 就把ls2 连在ls1最后
        {
            prev->next = ls2;
        }
         return  head;
    }
        

// llist mergeTwoLists(llist l1, llist l2)
// {
//     // L1 || L2 Null
//     if(NULL == l2)
//         return l1;
//     if(NULL == l1)
//         return l2

//     //L1 && L2 not Null

//     llist ans = NULL;
//     llist tmp = NULL;
//     llist op = NULL; 

//     //  process until  L1 || L2 Null   
//     while(NULL != l1 && NULL != l2)
//     {
//         if( l1->val >= l2->val /*|| NULL == l1*/ )
//         {
//             //insert smaller
//             op = ans;
//             ans = l2;            
//             l2 = l2->next;            
//             ans->next = op;
//         }
//         else if( l2->val >= l1->val /*|| NULL == l2 */)
//         {
//             //insert smaller
//             op = ans;
//             ans = l1;
//             l1 = l1->next;
//             ans->next = op;
//         }
//         else
//         {
//             cout << "excp" << endl;
//         }
//     }

//     ans = reverseList(ans);

//     if(NULL == l1)
//     {
//         //op = ans;
        
//         // //l2 = l2->next;            
//         //ans->next = op;

//         if(ans != NULL)
//             ans->next = l2;
//         else
//             ans = l2;

//         // cout << '.' << '\n';
//         // print(ans);
//         // print(ans->next);
//         // print(l2);
//         // cout << '.' << '\n';
//     }
//     else
//     {
//         //op = ans;
//         //ans = l1;
//         //l1 = l1->next;
//         //ans->next = op;
//         // if(ans == NULL) 
//         //     ans = l1;
//         // else
//         //     ans->next = l1;
//         print(l1);
//     }

    
//     return ans;


// }

int main()
{
    int list_1[] = {};
    int list_2[] = {1,3,4};

        //new list
    llist l1,l2;
    l1 = l2 = NULL;//= newNode(-1); "没有"头节点
    llist op = NULL;

    assignment(list_1,getLen(list_1),l1);
    assignment(list_2,getLen(list_2),l2);
    print(l1);
    print(l2);
    
    llist out = mergeTwoLists(l1,l2);

    print(out);
    deleteNode(out);

    //print(reverseList(head));
    //print(middleNode(head));
    //deleteNode(l1);
    //deleteNode(l2);
    
    return 0;
}