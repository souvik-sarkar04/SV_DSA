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

// GOOGLE
// We take a MAP and store the NODES in it.(not values because before reaching the starting node, if we get a node with a value SAME AS THE VALUE OF THE STARTING NODE, then the purpose is not served).
// Before inserting a node in map, we check if the node is ALREADY PRESENT in the map.
// T.C. O(n*2*logn) S.C. O(n)(needs OPTIMISATION)
Node *startingLoop_brute(Node *head)
{
    map<Node *, int> mpp;
    Node *temp = head;
    while (temp)
    {
        if (mpp.find(temp) != mpp.end())
        {
            return temp;
        }
        mpp[temp] = 1; // INSERTION: map_name[node] = value
        temp = temp->next;
    }
    return NULL; // Executed if LL is LINEAR
}

// OPTIMISATION: TORTOISE AND HARE ALGORITHM
//  Step-1: Detect a loop
//  Step-2: Finding the starting point
// After detecting the loop, both the slow and the fast pointers are pointing to the same node in the loop. Now, we move slow to head and fast remains at its original position.
// Now, we move them SIMULTANEOUSLY and we REALISE that they COLLIDE AGAIN, this time at the STARTING POINT OF THE LOOP.
// ESSENCE: If we would have started the slow and fast pointers from the STARTING POINT OF THE LOOP, they would have collided at the STARTING POINT ITSELF.
// Instead, if we start the traversal of slow and fast 'k' NODES BEFORE, then both the pointers COLLIDE 'K' NODES BEFORE THE STARTING POINT.
//  Now, as we have started the pointers k nodes before, that means kth nodes before, we have HEAD OF LL. This proves that the HEAD OF LL and COLLISION POINT are equidistant
// and hence, SIMULTANEOUS TRAVERSAL of slow from head and fast from collision point helps to reach the starting point of the loop.

// INTUITION: 1) HOW are we so sure that they will COLLIDE?
//  2)HOW are we sure that the COLLISION POINT will be the STARTING POINT OF THE LOOP?
//  Ans) Whenever slow is pointing to the STARTING POINT OF THE LOOP for the FIRST time(lets say after 3 nodes), the fast will be pointing after 6 nodes of head.
// This also certifies another fact. If the slow pointer is now at a distance L1(here,3)(distance between head and starting point of loop), then,
// fast is also exactly at L1 distance from the starting point of the loop(6-3=3). Let's assume that distance between fast and slow pointers is d.
// Fast is MOVING TOWARDS slow by 2 so, distance should DECREASE by 2. But slow MOVES AWAY from fast by 1 step so EFFECTIVELY fast moves TOWARDS slow by 1 step.
// Eventually d gets decremented to 0 and there they will COLLIDE.
//  From the time the slow was pointing to the starting node to the point it collides with fast, fst covers 2d distance and slow covers d distance.
// From the above conclusions, we deduce that the length of the loop is L1+d and as now, the distance of the collision point from the starting point is d(as slow covers distance d),
// from the counter-rotation direction, the distance between the starting point and the collision point is L1. We also remember that distance between HEAD and starting point is also L1
// and hence, when slow moves L1 distance from HEAD and fast moves L1 distance from COLLISION POINT and approach the STARTING POINT OF LOOP SIMULTANEOUSLY, they collide at the starting point of loop.

Node *startingLoop_optimal(Node *head)
{
    Node *slow = head;
    Node *fast = head;
    while (fast != NULL && fast->next != NULL)
    {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) // slow and fast must be UPDATED BEFORE CHECKING otherwise head is returned as INITIALLY they both point to head
        {
            // This part is written inside while loop so that we can conside the case of LINEAR LL also where we should return null
            slow = head;
            while (slow != fast)
            {
                slow = slow->next;
                fast = fast->next;
            }
            return slow; // or return fast;
        }
    }
    return NULL;
}
int main()
{
    vector<int> arr = {1, 2, 3, 4, 5};
    Node *head = convertArr2LL(arr);
    print(head);
    Node *temp = head;
    while (temp->next)
    {
        temp = temp->next;
    }
    temp->next = head->next->next;
    Node *st = startingLoop_brute(head);
    cout << st->data;
    Node *st1 = startingLoop_optimal(head);
    cout << st1->data;
    return 0;
}