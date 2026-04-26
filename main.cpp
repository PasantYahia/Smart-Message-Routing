#include <iostream>
#include <string>
#include <limits>
using namespace std;
struct Message
{
    int id;
    string text;
    int priority;
};
struct Node
{
    Message msg;
    Node *next;
};
struct StackNode
{
    Message msg;
    StackNode *next;
};
Node *front = NULL;
StackNode *top = NULL;
void Enqueue(int id, string text, int priority);
void Display();
void deleteSpecific(int id);
void searchById(int id);
bool isIdExist(int id);
int Peek();
void PushToStack(Message m);
void Dequeue();
void updateById(int id);
void topOfStack();
int main()
{
    system("start index.html");
    int choice, id, priority;
    string text;
    while (true)
    {
        cout << "\n=============================" << endl;
        cout << " SMART MESSAGE ROUTING SYSTEM " << endl;
        cout << "=============================" << endl;
        cout << "1. Add New Message (Enqueue)" << endl;
        cout << "2. Display All Pending Message" << endl;
        cout << "3. Search For A Message By Id" << endl;
        cout << "4. Update Message Data" << endl;
        cout << "5. Delete Specific Message" << endl;
        cout << "6. Send Message (Dequeue)" << endl;
        cout << "7. View Last Sent Message" << endl;
        cout << "8. Peek Next Message" << endl;
        cout << "9. Exist System" << endl;
        cout << "=============================" << endl;
        cout << "Enter Your Choice: ";
        cin >> choice;
        if (choice == 9)
        {
            cout << "Exiting System...GoodBye!" << endl;
            while (front != NULL)
            {
                Node *temp;
                temp = front;
                front = front->next;
                delete temp;
            }
            while (top != NULL)
            {
                StackNode *temp = top;
                top = top->next;
                delete temp;
            }
            break;
        }
        switch (choice)
        {
        case 1:
            cout << "Enter Message Id:" << endl;
            cin >> id;
            if (isIdExist(id))
            {
                cout << "[!] This Id Already Exists. Try Another One.\n";
                break;
            }
            cout << "Enter Priority (1-High , 3-Low): " << endl;
            cin >> priority;
            if (priority < 1 || priority > 3)
            {
                cout << "[!] Invalid Priority";
                break;
            }
            cout << "Enter Message Concept: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, text);
            Enqueue(id, text, priority);
            break;
        case 2:
            Display();
            break;
        case 3:
            cout << "Enter Id To Find: " << endl;
            cin >> id;
            searchById(id);
            break;
        case 4:
            cout << "Enter Id To Update: " << endl;
            cin >> id;
            updateById(id);
            break;
        case 5:
            cout << "Enter Id To Delete" << endl;
            cin >> id;
            deleteSpecific(id);
            break;
        case 6:
            Dequeue();
            break;
        case 7:
            topOfStack();
            break;
        case 8:
            Peek();
            break;
        default:
            cout << "[!] Invalid Choice . Try again" << endl;
        }
    }

    return 0;
}
// Add A New Message To The Queue Based On Priority (1 Is Highest)
void Enqueue(int id, string text, int priority)
{
    Node *new_node;
    new_node = new Node;
    new_node->msg.id = id;
    new_node->msg.text = text;
    new_node->msg.priority = priority;
    new_node->next = NULL;
    if (front == NULL)
    {
        front = new_node;
        new_node->next = NULL;
    }
    else if (priority < front->msg.priority)
    {
        new_node->next = front;
        front = new_node;
    }
    else
    {
        Node *temp;
        temp = front;

        while (temp->next != NULL && temp->next->msg.priority <= priority)
        {
            temp = temp->next;
        }
        new_node->next = temp->next;
        temp->next = new_node;
    }
}

