#include <iostream>
#include <bits/stdc++.h>
using namespace std;
// What is Linked List?
// Array has a fixed size. On the contrary,
//  Linked List helps to increase or decrease the size at any moment.
// Linked list is similar to array(any data type value can be stored) but they DO NOT STORE data in CONTIGUOUS LOCATIONS in heap memory.
// In array, it was unknown if the next location after the last location is free or not, but in Linked List, there is no concept of next location
// as adding a new element just puts it SOMEWHERE IN HEAP MEMORY.
// In linked list, for storing and traversal, we store an element(data) and at the SAME TIME, we store 'next' with EVERY DATA.
// We assign HEAD of LINKED LIST(starting element) as m1 and to signify m2 is the next element, we assign m2 to 'next' of m1. 
//This creates an invisible link between m1 and m2.
// To signify there will be nothing beyond m4(here, the last element - TAIL OF LINKED LIST), we assign its 'next' as null pointer(in C++).
// To add a new element, create its memory in heap memory and assign 'next' of tail to m5(the new location) to link it with the Linked List and assign 'next' of m5 to null pointer.

// Where is it used?
// Used in stacks, queues where there are no fixed sizes.
// The Linked List discussed above is a 1D Linked List where the 'next' is remembered but the 'previous' is not remembered.
//  In real life, it is used in a browser. Ex.> Search-->takeuforward-->A2Z-->article, back button takes back in the same tab. Looks like a Linked List where one can come back as many steps he feels like, not fixed.

// int x = 2;(creates x in the heap memory) int* y=&x;(gives memory location m1 where x is stored) cout<<y;
// In array, only elements of data type specified are stored. In Linked List, the element is stored along with the POINTER TO THE NEXT ELEMENT.
// A SELF-DEFINED DATA TYPE(here, class Node) is needed for storing both the DATA and the POINTER TO THE NEXT.
//   The Node* type indicates that the pointer is pointing to an object of type Node, allowing you to traverse the linked list by following these pointers from one node to the next.
// Adding element to node: Node x = Node(2,nullptr);  this is just the MEMORY LOCATION, no pointer points to it now.
// Here, variable is made of Node type and Node constructor is called to assign 2 to data and nullptr to next1.
// To get a pointer pointing to x, we have Node* y = &x;
// The above 2 lines can be written in a single line so that memory location is created and a pointer is also obtained which points to that memory location:
//  Node *y = new Node(2,nullptr);

class Node
{
public:
    int data;
    Node *next;

    Node(int data1, Node *next1)
    {
        data = data1;
        next = next1;
    }
    Node(int data1)
    {
        data = data1;
        next = nullptr;
    }
};

// For 32-bit system, int:4 bytes pointer: 4 bytes total:8 bytes
// For 64-bit system, int:4 bytes pointer: 8 bytes total:12 bytes

// Creation of HEAD(1st variable): Create memory for 1st element and emerge a null pointer from it.
// We create a mover variable at the memory location where HEAD is stored and now, we move to storing the next element in a data type(temp) and emerge a null pointer from it.
// mover->next = temp; now the null pointer emerging from HEAD starts pointing to 'temp'(effectively adding it to the linked list)
//(Set the next pointer of the current node pointed by mover to the newly created node, effectively adding it to the linked list.)
// and mover is incremented to the position of 'temp'(This step is essential to advance to the next position in the linked list for the next iteration of the loop), 'temp' now becomes the next memory location.
// Created all NODES while TRAVERSING in the above procedure. As HEAD was stored, we know the starting location.
// In Qs related to Linked List, entire linked list cannot be returned instead the Q demands the STARTING POINT(HEAD) of the Linked List and the rest of the traversal is taken care of.
// Technically, HEAD has to be returned so we return a POINTER TO THE HEAD(Node*) in the following function.

// TIME COMPLEXITY O(n) in conversion of array to linked list code.
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

// MAIN RULE: NEVER TAMPER HEAD - LEADS TO FORGETTING STARTING POINT

// CODESTUDIO
int lengthofLL(Node *head) // head is always provided as parameter
{
    // Copy paste the traversal and increment count to get length
    int count = 0;
    Node *temp = head; // head stored in a new pointer 'temp' so that head is NOT TAMPERED
    while (temp)       // while temp!=null or while temp is valid
    {
        count++;
        temp = temp->next; // temp->next means sending temp to point to next node
    }
    return count;
}

// CODESTUDIO
//  Given a linked list(that is, head of linked list is provided), search if an element is present in it or not
int checkIfPresent(Node *head, int val)
{
    // COPY PASTE the traversal and do not tamper the head
    Node *temp = head; // head stored in a new pointer 'temp' so that head is NOT TAMPERED
    // Write Node*<int> temp = head; in cases where TEMPLATE is used
    while (temp) // while temp!=null or while temp is valid
    {
        if (temp->data == val) //(IMPORTANT: temp->data will give ALL data/elements of Linked List)
        {
            return 1;
        }
        temp = temp->next; // temp->next means sending temp to point to next node
    }
    return 0;
}
// TIME COMPLEXITY: BEST CASE(val is head): O(1). AVERAGE CASE: O(n/2) if ELEMENT IS IN BETWEEN. WORST CASE: O(n) if ELEMENT IS AT END.

int main()
{
    vector<int> a = {2, 5, 8, 7};
    Node *x = new Node(a[0], nullptr);
    // returns pointer to the memory location(achieved using 'new' keyword)
    cout << x << endl;
    // using arrow operator with object helps to get data members
    cout << (x->data) << endl;

    // there can be multiple constructors in struct. Here, next has been assigned nullptr in constructor so no need to pass here.
    Node *x1 = new Node(a[0]);
    cout << x1->data;

    // Creating an OBJECT and accessing data members by removing 'new' keyword
    Node y = Node(a[0], nullptr);
    cout << y.data << endl;
    cout << y.next << endl;

    Node *head = convertArr2LL(a);
    // cout<<"HEAD->DATA:" <<head->data;

    // TRAVERSE AND PRINT ALL ELEMENTS of LINKED LIST
    Node *temp = head; // head stored in a new pointer 'temp' so that head is NOT TAMPERED
    while (temp)       // while temp!=null or while temp is valid
    {
        cout << temp->data << " "; // to TRAVERSE AND PRINT ALL ELEMENTS of LINKED LIST, (IMPORTANT: temp->data will give ALL data/elements of Linked List)
        temp = temp->next;         // temp->next means sending temp to point to next node
    }

    cout << "Length of Linked List: " << lengthofLL(head) << endl;

    if (checkIfPresent(head, 15))
    {
        cout << "15 is present in LL" << endl;
    }
    else
    {
        cout << "15 is not present in LL" << endl;
    }
    return 0;
}