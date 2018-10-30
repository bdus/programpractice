---
title:LinkedList
---
# singly-linked list

## in C

C语言中 不同的数据类型或结构体有不同的链表实现

void指针或者[C实现多态](https://blog.csdn.net/gatieme/article/details/50929737)不在考虑范围

下面是一个int链表的节点
```c
//Definition for singly-linked list.
struct ListNode {
    int val;
    struct ListNode *next;
};
```

## in C++

C++兼容c,可以利用多态实现,也可以不

下面是一个int链表的节点 用cpp实现

```cpp
//Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
```
可以看到和c很类似
但不同的是,cpp的结构体可以有方法

>ListNode(int x) : val(x), next(NULL) {}

上面这句就是结构体的构造函数,在初始化的时候调用,可以给结构体的参数赋初值,像这样:

```cpp
void createList(ListNode* &pHead){
    pHead = new ListNode(-1);
	int length = 5;
	ListNode *p = pHead;
	for (size_t i = 0; i < length; i++)
	{
	    ListNode *node = new ListNode(i);

		p->next = node;
		p = node;
	}		
}
```

## in python

其实python本身就有list类 再定义个ListNode也是有点意思 有兴趣搜索下[python linked list] 看看博客

```python
#Definition for singly-linked list.
class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None
```


# Instances
下面来实现一下

- [ ] 一些基本的线性链表操作
- [x] 链表反转 206                 

# 206. Reverse Linked List

链表反转@[leetcode](https://leetcode.com/problems/reverse-linked-list/description/)

我写的 in C
```c
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
```
官方的 (有判断是不是带头的链表)

```c
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* reverseList(struct ListNode* head) {
    struct ListNode *curNode = head;
    struct ListNode *prevNode = NULL;
    struct ListNode *tmpNode = NULL;
    
    if(head == NULL || head->next == NULL)
        return head;
    
    while(curNode)
    {
            tmpNode = curNode;
            curNode = curNode->next;
            tmpNode->next = prevNode;
            prevNode = tmpNode;
    }
    
    head = prevNode;
    
    return (head);
    
}
```

官方C++版本

```cpp

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        stack<ListNode*> sc;
        while (head!=NULL) {
            sc.push(head);
            head = head->next;
        }
        
        ListNode* sol = new ListNode(-1);
        head = sol;
        while(!sc.empty()) {
            sol->next = sc.top();
            sol->next->next = NULL;
            sc.pop();
            sol = sol->next;
        }
        return head->next;
    }
};
```

## 876. Middle of the Linked List

Problem [[link]](https://leetcode.com/problems/middle-of-the-linked-list/de

```cpp
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
```