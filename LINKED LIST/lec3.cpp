#include <iostream>
#include <bits/stdc++.h>
using namespace std;
// In DOUBLY LINKED LIST, not only forward linking is present(like Singly linked list) but also has BACKWARD LINKING(BOTH SIDE MOVEMENT).

// Thus, we need to remember the PREVIOUS NODE(here, back node)
//DOUBLY LINKED LIST is used in BROWSERS
class Node
{
public:
    int data;
    Node *next;
    Node *back;

    Node(int data1, Node *next1, Node *back1)
    {
        data = data1;
        next = next1;
        back = back1;
    }
    Node(int data1)
    {
        data = data1;
        next = nullptr;
        back = nullptr;
    }
};

//CODESTUDIO
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

// NO OUTPUT
Node *deleteHead_my(Node *head)
{
    if (head == NULL)
    {
        return head;
    }
    Node *temp = head;
    if (head->next == NULL)
    {
        head = head->next;
        return temp;
    }
    // When LL has >1 elements, the head has to be moved forward and the head cannot have 'back' pointing to something.
    // head always has back pointing to 'nullptr' soo that has to be ensured.
    head = head->next;
    temp->next = nullptr;
    head->back = nullptr;
    free(temp);

    return head;
}

Node *deleteHead(Node *head)
{
    if (head == NULL || head->next == NULL)
    // For EMPTY LL or SINGLE HEAD, to remove it, simply writing 'return NULL' is enough to delete it as NULL being a value of the pointer(here, head) returned will signify that the 2D LL is NOW EMPTY
    {
        return NULL;
    }
    Node *prev = head;

    // store CURRENT HEAD as PREV. Then, we move head to the NEXT NODE. So, we point head's BACK to nullptr as head cannot have 'back' pointing to something.
    // we have a prev pointing to head, so, to REMOVE THE LINK between prev and head, we point PREV'S NEXT to NULLPTR.

    head = head->next;
    head->back = nullptr;
    prev->next = nullptr;
    free(prev);

    return head; // DON'T FORGET THIS LINE, Otherwise infinite output is the result
}

//CODESTUDIO
Node *deleteTail(Node *head)
{
    if (head == NULL || head->next == NULL)
    {
        return NULL;
    }
    Node *temp = head;
    // Node *prev = NULL;
    while (temp->next != NULL)
    {
        // prev = temp;
        temp = temp->next;
    }
    // In 2D LL, the advantage to access the previous element without keeping its track in the traversal is shown in the following line
    Node *prev = temp->back;
    // to DELETE TAIL, tail 'back' should point to nullptr and new tail's next points to nullptr to segregate the ORIGINAL TAIL from the LL
    prev->next = nullptr;
    temp->back = nullptr;
    return head;
    // prev here is the nEW TAIL and temp is the ORIGINAL TAIL of 2D LL
}

// k is from 1 to LENGTH
Node *deleteKth(Node *head, int k)
{
    int count = 0;
    if (head == NULL)
    {
        return NULL;
    }
    // if (head->next == NULL && k == 1)
    // {
    //     return NULL;
    // }
    Node *temp = head;
    while (temp != NULL)
    {
        count++;
        if (count == k) // Coming to the kth NODE
        {
            break;
        }
        temp = temp->next;
    }
    // After this, temp is standing at KTH NODE
    Node *prev = temp->back;

    // Notice how the FRONT node is also accessed as well as the BACK node - OBSERVE this in 2D LL
    Node *front = temp->next;

    // OBSERVE EDGE CASES AND NOTE THEM
    //  1st EDGE CASE
    if (prev == NULL && front == NULL) // When there is only 1 NODE
    {
        free(temp);
        return NULL;
    }

    // 2nd EDGE CASE
    else if (prev == NULL) // temp is at HEAD, delete HEAD
    {
        return deleteHead(head);
    }

    // 3rd EDGE CASE
    else if (front == NULL) // temp is at TAIL, delete TAIL
    {
        return deleteTail(head);
    }

    // prev->next = prev->next->next; this line can be written as the following line
    prev->next = front;
    front->back = prev; // In case of 2D LL, ALWAYS REMEMBER BACKWARD LINKING

    // DESTROYING FORWARD AND BACKWARD LINK OF TEMP WITH 2D LL
    temp->back = nullptr;
    temp->next = nullptr;
    free(temp);
    return head;
}

//Do not remove HEAD
Node* deleteVal_my(Node* head, int val)
{
    Node* temp = head;
    while(temp!=NULL)
    {
        if(temp->data == val)
        {
            break;
        }
        temp = temp->next;
    }
    Node* prev = temp->back;
    Node* front = temp->next;
    // if(prev==NULL && front==NULL)
    // {
    //     return NULL;
    // }
     if(front==NULL)
    {
        return deleteTail(head);
    }

    prev->next = front;
    front->back = prev;
    temp->back = nullptr;
    temp->next = nullptr;

    return head;
}

