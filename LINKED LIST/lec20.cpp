#include <iostream>
#include <bits/stdc++.h>
using namespace std;
class Node
{
public:
    int data;
    Node *next;
    Node *prev;

    Node(int data1, Node *next1, Node *back1)
    {
        data = data1;
        next = next1;
        prev = back1;
    }
    Node(int data1)
    {
        data = data1;
        next = nullptr;
        prev = nullptr;
    }
};

// CODESTUDIO
Node *convertArr2DLL(vector<int> arr)
{
    // Node* head = new Node(head,nullptr, nullptr); //invoking the 1st constructor
    Node *head = new Node(arr[0]); // invoking the 2nd constructor
    Node *prev = head;
    for (int i = 1; i <= arr.size() - 1; i++)
    {
        Node *temp = new Node(arr[i], nullptr, prev); // 1st constructor is invoked to signify that next points to nullptr and back points to prev of arr[i]
        prev->next = temp;                            /*here, initially, the prev's next was pointing to null since it was created. This line instructs it to point to temp so that prev's next can be currently temp.*/
        prev = temp;                                  /*or prev = prev->next; here, the linking of prev and temp is done, hence, to MOVE FORWARD and make 'temp' the 'prev' of the next iteration, temp is assigned to prev.
                                          This step also serves the purpose in the next iteraton's FIRST LINE where the new NODE created will have its back pointed to its prev.*/
    }
    return head;
}
void print(Node *head)
{
    Node *temp = head;
    while (temp != NULL)
    {
        cout << temp->data << " ";
        temp = temp->next;
    }
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

// WORKING except cases where last element has duplicates
Node *delDuplicates_my(Node *head)
{
    if (head == NULL || head->next == NULL)
    {
        return head;
    }
    Node *temp = head;
    // Node *prev = NULL;
    while (temp->next != NULL) // VERY IMPORTANT, DO NOT WRITE TEMP!=NULL as temp REACHING LAST NODE AND TEMP->NEXT->NEXT WILL NOT MAKE SENSE
    // ALWAYS CHECK IF THE LOOP CONDITION IS RENDERING SOME POINTER INVALID
    {
        if (temp->data == temp->next->data)
        {
            Node *del = temp->next;
            // cout<<"del: "<<del->data<<endl;
            del->next->prev = temp;
            // cout<<"prev:  "<<del->next->prev->data<<endl;
            temp->next = del->next;
            // cout<<"temp->next: "<<temp->next->data<<endl;

            del->prev = nullptr;
            del->next = nullptr;
            free(del);
        }
        else // ANOTHER IMPORTANT POINT- IF THE PARTICULAR DUPLICATE HAS A FREQUENCY > 2, THEN, WE CANNOT INCREMENT THE TEMP UNTIL ALL
        // DUPLICATE OCCURRENCES OF THE ELEMENT IS REMOVED. IF IT IS MOVED ALWAYS, THEN ONLY ONE DUPLICATE OCCURRENCE IS REMOVED.
        {
            // cout<<"temp before: "<<temp->data<<endl;
            temp = temp->next;
            // cout<<"temp after: "<<temp->data<<endl;
        }
        if (temp->next->next == NULL && temp->data == temp->next->data)
        {
            Node *del1 = temp->next;
            temp->next = NULL;
            free(del1);
        }
    }
    temp = head;
    while (temp)
    {
        cout << temp->data << " ";
        temp = temp->next;
    }
    return head;
}

// SORTED DLL-> Duplicates will be in CONTIGUOUS MANNER. We point temp to head, if there is a duplicate of head,
//  then nextNode at head->next has same data, then we move nextNode to the following node and in this way, until the data is not equivalent to head's data,
//  we increment it and then we point temp's next to nextNode and nextNode's prev to temp.
// As we HAVE CHANGED THE LINKS, temp->next sends it to the next NON-DUPLICATE NODE and nextNode is temp's next.
// nextNode is the first element that has data not equal to temp's data. We STOP when temp REACHES LAST NODE as beyond last node, there can be no duplicates.

// T.C. O(n) (VERY IMPORTANT- NESTED LOOPS DO NOT ALWAYS MEAN O(n^2) but HOW?
//  The outer loop traverses NON-DUPLICATE ELEMENTS and the inner loop traverses DUPLICATE ELEMENTS so total traversals = length of LL
// S.C. O(1)
Node *delDuplicates_main(Node *head)
{
    if (head == NULL || head->next == NULL)
    {
        return head;
    }
    Node *temp = head;

    while (temp != NULL && temp->next != NULL) // temp!=NULL is IMPORTANT as it takes care of situation when LAST ELEMENT ALSO HAS DUPLICATES
    // The reason is CRITICAL: Consider the scenario when only 1 duplicate of the last element is present, that is the last 2 nodes have the SAME DATa.
    // Now, when the only duplicate is REMOVED, temp is sent to its next which is now NULL. Now, when the loop condition is checked(without
    // temp!=NULL written), the loop condition reads null->next!=NULL which DOES NOT MAKE SENSE. So, to incorporate the condition for
    // this situation, temp!=NULL is added.
    // CONCLUSION: Check for all possibilities and ALWAYS CHECK LOOP CONDITION AND VERIFY IF IT RENDERS ITSELF OR ANY OTHER POINTER
    //  IN THE LOOP BODY AS A SENSELESS INFO.
    {
        Node *nextNode = temp->next;
        while (nextNode != NULL && temp->data == nextNode->data)
        // THIS PARTICULAR LOOP SOLVES THE PROBLEM of DELETING MULTIPLE DUPLICATES or the MAJOR PROBLEM OF DELETING ULTIPLE DUPLICATES OF LAST
        // ELEMENT. What it does is it traverses until it finds the next NON-DUPLICATE NODE and DELETES ALL DUPLICATE ELEMENTS BEFORE THAT.
        //ESSENCE: When we want our counter variable to be compared to SEVERAL CONSECUTIVE ELEMENTS and produce an output,
        //a SEPERATE INNER LOOP with a SEPERATE VARIABLE is beneficial for this comparison and related operations
        {
            // Technique to delete multiple duplicate nodes
            Node *duplicate = nextNode;
            nextNode = nextNode->next;
            free(duplicate);
        }
        temp->next = nextNode;
        if (nextNode != NULL)
        // This is a check for the LAST NODE'S DUPLICATES. There will come a situation when nextNode will delete all duplicates of last
        // element and FINALLY POINT TO NULL. If that is so, then null's prev does not make sense so to avoid that, this block is written.
        {
            nextNode->prev = temp;
        }

        temp = temp->next;
        // nextNode = nextNode->next;
    }
    return head;
}

int main()
{
    vector<int> arr = {1, 2, 2, 2, 3, 4, 4, 5, 5};
    Node *head = convertArr2DLL(arr);
    print(head);
    cout << endl;
    head = delDuplicates_main(head);
    print(head);
    return 0;
}