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

int lengthCycle(Node *head)
{
    vector<int> arr(10001);
    Node *temp = head;
    int p = 1;
    while (temp)
    {
        arr[temp->data]++;
        if (arr[temp->data] >= 3)
        {
            break;
        }
        temp = temp->next;
    }
    for (int i = 0; i < arr.size(); i++)
    {
        if (arr[i] == 2)
        {
            p++;
        }
    }
    return p;
}

// Return length as 0 if LINEAR LL is given
// HASHING
// we take temp = head and take timer=1 and as we move ahead using temp and traverse the LL and increment the timer variable
// suppose length of loop is 7 so say, its value was 3 when it entered the first node in the loop and when it came back again to that node, timer's value became 10.
// So, the difference is (10-3) = 7.
// We will store the NODE and TIMER in the map
// We check each time if the NODE IS INSERTED AGAIN in the map and then we take DIFFERENCE of the CORRESPONDING TIMER VLAUES.

// T.C. O(n*2*logn), n->for traversal of entire LL, 2 operations of map(logn)- finding and inserting
// S.C. O(n)
int lengthOfLoop_brute(Node *head)
{
    map<Node *, int> mpp;
    Node *temp = head;
    int timer = 1, value;
    while (temp != NULL) // in case it is a linear LL
    {
        if (mpp.find(temp) != mpp.end()) // check if the CURRENT NODE was INSERTED BEFORE in the map
        {
            value = mpp[temp];
            return timer - value; // if the revisited node is found, then the corresponding values of timer are subtracted
        }
        mpp[temp] = 1; // In case the revisited node is not found at the current traversal, we INSERT temp node in the map along with its corresponding timer
        timer++;
        temp = temp->next;
    }
    return 0; // if it is a linear LL, nothing is returned inside the while loop, so it comes out so we need to print length of loop as 0
}

// TORTOISE AND HARE ALGORITHM: to find LENGTH OF LOOP

int findLength(Node *slow, Node *fast)
{
    int cnt = 1;
    fast = fast->next;
    while (slow != fast)
    {
        cnt++;
        fast = fast->next;
    }
    return cnt;
}
int lengthOfLoop_optimal(Node *head)
{
    Node *slow = head;
    Node *fast = head;
    int count = 1;
    while (fast != NULL && fast->next != NULL)
    // fast->next!=NULL(reaching LAST NODE is STOPPING condition of ODD length
    // fast!=NULL(reaching NULL is STOPPING condition of EVEN length ))
    {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast)
        {
            return findLength(slow, fast);
            // once fast reaches slow and they coincide on a particular node, we start fast's traversal by 1 STEP and move it until it gets back to slow again and in this way, we find the length.
            // It is computed in a seperate function to remove confusion or unwanted output or clashes between fast's 2 STEP movement or 1 STEP movement
        }
    }
    return 0; // In case of LINEAR LL
}

int main()
{
    vector<int> arr = {1, 2, 3};

    Node *head = convertArr2LL(arr);
    print(head);
    head->next->next = head;
    cout << lengthCycle(head) << endl;
    cout << lengthOfLoop_optimal(head) << endl;
    return 0;
}