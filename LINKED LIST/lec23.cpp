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

// BRUTE FORCE:
//  We take all elements of list1 and list2 and put them in a container. We take temp1 for list1 and temp2 for list2 and point them at the respective heads.
// An array is taken and all elements of list1 is taken until it is null and then all elements of list2 are taken until it is null and then we STOP.
// We SORT the array and we CALL THE CONVERT function which converts this array to LL. Then, we return head of this new LL.

// T.C. O(n1+n2+NlogN + N) (N=total number of elements of list1 and list2)
// n1,n2 for traversals of lists and putting their elements in array, NlogN for sorting array, N for converting array to list (NEEDS OPTIMISATION)
// S.C. O(N) + O(N) (for extra space of array + extra space to compute the new list)
Node *mergeLL_brute(Node *head1, Node *head2)
{
    Node *temp1 = head1;
    Node *temp2 = head2;
    vector<int> arr;
    while (temp1 != NULL)
    {
        arr.push_back(temp1->data);
        temp1 = temp1->next;
    }
    while (temp2 != NULL)
    {
        arr.push_back(temp2->data);
        temp2 = temp2->next;
    }
    sort(arr.begin(), arr.end());
    Node *list3 = convertArr2LL(arr);
    return list3;
}

// PROPERTY OF SORTED LL'S is considered --> TWO POINTER APPROACH
// First element of either of the lists will be the FIRST ELEMENT of the NEW LIST as the LISTS ARE SORTED.
// We place t1 at head and t2 at head2. We CHANGE LINKS rather than CREATING NEW LIST and in such situations, DUMMYNODE CONCEPT IS USEFUL.
// dummyNode points to EXISTING NODES so CREATION OF NEW NODES IS NOT REQUIRED.
// t1 and t2's data is compared, whichever is considered is pointed to curr and then is incremented.

//T.C. O(n1+n2)(WORST CASE) S.C. O(1)(nodes are RESUED, not NEWLY CREATED).
Node *mergeLL_optimal(Node *head1, Node *head2)
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
    // Leftover elements of either list1 and list2 get connected to curr.
    //NO NEED TO UE LOOPS HERE as temp1 or temp2 points to the FIRST NODE AMONG THE LEFTOVER NODES and when that is pointed at, the entire leftover list is added
    // while (temp1 != NULL)
    // {
        if(temp1!=NULL)
        {
             curr->next = temp1;
        }
    
    // while (temp2 != NULL)
    // {
        if(temp2!=NULL)
        {
            curr->next = temp2;
        }
    return dummyNode->next;
}
int main()
{
    vector<int> arr1 = {2, 4, 8, 10};
    vector<int> arr2 = {1, 3, 3, 6, 11, 14};
    Node *head1 = convertArr2LL(arr1);
    print(head1);
    Node *head2 = convertArr2LL(arr2);
    print(head2);
    Node *head3 = mergeLL_optimal(head1, head2);
    print(head3);
    return 0;
}