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

// Reaching the middle node here DOES NOT MAKE SENSE as we may be able to delete the middle node but WE WILL NOT BE ABLE TO LINK THE PREVIOUS NODE TO THE NEXT NODE.
//  So, our task is to reach the NODE PREVIOUS to MIDDLE node.

// T.C. O(n+n/2), needs optimisation(as it is 2 PASS solution), S.C. O(1)
Node *delMiddle_brute(Node *head)
{
    if (head == NULL || head->next == NULL)
    {
        return NULL;
    }
    int l = lengthofLL(head);
    int cnt = (l / 2); // For both odd and even length, the PREVIOUS node to MIDDLE node is the (length/2)th position
    Node *temp = head;
    while (temp)
    {
        cnt--;
        temp = temp->next;
        if (cnt == 0)
        {
            Node *middle = temp->next;
            temp->next = temp->next->next;
            // temp->next->next = NULL; NEVER DO THE MISTAKE OF CHANGING LINKS BEFORE KEEPING TRACK of the NODE to be DELETED
            free(middle);
        }
        temp = temp->next;
    }

    return head;
}

Node *delMiddle_optimal_my(Node *head)
{
    if (head == NULL || head->next == NULL)
    {
        return NULL;
    }
    Node *slow = head;
    Node *fast = head;
    Node *prev = NULL;
    while (fast != NULL && fast->next != NULL)
    {
        prev = slow;
        slow = slow->next;
        fast = fast->next->next;
    }
    prev->next = slow->next;
    slow->next = NULL;
    free(slow);
    return head;
}

//Here, as the AIM is to reach the node PREVIOUS TO MIDDLE, so, we SKIP 1 STEP of slow during the traversal so that it reaches the node PREVIOUS to where it was supposed to reach(middle) 
// T.C. O(n/2)(1 pASS- OPTIMISED) S.C. O(1)
Node *delMiddle(Node *head)
{
    if (head == NULL || head->next == NULL)
    {
        return NULL;
    }
    Node *slow = head;
    Node *fast = head;
     fast = fast->next->next; //ALTERNATIVE OF TAKING VARIABLE: Fast is already moved 2 steps ahead INITALLY to SKIP 1 STEP of slow
    // Node *prev = NULL;
    // int cnt=1;
    while (fast != NULL && fast->next != NULL)
    {
        // prev = slow;
        // if(cnt<1)
        // {
             slow = slow->next;
        // }
        fast = fast->next->next; 
       
        // cnt--;
    }
    Node *middle = slow->next;
    slow->next = slow->next->next;
    free(middle);
    return head;
}
int main()
{
    vector<int> arr = {1, 2, 3, 4, 5, 6};
    Node *head = convertArr2LL(arr);
    print(head);
    head = delMiddle(head);
    // print(head);
    // head = delMiddle_brute(head);
    print(head);
    return 0;
}