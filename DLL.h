#ifndef DLL_H
#define DLL_H
#include <iostream>
using namespace std;
template<typename t>
struct Node
{
public:
    t data;
    Node* next;
    Node* prev;
    Node(const t& data ) : data(data), next(nullptr), prev(nullptr) {}
};
template<typename t>
class DLL // Double Linked List
{
private:
    Node<t>* head;
    Node<t>* tail;
    size_t size;

public:
    DLL() : head(nullptr), size(0),tail(nullptr) {}
    ~DLL ()
    {
        clear();
    }
    Node <t>* gethead() const
    {
        return head;
    }
    Node <t>* gettail() const
    {
        return tail;
    }

    // Insert at beginning
    void insertAtBeg(const t& data)
    {
        Node<t>* newnode = new Node(data);
        if (head != nullptr)
        {
            head->prev = newnode;
        }
        newnode->next = head;
        head = newnode;
        size++;
    }

    // Insert at end
    void insertAtEnd(const t& data) //add
    {
        Node<t>* newnode = new Node(data);
        if (head == nullptr)
        {
            head = newnode;
        }
        else
        {
            Node<t>* temp = head;
            while (temp->next != nullptr)
            {
                temp = temp->next;
            }
            temp->next = newnode;
            newnode->prev = temp;
        }
        size++;
    }

    // Insert at specific position
    void insertAtGivenPos(const t& data, int pos)
    {
        if (pos == 1)
        {
            insertAtBeg(data);
        }
        else
        {
            Node<t>* newnode = new Node(data);
            Node<t>* temp = head;
            for (size_t i = 1; i < pos - 1 && temp != nullptr; i++)
            {
                temp = temp->next;
            }
            if (temp == nullptr)
            {
                cout << "Out of range" << endl;
            }
            else
            {
                newnode->next = temp->next;
                if (temp->next != nullptr)
                {
                    temp->next->prev = newnode;
                }
                temp->next = newnode;
                newnode->prev = temp;
                size++;
            }
        }
    }

    // Delete at beginning
    void deleteAtBeg()
    {
        if (head == nullptr)
        {
            cout << "List is empty!" << endl;
            return;
        }
        Node<t>* temp = head;
        head = head->next;
        if (head != nullptr)
        {
            head->prev = nullptr;
        }
        delete temp;
        size--;
    }

    // Delete at end
    void deleteAtEnd()
    {
        if (head == nullptr)
        {
            cout << "List is empty!" << endl;
            return;
        }
        if (head->next == nullptr)
        {
            delete head;
            head = nullptr;
        }
        else
        {
            Node<t>* temp = head;
            while (temp->next != nullptr)
            {
                temp = temp->next;
            }
            temp->prev->next = nullptr;
            delete temp;
        }
        size--;
    }


    void deleteAtSpecificPos(int pos)
    {
        if (pos < 1)
        {
            cout << "Invalid position" << endl;
            return;
        }
        if (head == nullptr)
        {
            cout << "List is empty!" << endl;
            return;
        }
        if (pos == 1)
        {
            deleteAtBeg();
        }
        else
        {
            Node<t>* temp = head;
            for (size_t i = 1; i < pos && temp != nullptr; i++)
            {
                temp = temp->next;
            }
            if (temp == nullptr)
            {
                cout << "Out of boundary" << endl;
            }
            else
            {
                if (temp->next != nullptr)
                {
                    temp->next->prev = temp->prev;
                }
                if (temp->prev != nullptr)
                {
                    temp->prev->next = temp->next;
                }
                delete temp;
                size--;
            }
        }
    }




    bool search(const t& value) const
    {
        Node<t>* current = head;
        while (current)
        {
            if (current->data == value)
            {
                return true;
            }
            current = current->next;
        }
        return false;
    }


    size_t getSize() const
    {
        return size;
    }
    Node<t>* getHead() const
    {
        return head;
    }



    Node<t>* getNodeAt(int position)
    {
        if (position < 1 || position > getSize())
        {
            return nullptr; // إذا كانت الموضع غير صحيح
        }

        Node<t>* current = head;
        int index = 1;
        while (current != nullptr && index < position)
        {
            current = current->next;
            index++;
        }

        return current;  // إرجاع العقدة في الموضع المحدد
    }
    void traverse() const
    {
        Node<t>* current = head;
        while (current)
        {
            cout << current->data << endl;
            current = current->next;
        }
        cout << endl;
    }
    void clear()
    {
        Node<t>* current = head;
        while (current != nullptr)
        {
            Node<t>* temp = current->next;
            delete current;
            current = temp;
        }
        head =tail= nullptr;
        size = 0;
    }

};
#endif

