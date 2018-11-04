#include<iostream>
#include<vector>

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
        ;
    std::cout << "[ ";
    while(head != NULL)
    {
        cout <<  head->val << ' ';
        head = head->next;
    }
    cout << "]" << endl;
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

void deleteNode(ListNode* node) {
    //*node = *node->next;
    ListNode* temp = node->next;
    node->val = node->next->val;
    node->next = temp->next;
    delete temp;
}

// int main()
// {
//     int list_init[] = {0,1,2,3,4,5,6,7,8,9};

//         //new list
//     llist head = NULL;//= newNode(-1); "没有"头节点
//     llist op = NULL;

//     int len = sizeof(list_init)/sizeof(int);  
//     for(int i = 0; i < len; i++ )
//     {
//         //头插 ...都没有头节点 hh        
//         op = head;
//         head = new ListNode(i);
//         head->next = op;                                
//     }
//     print(head);
//     //print(reverseList(head));
//     //print(middleNode(head));
//     deleteNode(head);
//     cout << '\n';
//     print(head);


//     return 0;
// }