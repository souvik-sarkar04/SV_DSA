#include <iostream>
#include <bits/stdc++.h>
using namespace std;

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

// Deleting elements from Linked List:
//  I) Deleting head:
//  We store the initial head into a temp pointer and move the head to point to the next node,
// ultimately changing the head of the Linked List. This means that the original 'head' remains in memory and to free its space, we free temp(that is why, temp was created).
Node *removesHead(Node *head)
{
    if (head == NULL) //(EDGE CASE to write in EVERY LINKED LIST CODE)checking if LINKED LIST IS EMPTY
    {
        return head;
    }
    Node *temp = head;
    head = head->next;
    free(temp); // or write delete temp;
                // to free the temp memory(original head)
    return head;
}

// CODESTUDIO
Node *deleteTail(Node *head)
{
    if (head == NULL || head->next == NULL)
    // head==null means Empty Linked List and head->next ==null means 1 element in Linked List(which acts as tail which if removed leaves nothing hence null is returned in both cases)
    {
        return NULL;
    }
    Node *temp = head;               // we create temp and store head in it so that we do not have to ALTER HEAD and we can return it properly
    while (temp->next->next != NULL) // observe the technique to point to 2 positions ahead of temp
    {
        temp = temp->next; // when position ahead of second last node is not NULL, make the pointer pointing to the second last position move forward
    }
    free(temp->next); // delete temp->next;
    // free the memory of tail
    temp->next = nullptr; // writing NULL here instead of nullptr also works
    // make the tail memory NULL
    return head; // return head in every program of LL
}

Node *deletePos_my(Node *head, int pos)
{
    int count = 1;
    if (head == NULL)
    {
        return head;
    }
    Node *temp = head;
    while (temp->next != NULL)
    {
        count++;
        if (count == pos)
        {
            // free(temp->next);
            // temp->next = temp->next->next;
            // count = 0;
            // break;
        }
        // else if (count > pos)
        // {
        //     cout << "Position greater than length" << endl;
        // }
        // else
        // {
        //     continue;
        // }
    }
    return head;
}

//pos=1 means removing HEAD, pos=length means REMOVING TAIL, any other case will mean removing MIDDLE ELEMENT of LL.
//Think of EDGE CASES always(here, pos=1, pos=length, etc.)
// Time Compexity = O(k).
Node *deletePos(Node *head, int pos)
{
    
    if (head == NULL) //Empty LL
    {
        return head;
    }
    if(pos==1) //HEAD REMOVAL
    {
        Node* temp = head; //OPTIONAL
        head = head->next;
        free(temp); //OPTIONAL
        return head;
    }
    int count = 0;
    Node *temp = head; /*remembering the head*/
    Node* prev = NULL; /*creating a prev pointer which will help us locating the node previous to the NODE TO BE DELETED
                        so that it can be accessed and its 'next' pointer can be pointed to the NEXT VALID NODE*/
    while(temp!=NULL)
    {
        count++;
        if(count==pos)
        {
            prev->next = prev->next->next;
                                            /*locating the node previous to the NODE TO BE DELETED
                                            so that it can be accessed and its 'next' pointer can be pointed to the NEXT VALID NODE*/
            
            free(temp);/*temp at this iteration points to the ELEMENT TO BE DELETED hence its memory is freed*/
            break;
        }
        prev = temp; /*assigning temp tp prev here simply means that prev will point to the CURRENT location
        that temp points to, which will in the next line act as the PREVIOUS POSITION to the node to which TEMP WILL POINT*/
        temp = temp->next;
    }
    return head; /*count>pos, no need to write this case as it is automatically assumed and entire LL is entered*/
}

Node* deleteVal(Node* head, int val)
{
    if(head==NULL)
    {
        return head;
    }
    if(head->data==val) 
    //HEAD REMOVAL - ALWAYS CHECK for this EDGE CASE whenever there is SITUATION OF REMOVING ELEMENTS other than HEAD and TAIL
    {
        Node* temp = head; //OPTIONAL
        head = head->next;
        free(temp); //OPTIONAL
        return head;
    }
    Node* temp = head;
    Node* prev = NULL;
    while(temp!=NULL)
    {
        if(temp->data == val) //TEMP->DATA is the way to access CURRENT ELEMENT
        {
            prev->next = prev->next->next;
            free(temp);
            break;
        }
        prev = temp;
        temp = temp->next;
    }
    return head; //never forget
}

//TIME COMPLEXITY: O(1)
Node* insertHead(Node* head, int val)
{
    if(head==NULL)
    {
        return new Node(val);
        //in case the LL is empty, this is a method of creating a NEW NODE and passing it as its NEW HEAD(NEW TAIL also here)
    }
    Node* temp = new Node(val, head); 
    //Passing head as 'next1' to 1st constructor shows we want head as CURRENT NEXT NODE
   
    //ALTERNATIVE CODE
    // Node* temp = new Node(val);
    // h1->next = head; //LINKING EXTERNAL ELEMENTS TO CURRENT HEAD USING ->next
    
    return temp; //Return NEW HEAD
}

Node* insertTail_my(Node* head, int val)
{
     if(head==NULL) 
    {
        return head; 
    }
    Node* temp = new Node(val); //Creation of node using val
    Node* head1 = head;
    while(head1!=NULL)
    {
        if(head1->next==NULL)
        {
            head1->next = temp;
            break;
            //This 'break' is VERY IMPORTANT in the context of the program. Consider the 1st time when the tail which was 
            //initially pointing to nullptr will now point to the node containing val. Now, in absence of 'break', head1 will never be NULL
            //and head1->next will ALWAYS BE NULL, resulting in INFINITE TIMES INSERTION of val at the tail. To prevent that, break is applied.
        }
         head1 = head1->next;
    } 
    return head;
}

