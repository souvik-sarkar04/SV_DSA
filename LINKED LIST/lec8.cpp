#include<iostream>
#include <bits/stdc++.h>
using namespace std;
class Node
{
public:
    int data;
    Node *next;
    Node()
    {
        this->data = 0;
        this->next = NULL;
    }
    Node(int data)
    {
        this->data = data;
        this->next = NULL;
    }
    Node(int data, Node *next)
    {
        this->data = data;
        this->next = next;
    }
};

Node *convertArr2LL(vector<int> &arr)
{
    Node *head = new Node(arr[0]);
    Node *mover = head; // initally points to 'head', stands at first place now
    for (int i = 1; i < arr.size(); i++)
    {
        Node *temp = new Node(arr[i]);
        mover->next = temp;
        mover = temp; // we can also write mover = mover->next;
    }
    return head;
}

void print(Node *head)
{
    while (head != NULL)
    {
        cout << head->data << " ";
        head = head->next;
    }
    cout << endl;
}
int length = 0;
int lengthofLL(Node *head) // head is always provided as parameter
{
    // Copy paste the traversal and increment count to get length

    Node *temp = head; // head stored in a new pointer 'temp' so that head is NOT TAMPERED
    while (temp)       // while temp!=null or while temp is valid
    {
        length++;
        temp = temp->next; // temp->next means sending temp to point to next node
    }
    return length;
}
Node* deleteHead(Node *head)
{
    if (head == NULL) //(EDGE CASE to write in EVERY LINKED LIST CODE)checking if LINKED LIST IS EMPTY
    {
        return head;
    }
    Node *temp = head;
    head = head->next;
    free(temp); // or write delete temp;
                // to free the temp memory(original head)
    return head;
}

Node* deleteTail(Node *head)
{
    if (head == NULL || head->next == NULL)
    // head==null means Empty Linked List and head->next ==null means 1 element in Linked List(which acts as tail which if removed leaves nothing hence null is returned in both cases)
    {
        return NULL;
    }
    Node *temp = head;               // we create temp and store head in it so that we do not have to ALTER HEAD and we can return it properly
    while (temp->next->next != NULL) // observe the technique to point to 2 positions ahead of temp
    {
        temp = temp->next; // when position ahead of second last node is not NULL, make the pointer pointing to the second last position move forward
    }
    free(temp->next); // delete temp->next;
    // free the memory of tail
    temp->next = nullptr; // writing NULL here instead of nullptr also works
    // make the tail memory NULL
    return head; // return head in every program of LL
}

//WORKING
Node* removeKthNode_my(Node* head, int k)
{
    int l = lengthofLL(head); 
    //take the returned value of length function to use it, directly using global variable will give value of length as 0
    if (head == NULL || head->next == NULL)
    // head==null means Empty Linked List and head->next ==null means 1 element in Linked List(which acts as tail which if removed leaves nothing hence null is returned in both cases)
    {
        return NULL;
    }
    if(k==1)
    {
        return deleteTail(head);
    }
    if(k==l)
    {
        return deleteHead(head);
    }
    Node* temp = head;
    Node* prev = NULL;
    int cnt = 1;
    while(temp)
    {
        if(cnt==l-k+1)
        {
            break;
        }
        prev = temp;
        temp = temp->next;
        cnt++;
    }
    cout<<"Length: "<<l<<endl;
    Node* n = temp->next;
    temp->next = nullptr;
    prev->next = n;
    free(temp);
    return head;    
}
// T.C. : O(length) + O(length-k) 
// 1st term for calculating length and second term for reaching (length-k)th node 
//WORST CASE T.C.: O(2n) when k=1 so OPTIMISATION OF CODE IS NEEDED
//S.C. O(1)
Node* removeKthNode_brutemain(Node* head, int k)
{
    int l = lengthofLL(head); 
    //take the returned value of length function to use it, directly using global variable will give value of length as 0
    if (head == NULL || head->next == NULL)
    // head==null means Empty Linked List and head->next ==null means 1 element in Linked List(which acts as tail which if removed leaves nothing hence null is returned in both cases)
    {
        return NULL;
    }
    // if(k==1) unnecessary as res==0 condition can delete TAIL
    // {
    //     return deleteTail(head);
    // }
    if(k==l)
    {
        return deleteHead(head);
    }
    Node* temp = head;
    //ESSENCE: we need to reach (length-k)th node, the reason is the node NEXT TO IT has to be deleted.
    // So, by using temp->next, we can delete that node and by assigning the (length-k) node to its next->next, we can change the links too, so, 
    //both the purposes of DLEETING THE NODE and CHANGING THE LINK OF PREVIOUS NODE is achieved(thus, discarding the idea of having 'prev' pointer).
    int res = l-k;
    while(temp)
    {
       res--;
        if(!res)
        {
            break;
        }
         
        temp = temp->next;
    }
    Node* delNode = temp->next;
    temp->next = temp->next->next;
    free(delNode);
    return head;
}

//OPTIMISED CODE: Delete Kth node by NOT knowing LENGTH OF LINKED LIST
//The algorithm is to take two pointers fast and slow
//fast pointer is first pointed to head and is incremented k times
//After incrementing fast for the kth time, the sloww pointer is pointed to head.
//Thereafter, fast and slow both pointers are incremented and when the fast pointer reaches the LAST NODE, we observe that the SLOW pointer has reached (LENGTH-K)th node, which was the main objective.

// T.C. O(length) (fast first moves till k and then trvels length-k so overall O(length))
// S.C. O(1)
//REWRITE THE CODE
Node* removeKthNode_optimal(Node* head, int k)
{
    int l = lengthofLL(head);
    if (head == NULL || head->next == NULL)
    // head==null means Empty Linked List and head->next ==null means 1 element in Linked List(which acts as tail which if removed leaves nothing hence null is returned in both cases)
    {
        return NULL;
    }
    if(k==l) //fast reaches null in loop written below, so, deleting head has to be taken seperately
    { 
        //to write this after FOR LOOP, we need to use fast==NULL
        Node* newHead = head->next;
        return newHead;
    }
    Node* fast = head;
    Node* fast = head;
    Node* slow = head;
    Node* temp = head;
    int cnt = k;
    // for(int i=0; i<k; i++) ALTERNATIVELY IF CONDITION IS WRIITEN IN WHILE LOOP TO MOVE FAST POINTER IN THE BEGINNING
    // {
    //     fast = fast->next;
    // }
    while(temp && fast->next!=NULL)
    {
        if(k)
        {
            fast = fast->next;
            k--;
        }
        else{
            fast = fast->next;
            slow = slow->next;
        }
        temp = temp->next;
    }
    Node* delNode = slow->next;
    //freeing delNode before connecting the previous and the next nodes will result in loss of next node and linking with previous node will not be possible
    slow->next = slow->next->next;
    free(delNode);
    return head;
}
int main(){
vector<int> arr = {1,2,3,4,5,6,7};
Node* head = convertArr2LL(arr);
print(head);
// head = removeKthNode_my(head,3);
// print(head);
// head = removeKthNode_brutemain(head,3);
// print(head);
head = removeKthNode_optimal(head,3);
print(head);
return 0;
}