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
int maxi = INT_MIN;
int mini = INT_MAX;
int maximum(Node *head)
{
    if (head == NULL || head->next == NULL)
    {
        return head->data;
    }
    Node *temp = head;

    while (temp)
    {
        if (temp->data > maxi)
        {
            maxi = temp->data;
        }
        temp = temp->next;
    }
    return maxi;
}
int minimum(Node *head)
{
    if (head == NULL || head->next == NULL)
    {
        return head->data;
    }
    Node *temp = head;

    while (temp)
    {
        if (temp->data < mini)
        {
            mini = temp->data;
        }
        temp = temp->next;
    }
    return mini;
}
Node *y_intersect(Node *head1, Node *head2)
{
    if (head1 == NULL || head2 == NULL)
    {
        return NULL;
    }
    vector<int> a(max(lengthofLL(head1), lengthofLL(head2)));
    std::fill(a.begin(), a.end(), 0);
    Node *temp1 = head1;
    while (temp1)
    {
        a[temp1->data] += temp1->data;
        temp1 = temp1->next;
    }

    Node *temp2 = head2;
    while (temp2)
    {
        a[temp2->data] = a[temp2->data] - temp2->data;
        if (a[temp2->data] == 0)
        {
            return temp2;
        }
        temp2 = temp2->next;
    }
    return NULL;
}

// While traversing through both the LLs, we realize that if we memorise the node values of the 1st LL and while traversing the 2nd LL,
//   if we find an element has been VISITED AGAIN, then, we return it as the first intersection node.
// Concept of HASHING will be used to solve this Q.
// We take a MAP DS and store the NODES(not VALUES) of the 1st linked list in the map using a pointer temp.
// Now, we move ahead and traverse the 2nd linked list and when we find the FIRST REPEATING NODE, we STOP.
//  T.C. O(n1*map's time complexity + n2*map's time complexity)  S.C. O(N1) or O(N2) depending on the linked list that gets ENTIRELY stored in map.
//NOT WORKING
Node *y_intersect_brute(Node *head1, Node *head2)
{
    // if (head1 == NULL || head2 == NULL)
    // {
    //     return NULL;
    // }
    unordered_set<Node*> st;
    Node *temp = head1;
    while (temp != NULL)
    {
        // pair<Node*, int> nodePair(temp, temp->data);
        st.insert(temp);
        temp = temp->next;
    }
    temp = head2;
    while (temp != NULL)
    {
        // auto it = st.find(temp);
        if (st.find(temp)!= st.end())
        {
            // use the != operator to compare the iterator returned by find with end() to check if the element was found or not. If find doesn't find the element, it returns the iterator equal to end().
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}
//NOT WORKING
Node* intersectionPresent1(Node* head1,Node* head2) {
     unordered_set<Node*> st;
    while(head1 != NULL) {
       st.insert(head1);
       head1 = head1->next;
    }
    while(head2 != NULL) {
        if(st.find(head2) != st.end()) return head2;
        head2 = head2->next;
    }
    return NULL;

}

Node *collisionPoint(Node *t1, Node *t2, int d)
{
    while (d) // to first traverse the LONGER LL by distance d
    {
        d--;
        t2 = t2->next;
    }
    while (t1 != t2) // for COMMON TRAVERSAL of both LLs until COMMON INTERSECTION POINT is obtained
    {
        t1 = t1->next;
        t2 = t2->next;
    }
    return t1;
}
// we find out lengths of the 2 LLs, say N1 and N2(N2>N1). difference(d) = N2-N1. Now, we move the t2 pointer of the larger LL by d steps forward and then start the COMMON TRAVERSAL of both the LLs until the intersection node is obtained.
// T.C. O(n1+n2+(n2-n1)+n1)(length traversals n1 and n2, (n2-n1) for forward traversal of the longer LL, n1 for MAX POSSIBLE common traversal) = O(n1+2n2)(OPTIMISATION needed)
// S.C. O(1)
Node *intersection_brute1(Node *head1, Node *head2)
{
    Node *t1 = head1;
    Node *t2 = head2;
    int n1 = lengthofLL(t1);
    int n2 = lengthofLL(t2);
    if (n1 < n2)
    {
        collisionPoint(head1, head2, n2 - n1); // assuming head2 is greater LL than head1 and cover a distance of (n2-n1) and find out a collision point
    }
    else
    {
        collisionPoint(head2, head1, n1 - n2);
    }
}

Node* intersectionPresent(Node* head1,Node* head2) {
 int diff = lengthofLL(head1) - lengthofLL(head2);
        if(diff < 0) 
            while(diff++ != 0) head2 = head2->next; 
        else while(diff-- != 0) head1 = head1->next;
        while(head1 != NULL) {
            if(head1 == head2) return head1;
            head2 = head2->next;
            head1 = head1->next;
        }
        return head1;
}



// Optimal approach is starting from the head of both LLs, t1 for LL1 and t2 for LL2. Once one of the pointers reaches the LAST NODE, 
// it is transferred to the HEAD OF THE OTHER LINKED LIST and the traversal is carried on. At a certain point,
//  both the pointers REACH THE SAME VERTICAL LEVEL from where COMMON TRAVERSAL can be done to find intersection node.
// EDGE CASES:
//  Above algorithm was for the situation when both LLs have different lengths.
//  Now, if they have same length, then on reaching null, temp of 1 LL moves to head of another algorithm is unnecessary as they will reach the intersection point together
// If they do not intersect, then the same algorithm is applied and then if they reach the LAST NODE TOGETHER, we say they have no intersection.

// INTUITION OF ALGORITHM: Lets say the difference in length of 2 LLs is d. So, if t2 is pointer of longer LL, it is always d STEPS BEHIND t1.
//  When t1 reaches null, it is sent to head2 and now, t2 is behind t1 by the SAME d STEPS in a REVERSE CIRCULAR MANNER.
//  As the pointers maintain a difference of d steps until they are transferred to the respective heads of the other LL, they align vertically on reaching the other LL.
// T.C. O(n1+n2) at WORST CASE when they do not intersect.
Node *intersection_optimal(Node *head1, Node *head2)
{
    Node *t1 = head1;
    Node *t2 = head2;
    while (t1 != t2)
    {
        t1 = t1->next;
        t2 = t2->next;
        if (t1 == t2)
        {
            return t1; // or return t2; //This is EXIT CONDITION of COLLISION(intersection)
        }
        if (t1 == NULL)
        {
            t1 = head2;
        }
        if (t2 == NULL)
        {
            t2 = head1;
        }
    }
    return t1; //returns NULL when both the pointers reach NULL when there is no node of intersection
}
int main()
{
    vector<int> arr1 = {1, 2, 3, 4, 5};
    Node *head1 = convertArr2LL(arr1);
    print(head1);
    vector<int> arr2 = {6, 7, 8, 3, 4, 5};
    Node *head2 = convertArr2LL(arr2);
    print(head2);
    //  vector<int> a(max(lengthofLL(head1), lengthofLL(head2)));
    // std::fill(a.begin(), a.end(), 0);
    // for(auto it:a)
    // {
    //     cout<<"Element:"<<it;
    // }
    Node *in = intersection_optimal(head1, head2);
    cout << "Result:" << in->data;
    return 0;
}