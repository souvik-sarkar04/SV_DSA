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

// WORKING
Node *deleteAll(Node *head, int key)
{
    Node *temp1 = head;
    while (temp1 != NULL)
    {
        Node *temp = temp1;
        Node *prev1 = temp->prev;
        Node *next1 = temp->next;
        cout << "DATA IN: " << temp->data << endl;
        //  cout << "DATA BACK: " << temp->next->data << endl;
        temp1 = temp1->next;

        if (temp->data == key)
        {

            if (temp == head)
            {
                Node *h = head;
                head = head->next;
                // In deletion of head, head = head->next is IMPORTANT STEP. Do not write h = h->next as that DOES NOT SHIFT THE HEAD to the NEXT NODE.
                next1->prev = prev1;
                // h->next = NULL;
                // next1->prev = NULL;
                // temp->next = NULL;
                // temp->prev = NULL;
                //  temp = temp->next;
                free(h);
            }
            else if (next1 == NULL)
            {
                prev1->next = NULL;
                // temp->prev = NULL;
                // temp->next = NULL;
                // temp = temp->next;
                free(temp);
            }
            else
            {
                prev1->next = next1;
                next1->prev = prev1;
                // temp->prev = NULL;
                //  temp->next = NULL;
                //   temp = temp->next;
                free(temp);
            }
        }

        // cout << "DATA: " << temp1->data << endl;
    }
    return head;
}

// We take temp and start traversal. If key is at head, head is moved forward and the ORIGINAL HEAD is deleted. We take prevNode and nextNode. In case of head deletion, nextNode's prev will be NULL.
//T.C. O(n) S.C. O(1)
Node *deleteAll_main(Node *head, int key)
{
    Node *temp = head;
    while (temp != NULL)
    {
        if (temp->data == key)
        {
            if (temp == head)
            {
              head = temp->next;  // ALTERNATIVE: head = head->next;
            }

            Node *nextNode = temp->next;
            Node *prevNode = temp->prev;
            if (nextNode)
            {
                nextNode->prev = prevNode;
            }
            if (prevNode)
            {
                prevNode->next = nextNode;
            }
            free(temp);
            temp = nextNode;
        }
        else
        {
            temp = temp->next;
        }
        
    }
    return head;
}
//Qs arising from above code:
// 1) Why newNode and prevNode if blocks are written?
//Ans) These blocks take care of the fact that the LINK CHANGES between previous and next nodes of the NODE TO BE DELETED is taken care of sucessfully
// 2) Do these 2 if blocks take care of DELETION OF TAIL?
// Ans) Yes, only prevNode block gets executed
// 3) Do these 2 if blocks take care of DELETION OF HEAD?
// Ans) NO, they cannot as the HEAD does NOT get assigned to its NEW HEAD NODE and thus, it leads to LOSING THE FURTHER LINKS OF HEAD and undesirable output
// 4) Why else block is written?
// Ans) To consider the cases where the node value is NOT EQUAL to key, this case was MISSING in MY code.
    int main()
    {
        vector<int> arr = {10,4, 10, 6, 10, 10};
        Node *head = convertArr2DLL(arr);
        print(head);
        cout << endl;
        // Node* head1 = deleteAll(head, 10);
        // print(head1);
        Node *head1 = deleteAll_main(head, 10);
        print(head1);
        return 0;
    }