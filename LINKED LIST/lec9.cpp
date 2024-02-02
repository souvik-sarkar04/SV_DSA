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

// T.C. O(n) S.C. O(1)
Node *reverse_main1(Node *head)
{
    if (head == NULL || head->next == NULL)
    {
        return head;
    }
    Node *temp = head;
    Node *prev = NULL;
    Node *front = NULL;
    // In LEC4, the constructor had the ability to STORE THE PREVIOUS NODE, but here it is not possible.
    // So, the algorithm is like first the element NEXT to the temp CURRENTLY is stored and 
    //then the 'next' pointer of temp is assigned its PREVIOUS NODE. Then, both the prev and temp are moved forward.
    while (temp != NULL)
    {

        front = temp->next;
        temp->next = prev;
        prev = temp;
        temp = front;
        // cout<<prev->data<<temp->data<<front->data<<endl;
        // cout<<"Data1: "<<temp->data<<endl;
    }
    // IMPORTANT LINE: After reversing(or in general MANIPULATING A LL), return head is a WRONG STATEMENT as it does not give the NEW HEAD of the LL.
    // Analysis is required to DEDUCE THE NEW HEAD and in terms of some variable, it has to be returned. Handwritten TRAVERSAL DRY RUN helps in such situations.
    return prev;
}
// Reversing LL Recursively: Say, reversing 4 nodes means reversing 3 nodes in next step, in further next step reverse 2 nodes and in final step everse final step.
Node *prev1 = NULL;
Node *front1 = NULL;
// WORKING
Node *reverse_rec_my(Node *head)
{
    Node *temp = head;
    if (temp == NULL)
    {
        return prev1;
    }
    front1 = temp->next;
    temp->next = prev1;
    prev1 = temp;
    return reverse_rec_my(front1);
}

//Solving problem for 2 nodes: Suppose our second last node is 2 and last node is 5.
//We take 2 as head and 5 as front. To apply reversal, we write front->next = head and head->next = NULL then we return front as our new head
//For 3 nodes, first we get the solution of the problem of 2 nodes, now, we assume that element BEFORE 2 ORIGINALLY was 3.
//So, we assign 3 as head and 2 as front and write front->next = head and head->next = NULL then we return newHead as our new head

//T.C. O(n) S.C. O(n) because of RECURSION STACK SPACE(IMPORTANT)

Node *reverseLinkedList(Node *head)
{
    if (head == NULL || head->next == NULL) // 0 elements or 1 elements
    {
        return head;
    }
    Node* newHead = reverseLinkedList(head->next);
   Node* front = head->next;
    front->next = head;
    head->next = NULL;
    return newHead;
}

//HEAD RECURSION has been used in the above problem to solve it.
//We take a LL say 1->3->2->5. So, when we enter the function, our head is 1 and after failing the base case, the RECURSIVE CALL is executed
//which sends the entire LL from the NEXT ELEMENT. This continues until the ENTIRE LL is BROKEN DOWN into a SINGLE ELEMENT LL.
//  VERY IMPORTANT POINT TO NOTE(ESSENCE 1) is in the algorithm, we were struggling to reach the LAST NODE of the LL from 
// where we intended to REVERSE THE LINKS. The HEAD RECURSION solves till problem and breaks down the LL and we achieve to reach the LAST NODE.
//Once we reach the last node, the BASE CASE is executed and so, it moves to the previous recursion call's body with a LL that has its head as 5.
//Now, newHead is obtained as 5 and front = head->next is executed. Important to note is in the previous recursion call, 2->5 was passed so ITS HEAD is 2.
//  So, 2->next =5 is assigned as front.
//front->next = head is executed so 5->next = 2 is done so now the LL becomes 2<-5. This is an IMPORTANT STEP in changing the links to REVERSE the LL.
//  Now, we return the newHead which was assigned 5 in the beginning of the body,so, the previous recursion call now gets newHead as 5. 
// Now, the situation is like 3 is pointing to 1 and 2 is pointing to NULL. 
// It was passed 3->2->5 so ITS HEAD is 3 so when front = head->next is executed, front = 3->next that is 2.
//  Now, front->next = head means 2->next = 3 which reverses the link between 2 and 3.
//Ultimately, 3<-2<-5 is obtained(next of 3 is changed from 1 to NULL and next of 2 is changed from NULL to 3) 
// and newHead that is 5 is returned and the recursion carries on to reverse the entire LL. 
//ESSENCE 2: By storing the recursive call in newHead and FINALLY RETURNING it, we are able to RETAIN the LAST NODE as the LL'S NEW HEAD.
//ESSENCE 3: In each recursive call, the component LL's are passed and the FIRST ELEMENT of each such LL is considered HEAD in that particular recursion body.
// By using essence 3, we conclude that in each recursive call, it gets a REVERSED SUB-LINKED LIST whose last element points to NULL. 
// To point that last element to the head of the present recursive call,
//we remember that this last element is ORIGINALLY the NEXT ELEMENT of that head and so that element is stored in FRONT
// and to reverse the link, front's next is POINTED to the CURRENT HEAD.
int main()
{
    vector<int> arr = {1, 2, 3, 4, 5};
    Node *head = convertArr2LL(arr);
    print(head);
    // head = reverse_main1(head);
    // print(head);
    // head = reverse_rec_my(head);
    // print(head);
    head = reverseLinkedList(head);
    print(head);
    return 0;
}