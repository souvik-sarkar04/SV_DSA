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

Node *sum_my(Node *num1, Node *num2, Node *temp_main)
{
    Node *temp1 = num1;
    Node *temp2 = num2;
    Node *temp3 = temp_main;
    while (temp1 != NULL && temp2 != NULL && temp3 != NULL)
    {
        temp3->data += temp2->data + temp1->data;
        if (temp3->data >= 10)
        {
            temp3->next->data = (temp3->data) / 10;
            temp3->data = (temp3->data) % 10;
        }
        if (temp3->data >= 10 && temp3->next == NULL)
        {
            Node *value = new Node(temp3->data / 10, nullptr);
            temp3->next = value;
        }
        // cout<<"Next"<<temp3->next->data<<endl;
        temp1 = temp1->next;
        temp2 = temp2->next;
        temp3 = temp3->next;
    }
    return temp_main;
}

// A DUMMY NODE is created with value -1. A variable current is used to traverse in the LL which initially points to dummyNode.
// Now, we take the sum of 2 nodes and put it in the sumList's node. We check if there is any carry, if yes, then only part excluding carry is put into
// sumList's node and the carry is assigned the value that it is to have. Now, we point current's next to the node
// in which the sum is stored and move the current to that node to EFFECT THE TRAVERSAL.
// There will come a situation when one of the Linked list's elements will be exhausted as it will contain a shorter number,
// in that case, we do NOT move the pointer of it FORWARD anymore.
// When pointers of both the linked lists are completed, we STOP and if we have a carry over, we create a new node and store the carry in it and make the current's next point to it.
// The dummyNode's next is the head of the element.

// T.C. O(max(num1, num2))
// S.C. O(max(num1, num2)) even space depends on n1 nad n2 as Q asks to STORE the values and the number of stored values will depend on the maximum value of n1 and n2 hence it cannot be optimised
Node *addTwoNumbers(Node *num1, Node *num2)
{
    Node *t1 = num1;
    Node *t2 = num2;
    Node *dummyNode = new Node(-1); // creation of dummyNode
    Node *current = dummyNode;      // pointing the current pointer to the dummyNode for effective traversal
    int carry = 0, sum = 0;
    while (t1 != NULL || t2 != NULL) // we want traversal until BOTH are null, not any one is NULL
    {
        sum = carry;
        // Adding the sum seperately gives another pattern--> Whenever there is disparity in SIZES OF LL and it needs to be managed,
        // operate them seperately so that if one of the LL's traversal ends, it does not affect the other one's traversal
        if (t1)
        {
            sum += t1->data;
        }
        if (t2)
        {
            sum += t2->data;
        }
        // OBSERVE EFFECTIVE TECHNIQUE TO SEPERATE CARRY FROM SUM
        Node *newNode = new Node(sum % 10);
        carry = sum / 10;
        // TRAVERSAL
        current->next = newNode;
        current = current->next;
        // Again to avoid null->next situation, the TRAVERSAL is done seperately
        if (t1)
        {
            t1 = t1->next;
        }
        if (t2)
        {
            t2 = t2->next;
        }
        if (carry) // After completion of traversals of both LL's, there is possibility of carry remaining which is put in a new node thereafter
        {
            Node *newNode = new Node(carry);
            current->next = newNode;
        }
        // IMPORTANT CONCEPT OF DUMMY NODE
        // Whenever we want to create a NEW LIST out of other lists, DUMMYNODE CONCEPT is preferable because
        // in case it is not used, when we first take the sum, then we need to store the new node as the head of the sumList and it makes the implementation messier.
        // By creating the dummyNode, we are able to access the new head easily using dummyNode->next.
        
    }
    return dummyNode->next;
}
int main()
{
    vector<int> num1 = {1, 2, 3};
    Node *head1 = convertArr2LL(num1);
    print(head1);
    vector<int> num2 = {9, 7, 8};
    Node *head2 = convertArr2LL(num2);
    print(head2);
    vector<int> num3;
    num3.resize(6); /*(important) without this line, vector is not getting converted to linked list*/
    fill(num3.begin(), num3.end(), 0);
    // for(auto it:num3)
    // {
    //     cout<<it<<" ";
    // }
    // Node* head3 = convertArr2LL(num3);
    // head3 = sum_my(head1,head2,head3);
    // print(head3);

    Node *head3 = addTwoNumbers(head1, head2);
    print(head3);
    return 0;
}