Node* insertTail(Node* head, int val)
{
  if(head==NULL)
    {
        return new Node(val); 
        //in case the LL is empty, this is a method of creating a NEW NODE and passing it as its NEW HEAD(NEW TAIL also here)
    } 
    Node* temp = head;
    while(temp->next != NULL) //Instead of traversal condition, write NECESSARY CONDITION in loop to AVOID BREAK
    {
        temp = temp->next;
    }
    //The above traversal sends temp to the LAST NODE(handy when operations will happen at lAST NODE orr at SPECIFIED POSITION)
    Node* newNode = new Node(val);
    temp->next = newNode; //Now, a new node is created and the next node of current temp is assigned val
    return head;
}

Node* insertVal_my(Node* head, int pos, int val)
{
  if(head==NULL)
    {
        return head;
    } 
    Node* newNode = new Node(val);
    Node* temp = head;
    Node* prev = temp;
    int count=0;
    while(temp!=NULL)
    {
        count++;
        // if(count>length)
        // {
        //     cout<<"Count>length"<<endl;
        //     break;
        // }
        if(count==pos)
        {
           break;
        }
        prev = temp;
        temp= temp->next;
    }
    prev->next = newNode; //Now, a new node is created and the next node of current temp is assigned val
    newNode->next = temp;
    return head;
}


//TIME COMPLEXITY:
// BEST CASE(it is at head)- O(1)
//Worst Case(traversing entire LL): O(n)
Node* insertVal(Node* head, int pos, int val)
{
    //1st TEST CASE
  if(head==NULL) //EMPTY LL
    {
        if(pos==1)
        {
            return new Node(val); //Only for 1st position, a new node can be created and assigned as NEW HEAD
        }
        else{
            return head;
        }
    } 
    if(pos==1) //INSERTION AT HEAD
    {
        // Node* temp = new Node(val, head);
        // return temp;
        //REPLACE ABOVE TWO LINES WITH THE FOLLOWING LINE
        return new Node(val, head);
    }
    int count=0;
    Node* temp = head;
    while(temp!=NULL) //pos is valid from 1 to length+1
    {
        count++;
        if(count==(pos-1))
        {
            // Node* newNode = new Node(val);
            // newNode->next = temp->next;
            Node* newNode = new Node(val, temp->next); //newnode's 'next' is temp->next so in place of 'next' in constructor 1, newnode's 'next' can be substituted
            temp->next = newNode; /*temp's next is pointed to newNode so now, the connection is like : temp -> newNode -> (original temp)->next*/
            break;
        }
        temp = temp->next; //do not miss this, this is required to traverse the entire LL
    }
    return head;
}

Node* insertBefore(Node* head, int el, int val)
{
    //1st TEST CASE
  if(head==NULL) //EMPTY LL
    {
            return NULL;
    } 
    if(head->data==el) //INSERTION AT HEAD
    {
        // Node* temp = new Node(val, head);
        // return temp;
        //REPLACE ABOVE TWO LINES WITH THE FOLLOWING LINE
        return new Node(val, head);
    }
    Node* temp = head;
    //  Node* prev = NULL;
    // while(temp!=NULL)
     while(temp->next !=NULL) //Stopping at SECOND LAST element to fit the VAL there
    {
        if(temp->next->data==el)
        {
            Node* newNode = new Node(val, temp->next);
             //newnode's 'next' is temp->next so in place of 'next' in constructor 1, newnode's 'next' can be substituted
            // prev->next = newNode; 
            temp->next = newNode;
            /*temp's next is pointed to newNode so now, the connection is like : temp -> newNode -> (original temp)->next*/
            break;
        }
        // prev = temp;
        temp = temp->next; //do not miss this, this is required to traverse the entire LL
    }
    return head;
}

Node* insertAfter(Node* head, int el, int val)
{
    //1st TEST CASE
  if(head==NULL) //EMPTY LL
    {
            return NULL;
    } 
    if(head->data==el) //INSERTION AT HEAD
    {
        return new Node(val, head);
    }
    Node* temp = head;
    //  Node* prev = NULL;
    while(temp!=NULL) 
    {
        if(temp->data==el)
        {
            // Node* newNode = new Node(val);
            // newNode->next = temp->next;
            Node* newNode = new Node(val, temp->next); //newnode's 'next' is temp->next so in place of 'next' in constructor 1, newnode's 'next' can be substituted
            temp->next = newNode; /*temp's next is pointed to newNode so now, the connection is like : temp -> newNode -> (original temp)->next*/
            break;
        }
        temp = temp->next; //do not miss this, this is required to traverse the entire LL
    }
    return head;
}


int main()
{
    vector<int> arr = {2, 5, 8, 7};
    Node *head = convertArr2LL(arr);
    //DELETE HEAD
    // head = removesHead(head);
    // print(head);

    //DELETE TAIL
    // head = deleteTail(head);
    // print(head);

    //DELETE NODE BASED ON POSITION
    // head = deletePos(head, 3);
    // print(head);

    //DELETE NODE BASED ON VALUE
    // head = deleteVal(head, 5);
    // print(head);

    //INSERT NODE AT HEAD
    // head = insertHead(head,10);
    
    // head = new Node(100, head); //Technique to call constructor 1 and pass the data we want as NEW HEAD 
    //and communicating to it that we want the CURRENT HEAD to become the FUTURE NEXT NODE
    // print(head);

    //INSERT NODE AT TAIL
    // head = insertTail(head, 90);
    // print(head);

    //INSERT NODE AT POSITION K
    //  head = insertVal(head, 3,90);
    // print(head);

    // head = insertBefore(head, 7,90);
    // print(head);

    head = insertAfter(head, 7,90);
    print(head);
    return 0;
}