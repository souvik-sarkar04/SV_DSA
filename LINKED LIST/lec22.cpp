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

Node *rotateLL(Node *head, int k)
{
    int l = lengthofLL(head);
    if (head == NULL || head->next == NULL || k == 0 || k == l)
    // here, k=0 or k=l returns the same LL(EDGE CASES)
    {
        return NULL;
    }
    Node *temp = head;

    int res = l - (k % l); //(k can be GREATER than l, in that case, multiple of length rotations are to be ignored and only extra traversals
    // are to be considered, hence (k%l) is subtracted)
    Node *begin = NULL;
    while (temp->next != NULL)
    {
        // cout<<"res: "<<res<<endl;
        res--;
        if (res == 0)
        {
            begin = temp->next;
            temp->next = NULL;
            break;
        }
        temp = temp->next;
    }
    Node *temp1 = begin;
    while (temp1->next != NULL)
    {
        temp1 = temp1->next;
    }
    temp1->next = head;
    return begin;

    // For 1 rotation:
    //  while (temp->next != NULL)
    //  {
    //      prev = temp;
    //      temp = temp->next;
    //  }
    //  last = new Node(temp->data);
    //  prev->next = NULL;
    //  last->next = head;
    //  return last;
}

// After rotation, we observe that the TAIL is pointing to the HEAD instead of NULL.
// We also observe after rotation, the LAST NODE of the ROTATED LL also points to NULL which PREVIOUSLY POINTED TO SOME NODE OF LL.
// So, these links need to be changed. Also, from observation, we realise that the LAST NODE of ROTATED LL is (length-k)th node which can be obtained by traversal.
// Another observation is the UPDATED HEAD of the ROTATED LL is the IMMEDIATE NEXT NODE of the LAST NODE OF ROTATED LL in the ORIGINAL LL.
// If k=length, we come back to ORIGINAL LL. Using the same fact, if k is ANY MULTIPLE OF LENGTH, it gives back the ORIGINAL LL.
// This can be represented as if(k%len==0) then return head(This handles k=ALL MULTIPLES OF LENGTH and not only k=length, ABSENT in MY code.)
// We deduce from above if k is NOT MULTIPLE OF LENGTH, we need to EFFECTIVELY do (k%length) rotations.

Node *findNthNode(Node *head, int res)
{
    Node *temp = head;
    while (temp != NULL)
    {
        res--;
        if (res == 0)
        {
            return temp;
        }
        temp = temp->next;
    }
    return temp;
}

//T.C. O(n+n) = O(2n) traversal for tail and traversal for nth node //S.C. O(1)
Node *rotateLL_main(Node *head, int k)
{
    if(head==NULL || k==0) //k==0 means NO ROTATIONS
    {
        return head;
    }
    int len = 1;
    Node *tail = head;
    //The following loop finds TAIL and LENGTH in same traversal(I took 2 traversals)
    while (tail->next != NULL)
    {
        len++;
        tail = tail->next;
    }
    if (k % len == 0)
    {
        return head;
    }
    tail->next = head;
    k = k%len; //to consider only EFFECTIVE ROTATIONS
    Node *newLastNode = findNthNode(head, len - k);
    head = newLastNode->next;
    newLastNode->next = NULL;
    return head;
}
int main()
{
    vector<int> arr = {1, 2, 3, 4, 5};
    Node *head = convertArr2LL(arr);
    print(head);
    head = rotateLL(head, 4);
    print(head);
    return 0;
}