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

Node *reverse_main1(Node *head)
{
    if (head == NULL || head->next == NULL)
    {
        return head;
    }
    Node *temp = head;
    Node *prev = NULL;
    Node *front = NULL;
    while (temp != NULL)
    {

        front = temp->next;
        temp->next = prev;
        prev = temp;
        temp = front;
    }
    return prev;
}
//WORKING
Node *add1_my(Node *head)
{
    if (head == NULL)
    {
        return NULL;
    }
    Node *dummyNode = new Node(-1);
    Node *point = dummyNode;
    Node *temp = head;
    Node *rev = reverse_main1(temp);
    print(rev);
    int carry = 0, sum;
    temp = rev;
    // cout << temp->data;
    sum = temp->data + 1;
    if (sum < 10)
    {
        rev->data = sum;
        return reverse_main1(rev);
    }
    else
    {
        int carry = sum/10;
        temp->data = sum%10;
        point->next = temp;
        point  = temp;
        // cout<<carry<<" "<<temp->data<<endl;
        Node* temp1 = temp->next;
        while (temp1)
        {
            sum = temp1->data + carry;
            temp1->data = sum % 10;
            point->next = temp1;
            point = temp1;
            carry = sum / 10;
            temp1 = temp1->next;
        }
// cout<<dummyNode->next->data<<endl;
cout<<carry<<endl;
if(carry>0)
{
    Node* c = new Node(carry);
    point->next = c;
}
        return reverse_main1(dummyNode->next);
    }
}


Node* add1_my2(Node* head)
{
     Node *t = head;
    Node *t1 = reverse_main1(t);
    Node *dummyNode = new Node(-1); // creation of dummyNode
    Node *current = dummyNode;      // pointing the current pointer to the dummyNode for effective traversal
    int carry = 0, sum = 0;
    while (t1 != NULL) // we want traversal until BOTH are null, not any one is NULL
    {
        sum = carry; //THIS LINE IS INCORPORATED SO THAT CARRY IS NOT TO BE ADDED EXPLICITLY IN SUM AND IT GETS STORED IN SUM AT BEGINNING OF NEW TRAVERSAL
        // OBSERVE EFFECTIVE TECHNIQUE TO SEPERATE CARRY FROM SUM
        sum = t1->data +1;
        Node *newNode = new Node(sum % 10);
        carry = sum / 10;
        // TRAVERSAL
        current->next = newNode;
        current = current->next;
        t1 = t1->next;
        
        if (carry)
         // After completion of traversals of both LL's, there is possibility of carry remaining which is put in a new node thereafter
        {
            Node *newNode = new Node(carry);
            current->next = newNode;
        }
        // IMPORTANT CONCEPT OF DUMMY NODE
        // Whenever we want to create a NEW LIST out of other lists, DUMMYNODE CONCEPT is preferable because
        // in case it is not used, when we first take the sum, then we need to store the new node as the head of the sumList and it makes the implementation messier.
        // By creating the dummyNode, we are able to access the new head easily using dummyNode->next.
    }
    return reverse_main1(dummyNode->next);
}

//adding 1 to 1->5->9 will give 1->6->0 that means addition has to start from 9(LAST NODE) and carry gets transferred BACKWARD that demands BACKWARD TRAVERSAL
//which is NOT POSSIBLE in SINGLY LINKED LIST, so, that demands us to REVERSE LL. Now, after reversing, we take a variable carry=1 and then store head in temp.
// Now, on addition of 9 with 1 gives 10 and the node will have value 0 so we put 0 in that node and ASSIGN CARRY=1 and then add carry with value of next node
// which gives 5+1=6. As 6<10, ao, now we can assign carry=0 and this is the condition oof STOPPING as adding carry=0 with any node's value will give the SAME VALUE, hence, when this is obtained, we have REACHED OUR RESULT. 
//We have the number in reversed order, so, we REVERSE THE MANIPULATED LL to get our RESULT.
//If the last node has value>=10 so we assign value%10 to the node and reverse the LL and then CREATE A NEW NODE and ASSIGN IT as the NEW HEAD of the RESULTANT LL.
//ESSENCE: The portion where carry is taken as 1 and that IT CONTINUES TO STORE THE CARRY OBTAINED(IF APPLICABLE)TILL THE END and that we STOP when the carry becomes 0 is
//what TAKES CARE OF BOTH CASES, value<10 and value>=10, so, seperate cases taken in my code is NULLIFIED.