//Do not remove HEAD because the head has to be moved forward and more conditions will have to be written which is AVOIDED by the INSTRUCTION of the Question
void deleteNode(Node* temp)
{
    //In this code, the input does not demand the code to reach the NODE TO BE DELETED, rather the INPUT will be such that it will REACH THE NODE TO BE DELETED ITSELF.
    Node* prev=  temp->back;
    Node* front=  temp->next;

    if(front==NULL) //removing TAIL
    {
        prev->next = nullptr;
        temp->back = nullptr; //Destroying link of temp with LL
        free(temp);
        return;
    }
    prev->next = front;
    front->back = prev;

    temp->next = nullptr;
    temp->back = nullptr;
    free(temp);
}

Node* insertBeforeHead(Node* head, int val)
{
    Node* temp = head;
    // if(head==NULL)
    // {
    //     Node* h = new Node(val,nullptr,nullptr);
    //     return h;
    // }
    Node* newHead = new Node(val,head, nullptr);
    //a new node is created whose 'back' is pointing to nullptr and 'next' is pointing to ORIGINAL HEAD
    head->back = newHead; //In INSERTION OR DELETION in 2D LL, BACKWARD LINKING has to be CONSIDERED ALWAYS(do not forget)
    return newHead;
    }

Node* insertBeforeTail(Node* head, int val)
{
    if(head->next == NULL) //if the LL has only 1 element
    {
        return insertBeforeHead(head,val);
    }
    Node* temp = head;
    while(temp->next!=NULL) //technique to take temp to the TAIL OF 2D LL
    {
        temp = temp->next;
    }
     Node* prev = temp->back;

     //creating a node with value 'val' whose next points to 'temp' and back points to 'temp->back'
     Node* newTail = new Node(val, temp, prev);
     

    //   newTail->back = prev;
     //   newTail->next = temp;

    //ensuring that the FORWARD LINKING of prev is newTail and the BACKWARD LINKING OF temp is newTail
      prev->next = newTail;
      temp->back = newTail;
      return head;
}

//CODESTUDIO
Node* insertAfterTail(Node* head, int val)
{
    if(head==NULL) //new tail inserted at EMPTY 2D LL
    {
        return new Node(val);
    }
    Node* temp = head;
    while(temp->next!=NULL)
    {
        temp = temp->next;
    }
    Node* newTail = new Node(val,nullptr,temp);
    temp->next = newTail;
    return head;
}

Node* insertBeforeKth(Node* head, int k, int val)
{
    if(head==NULL)
    {
        return NULL;
    }
    if(k==1) //k=1 means HEAD 
    {
        return insertBeforeHead(head,val);
    }
    if(k==length) //k=length means TAIL
    {
        return insertBeforeTail(head, val);
    }

    Node* temp = head;
    int count=0;
    while(temp->next!=NULL)
    {
        if(count==k) //reaching kth element
        {
            break;
        }
        temp = temp->next;
    }

    //(VERY IMPORTANT) declaring 'prev' before the while loop is DISASTROUS as that does not give the CORRECT NODE that we want as 'prev' AFTER we REACH THE KTH ELEMENT.
    //To get the ACTUAL PREV, we must declare it AFTER THE TRAVERSAL IS OVER.
    Node* prev = temp->back;
    // Node* front = temp->next;

    Node* value = new Node(val,temp,prev);
    
    temp->back = value;
    prev->next = value;
    return head;
}

//void because there is no change of head
void insertNodeBefore(Node* temp, int val)
{
    Node* prev = temp->back;
    // Node* front = temp->next;
    Node* value = new Node(val,temp,prev);
    temp->back = value;
    prev->next = value;
}
int main()
{
    vector<int> arr = {12,5,8,7};

    // Converting array to 2D LL
    Node *head = convertArr2DLL(arr);
    print(head);

    // Deleting HEAD of 2D LL
    // head = deleteHead(head);
    // If function RETURNS A POINTER, ASSIGN it to HEAD and then print it otherwise infinite loop is the result
    //  print(head);
    cout << endl;
    // Deleting TAIL of 2D LL
    // head = deleteTail(head);
    // To call deleteTail(), stop execution of deleteHead() otherwise head gets deleted along with tail
    // print(head);

    // DELETING KTH ELEMENT of 2D LL
    // head = deleteKth(head, 3);
    // print(head);

    // DELETING GIVEN NODE of 2D LL
    // head = deleteVal_my(head, 8);
    // deleteNode(head->next);
    // deleteNode(head->next->next);
    // print(head);

    //INSERTING NEW HEAD of 2D LL
    // head = insertBeforeHead(head,10);
    // print(head);

     //INSERTING NEW TAIL of 2D LL
    // head = insertBeforeTail(head,10);
    // print(head);

    //INSERTING NEW NODE BEFORE KTH ELEMENT
    // head = insertBeforeKth(head,3,10);
    // print(head);

    //INSERTING NEW NODE BEFORE VALUE
    insertNodeBefore(head->next,10);
    insertNodeBefore(head->next->next,100);
    print(head);
    return 0;
}