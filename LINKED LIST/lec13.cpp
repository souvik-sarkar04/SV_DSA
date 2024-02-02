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

//T.C. O(n+n/2),[needs OPTIMISATION] n is for length of LL and n/2 is for finding mid, S.C. O(1)
Node *middle_brute(Node *head)
{
    if (head == NULL || head->next == NULL)
    {
        return head;
    }
    int l = lengthofLL(head); //FIRST STEP is to find length of LL
    //MID ELEMENT IS [(length/2) + 1]th node of LL
    int cnt = (l / 2) + 1;
    
    Node *temp = head;

    // int count = 1;
    // while (temp && count < cnt) //'<' because the temp crosses the mid element when '<=' is used
    // {
    //     temp = temp->next;
    //     count++;
    // }
    // while(temp && (cnt-1))
    while(temp)
    {
        cnt = cnt-1; //ALTERNATIVE is the while condition commented out above which has same meaning
        //Here, updation is done before checking to avoid temp to go BEYOND MID
        if(cnt==0)
        {
            break;
        }
        temp = temp->next;
    }
    return temp;
}

//OPTIMAL CODE
//TORTOISE AND HARE ALGORITHM
//We take two pointers, slow and fast and point both of them to head. Now, we move the SLOW pointer by 1 FORWARD STEP and 
//the FAST pointer by 2 FORWARD steps. In case of ODD length, when Fast reaches LAST NODE and in case of EVEN length, when 
//Fast reaches NULL(never reaches the last node), the SLOW reaches the DESIRED MIDDLE ELEMENT. 
//ESSENCE: The FAST pointer is EFFECTIVELY TRAVERSING THE ENTIRE LINKED LIST and by asking the SLOW pointer to traverse HALF THE NUMBER OF TRAVERSALS OF FAST,
// we demand it to reach the EFFECTIVE MIDDLE NODE  of LL. 
//Or in other words, if Person 1 has speed x and Person 2 has speed x/2, then, in same time, A covers distance d while B covers distance x/2.

// T.C. O(n/2) S.C. O(1)
Node* middle_optimal(Node* head)
{
    // if(head==NULL || head->next == NULL)
    // {
    //     return head;
    // }
    Node* slow = head;
    Node* fast = head;
    while(fast!=NULL && fast->next!=NULL)
    //fast!=NULL is for even length and fast->next!=NULL is for odd length. Before fast starts pointing to last node in case of ODD LENGTH, 
    //slow reaches the MID ELEMENT as it is updated before and the current traversal is completed, after that the loop condition evaluates to false.
    //&& is applied to cover both odd and even length cases in a SINGLE TRAVERSAL
    {
        slow = slow->next;
       
        fast = fast->next->next;
         
    }
    return slow;
}
int main()
{
    vector<int> arr = {1, 2, 3, 4, 5,6,7};
    Node *head = convertArr2LL(arr);
    print(head);
    // Node *mid = middle_brute(head);
    // cout << mid->data;
    Node *mid = middle_optimal(head);
    cout << mid->data;
    return 0;
}