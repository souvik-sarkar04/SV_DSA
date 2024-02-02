#include <iostream>
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

Node *reverse_main1(Node *head)
{
    if (head == NULL || head->next == NULL)
    {
        return head;
    }
    Node *temp = head;
    Node *prev = NULL;
    Node *front = NULL;
    while(temp!=NULL)
    {
    
        front = temp->next;
        temp->next = prev;
        prev = temp;
        temp = front;
    }
    return prev;
}

bool compare(Node *head1, Node *head2)
{
    Node *temp1 = head1;
    Node *temp2 = head2;
    while (temp1 && temp2)
    {
        if (temp1->data != temp2->data)
        {
            return 0;
        }
        return 1;
    }
} 
//Values are put into the stack by placing it at the head and then traverse.
//Then, COMPARISON by taking temp at head and compare it with top element of stack and remove it if the 2 elements are matching.
//We STOP if temp is NULL or the STACK is EMPTY and we return that it is palindrome.
//Using stack is beneficial in this comparison because the last element of LL was at the top of stack which could be compared to FIRST ELEMENT of LL to check palindrome.
//REVERSING a LL using STACK is turning out to be a HANDY TOOL.

//T.C. O(2n) for 2 traversals, S.C. O(n) for extra stack, S.C. needs OPTIMISATION
bool palindrome_brute(Node* head)
{
    stack<int> s;
    if(head==NULL)
    {
        return NULL;
    }
    Node* temp = head;
    while(temp)
    {
        s.push(temp->data);
        temp = temp->next;
    }
    temp = head;
    while(temp)
    {
        if(temp->data == s.top())
        {
            s.pop();
        }
        else{
            return 0;
        }
        temp = temp->next;
    }
    return 1;
}

//USING TORTOISE AND HARE ALGORITHM, PALINDROME CODE will be OPTIMISED
//WORKING
bool palindrome_optimal_my(Node* head)
{
    Node* slow = head;
    Node* fast= head;
    while(fast!=NULL && fast->next!=NULL)
    {
        slow = slow->next;
        fast = fast->next->next;
    }
    Node* mid = slow;
    Node* rev = reverse_main1(mid);
    Node *temp1 = head;
    Node *temp2 = rev;
   
    while (temp1 && temp2)
    {
        if (temp1->data != temp2->data)
        {
            return 0;
        }
        temp1 = temp1->next;
        temp2 = temp2->next;
    }
    reverse_main1(temp2);
    return 1;
}

//RECOGNISING the SECOND HALF of LL by finding MIDDLE OF LL(TORTOISE AND HARE ALGORITHM).
//In this case, instead of reaching middle 2(in case of finding middle element), we aim to reach MIDDLE 1 and so,
// for EVEN LENGTH, the FAST POINTER's next->next should not be NULL.
//Now, slow->next is the CURRENT HEAD of the SECOND HALF and then, the SECOND HALF is REVERSED by CHANGING LINKS.
// Now, middle1 is STILL POINTING to the CURRENT TAIL(ORIGINAL HEAD) of the second half. 
//2nd STEP is to REVERSE THE SECOND HALF as mentioned above.
//The 3rd step is to COMPARE THE FIRST AND SECOND HALVES' ELEMENTS and finally when the comparison is done, again REVERSE the SECOND HALF to RETAIN the original LL.

//T.C. O(n/2+n/2+n/2+n/2) = O(2n) (recognition of mid + reverse 2nd half + comparison +re-reverse 2nd half)
//S.C. O(1)
bool palindrome_optimal(Node* head)
{
    if(head==NULL || head->next == NULL)
    {
        return head;
    }
    Node* slow = head;
    Node* fast= head;
    while(fast->next!=NULL && fast->next->next!=NULL)  
    //only even length condition changes from fast!=null to fast->next->next!=null, odd condition remains same as fast->next!=null
    {
        slow = slow->next;
        fast = fast->next->next;
    }
    Node* newHead = slow->next;
    
    Node* rev = reverse_main1(newHead);
    Node *temp1 = head;
    Node *temp2 = rev;
    while (temp2) 
    //only checking for SECOND HALF'S NULL is SUFFICIENT as for EVEN LENGTH, both halves have same number of elements while in ODD LENGTH, the second half has LESSER NUMBER OF ELEMENTS and will get EXHAUSTED earlier
    {
        if (temp1->data != temp2->data)
        {
            reverse_main1(temp2);
            return 0;
        }
       temp1 = temp1->next;
       temp2 = temp2->next; //DO NOT FORGET UPDATION OF TEMP FOR GOD'S SAKE
    }
    reverse_main1(temp2); //PEOPLE DONT WANT TO MANIPULATE GIVEN DATA, so, converting the MANIPULATED LL to ORIGINAL LL is IMPORTANT FOR INTERVIEWS
    return 1;
   
}
int main()
{
    vector<int> arr1 = {1, 2, 3, 2, 1};
    Node *head1 = convertArr2LL(arr1);
    print(head1);
    // Node *head2 = reverse_main1(head1);
    // print(head2);
    // if (compare(head1, head2))
    // {
    //     cout << "Palindrome" << endl;
    // }
    // else
    // {
    //     cout << "Not palindrome" << endl;
    // }
    // cout<<"Result:"<<palindrome_brute(head1);
    // cout<<"Result:"<<palindrome_optimal_my(head1);
    cout<<"Result:"<<palindrome_optimal(head1);
    return 0;
}