void Display()
{
    Node *current;
    current = front;
    if (front == NULL)
    {
        cout << "\n\t [!] ATTENTION: The System Is Currently Empty--" << endl;
        return;
    }
    cout << "\n --Current Message In System--" << endl;
    cout << " ID    |   Priority    |Content " << endl;
    cout << " ----------------------------------------" << endl;
    while (current != NULL)
    {
        cout << " " << current->msg.id << "    |   "
             << current->msg.priority << "    |   "
             << current->msg.text << endl;
        current = current->next;
        cout << " ====================================" << endl;
    }
}
void searchById(int id)
{
    Node *current;
    current = front;
    if (front == NULL)
    {
        cout << "\n --System Is Empty-- " << endl;
        return;
    }
    while (current != NULL && current->msg.id != id)
    {
        current = current->next;
    }
    if (current == NULL)
    {
        cout << "\n [!] Message With Id: " << id << " was not found" << endl;
    }
    else
    {
        cout << "\n>>>[Success] Message Found <<<" << endl;
        cout << "-------------------------------" << endl;
        cout << ">ID: " << current->msg.id << endl;
        cout << ">Priority: " << current->msg.priority << endl;
        cout << ">Content: " << current->msg.text << endl;
    }
}
bool isIdExist(int id)
{
    Node *temp = front;
    while (temp != NULL)
    {
        if (temp->msg.id == id)
        {
            return true;
        }
        temp = temp->next;
    }
    return false;
}
// Return The Id Of The Front Message Without Deleting It
int Peek()
{
    if (front == NULL)
    {
        cout << "\n -- No Message in System --" << endl;
        return -1;
    }
    cout << "\n ----------------------------" << endl;
    cout << " -- Next Message In Process --" << endl;
    cout << "ID: " << front->msg.id << endl;
    cout << "Priority: " << front->msg.priority << endl;
    cout << "Content: " << front->msg.text << endl;
    cout << "----------------------------" << endl;
    return front->msg.id;
}
// Removes And Deleting The Message At The Front (Highest Priority)
void Dequeue()
{
    if (front == NULL)
    {
        cout << "\n -- No Message in System --" << endl;
        return;
    }
    Node *temp;
    temp = front;
    PushToStack(temp->msg);
    front = front->next;
    cout << "[-]Processing And Deleting Message " << temp->msg.id << endl;
    delete (temp);
    cout << "Success! Next Message is Now At The Front." << endl;
}
void deleteSpecific(int id)
{
    if (front == NULL)
    {
        return;
    }
    if (front->msg.id == id)
    {
        Node *temp = front;
        front = front->next;
        delete (temp);
        cout << "\n[V] Message " << id << " Deleted Successfully." << endl;
        return;
    }
    Node *temp;
    temp = front;
    while (temp->next != NULL && temp->next->msg.id != id)
    {
        temp = temp->next;
    }
    if (temp->next != NULL)
    {
        Node *nodeToDelete = temp->next;
        temp->next = nodeToDelete->next;
        delete (nodeToDelete);
        cout << "\n[V] Message " << id << "Deleted Successfully.";
    }
    else
    {
        cout << "\n[!]Message Not Found." << endl;
    }
}
/* Updates A Message By Deleting The Old One And Re-inserting it
This Ensures The System Remains Sorted By Priority */

void updateById(int id)
{
    Node *temp;
    temp = front;
    while (temp != NULL && temp->msg.id != id)
    {
        temp = temp->next;
    }
    if (temp == NULL)
    {
        cout << "\n[!] Message With Id: " << id << " Not Found To Update" << endl;
        return;
    }
    string newText;
    int newPriority;
    cout << "---Updating Message " << id << "---" << endl;
    cout << "Enter Your New Content: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, newText);
    cout << "Enter New Priority:";
    cin >> newPriority;
    if (newPriority < 1 || newPriority > 3)
    {
        cout << "[!] Invalid Priority. Update Cancelled." << endl;
        return;
    }
    deleteSpecific(id);
    Enqueue(id, newText, newPriority);
    cout << "\n [V] Message Updated And Re-order Successfully!!" << endl;
}
// Function To Archive Sent Message Into The Stack
void PushToStack(Message m)
{
    StackNode *new_node;
    new_node = new StackNode;
    new_node->msg = m;
    new_node->next = top;
    top = new_node;
}
// Function To View The Last Message That Was Successsfully Sent
void topOfStack()
{
    if (top == NULL)
    {
        cout << "\n [!] No Message Sent Yet " << endl;
        return;
    }
    cout << "\n -- Last Message Sent -- " << endl;
    cout << "ID: " << top->msg.id << endl;
    cout << "Content: " << top->msg.text << endl;
    cout << "---------------------------------" << endl;
}