// T.C. O(3n) (reverse twice + 1 traversal), S.C. O(1) 
Node* add1_main(Node* head)
{
    Node* head1 = reverse_main1(head);
    Node* temp  = head1;
    int carry = 1;
    while(temp!=NULL)
    {
        temp->data += carry;
        if(temp->data<10)
        {
            carry=0;
            break;
        }
        else{
            temp->data = 0;
            carry = 1; //as 1 is added so total sum will never go beyond 10 so temp->data can be at max 0 and carry at max 1
        }
        temp = temp->next;
    }
    if(carry==1)
    {
        Node* newNode = new Node(1); //carry will always be 1
        head = reverse_main1(head);
        newNode->next = head;
        return newNode; //newNode is our new head
    }
    head = reverse_main1(head); //we reverse the head itself if carry=0
    return head;
}

//OPTIMISATION OF O(3n) by using RECURSION BACKTRACKING
//Ex. 1> 1->5->9. Firstly, we take the first node 1, then we take the next node 5, then the next node 9, then we reach NULL(base case). 
//Now, BASE CASE instructs to add a CARRY OF 1. Here, when we COME BACK to node 9, RECURSION COMPLETES and BACKTRACKING STARTS. 
//We come back to node 9 and we add 1 to get 10. So, we REPLACE node 9 with 0 and RETURN CARRY as 1. 
//We reach node 5 and we add carry 1 to get 6. So, we replace node 5 by value 6 and RETURN carry as 0. 
//Now, when we reach node 1 and it gets carry 0, so, its value is 1+0=1. As in the END, there is carry=0 so there is no addition of new node.

//Ex.2>9->9->9->9. We move from node9, to node9, to node9, to node 9, to NULL. We get carry=1 from BASE CASE(null) and then BACKTRACKING starts to add carry=1
// to each node 9 in the path to get 10 where each node gets REPLACED BY 0 and the carry is RETURNED as 1. In the last step, CARRY=1 so there will be ADDITION OF NEW NODE,
// so, we create a new node with value 1 and we point its next to original head. 

//T.C. O(n) in 1 recursion, S.C. O(n) RECURSIVE STACK SPACE
int helper(Node* temp)
{
    if(temp==NULL)
    {
        return 1;
    }
   int carry = helper(temp->next);
   //FOLLOWING STEPS TILL THE END IS A PART OF RECURSION BACKTRACKING
    temp->data = temp->data +carry;
    if(temp->data<10)
    {
        return 0;
    }
    temp->data = 0;
    return 1;
}
Node* add1_rec(Node* head)
{
    int carry = helper(head); //This will be the FINAL CARRY(0 for 159, 1 for 9999, depending on it, NEW NODE IS ADDED)
    if(carry==1)
    {
        Node* newNode = new Node(1);
        newNode->next = head;
        return newNode; //as newNode is the NEW HEAD
    }
    return head;

}

//Pros:
//ITERATIVE: No space
//RECURSIVE: NO TAMPERING of data, addition DONE IN PLACE, done in FASTER TIME
//Cons:
//ITERATIVE: TAMPERING DATA, MORE TIME taken
//RECURSIVE: EXTRA SPACE
int main()
{
    vector<int> arr = { 9, 9};
    Node *head = convertArr2LL(arr);
    print(head);
    // head = add1_my(head);
    // print(head);
    head = add1_main(head);
    print(head);
    return 0;
}