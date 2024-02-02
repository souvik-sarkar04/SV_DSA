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

// T.C. O(N+NLOGN+N)(N,N for LL traversals, NlogN for sorting array), S.C. O(n)(NEEDS OPTIMISATION)
Node *sorting_brute(Node *head)
{
    // int i=0, j, l=lengthofLL(head);
    Node *temp = head;
    vector<int> arr;
    while (temp)
    {
        arr.push_back(temp->data);
        temp = temp->next;
    }
    sort(arr.begin(), arr.end());
    // Node* head1 = convertArr2LL(arr);
    // return head1;
    // AN ALTERNATIVE OF USING convert() function(to avoid CREATING NEW LIST):
    int i = 0;
    temp = head;
    for (int i = 0; i < arr.size() && temp != NULL; i++)
    {
        temp->data = arr[i];
        temp = temp->next;
    }
    return head;
}

// FOR OPTIMISATION OF SPACE, merge sort is applied which is EASIER TO IMPLEMENT.
// Ex.> 3->4->2->1->5. We divide it into 2 LL's 3->4->2 and 1->5 and last elements of these 2 LLs point to NULL.
//  Then they are broken down into single element LLs. In each recursion step of MEERGING BACK, we have 2 sorted lists which can be MERGED using the mERGE 2 SORTED LLs algorithm.
//
Node *middle(Node *head)
{
    Node *slow = head;
    Node *fast = head->next;
    // We need FIRST MIDDLE and NOT second middle for merge sort as we need to point the first middle's next to null and break the LL there and start the next component LL from mid->next.
    // Node *fast = head;
    while (fast != NULL && fast->next != NULL)
    {
        slow = slow->next;

        fast = fast->next->next;
    }
    return slow;
}

Node *merge2LL(Node *head1, Node *head2)
{
    if (head1 == NULL && head2 == NULL)
    {
        return NULL;
    }

    Node *dummyNode = new Node(-1);
    Node *curr = dummyNode;
    Node *temp1 = head1;
    Node *temp2 = head2;
    while (temp1 != NULL && temp2 != NULL) // traversal done till BOTH of them are ACTIVE
    {
        if (temp1->data <= temp2->data)
        {
            curr->next = temp1;
            curr = temp1;
            temp1 = temp1->next;
        }
        else
        {
            curr->next = temp2;
            curr = temp2;
            temp2 = temp2->next;
        }
    }
    if (temp1 != NULL)
    {
        curr->next = temp1;
    }
    if (temp2 != NULL)
    {
        curr->next = temp2;
    }
    return dummyNode->next;
}
// T.C. O(Logn(to the base 2) * (n+n/2) logn is for depth of recursion, n is for merging andd n/2 is for finding middle node)
// S.C. o(1) (O(logn) for recursive stack space)
Node *mergeSort(Node *head)
{
    // if (low >= high)
    if (head == NULL || head->next == NULL) // EDGE CASE, also returns the SINGLE NODE LL(considered sorted) when it reaches base case at last
    {

        // return;
        return head;
    }
    // int mid = (low + high) / 2;
    Node *mid = middle(head);
    Node *leftHead = head;
    Node *rightHead = mid->next;
    mid->next = NULL; //VERY IMPORTANT STEP(Finding middle node alone is NOT CAPABLE of breaking down the LL into 2 parts,
    //assigning middle node's next as NULL and thereafter passing head to the recursive function would mean that ONLY THE LEFT HALF
    // of the LL is passed and DIVIDING ALGORITHM IS DONE. Also, assigning rightHead as middle node's next and theen passing it to the recursive 
    // function allows it to DIVIDE the RIGHT HALF OF THE LL SEPERATELY. These2 function calls finally give SINGLE NODE LLs which are
    // considered sorted and then they are MERGED and then progressively MERGING ALGORITHM is done.)
    leftHead = mergeSort(leftHead);
    rightHead = mergeSort(rightHead);
    Node *m3 = merge2LL(leftHead, rightHead);
    return m3;
}
int main()
{
    vector<int> arr = {3, 4, 5, 1, 2};
    Node *head = convertArr2LL(arr);
    print(head);
    // head = sorting_brute(head);
    // print(head);
    Node *temp = head;
    while (temp->next)
    {
        temp = temp->next;
    }
    head = mergeSort(head);
    print(head);
    return 0;
}