/**
* @file my_set.cpp
* @author  Gal Batzia <gal.batzia@mail.huji.ac.il>
* @version 1.0
* @date 30 Aug 2018
*
* @brief  This class holds the implementation of the object "my_set", which is a "set" data structure.
* The set's implementation is done by creating a nested class "Node", that has a field to hold the data, and a field for
* holding the next node (LinkedList). In this way, the set is also sorted.
* @section LICENSE
* This program is not a free software; bla bla bla...
*
* @section DESCRIPTION
* This class is enables the sets' arithmetics (union, subtraction, intersection...) and also it's
* printings to the screen.
* Input  : Numbers to be in the set
* Process: The program converts the number into a "big_integer" object, thats how it keeps it's data, and puts it in
* the matching spot for the set to be sorted even after an adding/removing a node.
* Output : Any simple arithmetic action that the user wants to preform on the set.
*/

// -------------------------- includes -------------------------

#include "my_set.h"
#include <iostream>

using std :: ostream;
using std :: cout;
using std :: endl;

// -------------------------- constructors -------------------------

/**
 * @brief A constructor for the nested class "Node", by a given "big_integer" object
 * @param num The "big_integer" object
 */
my_set :: Node :: Node(const big_integer& newVal): next(nullptr), prev(nullptr), val(newVal){}

/**
 * @brief The destructor for the nested class "Node"
 */
my_set::Node::~Node() = default;

/**
 * @brief The default constructor
 */
my_set :: my_set(): head(nullptr){};

/**
 * @brief A copy constructor
 * @param other The "my_set" object that we'd like to copy
 */
my_set :: my_set(const my_set &other)
{
    if(other.head == nullptr)
    {
        this -> head = nullptr;
        return;
    }
    Node *otherPtr = other.head;
    Node *thisHead = new Node(other.head->val);
    Node *thisPtr = thisHead;
    otherPtr = otherPtr -> next;
    while(otherPtr != nullptr)
    {
        thisPtr->next = new Node(otherPtr->val);
        otherPtr = otherPtr -> next;
        thisPtr = thisPtr -> next;
    }
    this->head = thisHead;
}

/**
 * @brief The destructor
 */
my_set::~my_set()
{
    if(head != nullptr)
    {
        Node *temp = head;
//        Node *next;
        while(temp != nullptr)
        {
            Node * next = temp -> next;
            delete(temp);
            temp = next;
        }
    }

}

// -------------------------- methods -------------------------
/**
 * @brief This method looks for a number in the set. if it's not foundm it returns the element that would have been
 * before the given number in the set, if the given number had been in the set (which means the biggest element of the
 * set, that is smaller than the given number)
 * @param num The given number
 * @return The node that holds the same value of the given number iff it's in the set, a smaller node otherwise
 */
my_set :: Node *my_set :: getNumOrSmaller(const big_integer &num) const
{
    Node *temp = this -> head;
    if((big_integer)num < head -> val)
    {
        return nullptr;
    }
    while(temp -> next != nullptr && temp -> next -> val <= num)
    {
        if(temp -> val == num)
        {
            return temp;
        }
        temp = temp -> next;
    }
    return temp;
}

/**
 * @brief This method looks for a number in the set.
 * @param num The given number
 * @return true iff the number is in the set, false otherwise
 */
bool my_set :: is_in_set(const big_integer& num) const
{
    Node *foundNode = getNumOrSmaller(num);
    if(foundNode == nullptr)
    {
        return false;
    }
    return (bool)(foundNode -> val == num);
}

/**
 * @brief This method handles the case in which we try to add the first/ second element of the list. This method also
 * makes sure that the node isn't already in the set
 * @param newNode THe node we'd like to add
 * @return 1 iff the node was added successfully, 0 if the node was already on the set, 2 if it should be added to the
 * set, but it's not the first/ second element we try to add to this set
 */
int my_set :: handleNewList(Node *newNode)
{
    if(head == nullptr) //Adding first node
    {
        head = newNode;
        return 1;
    }
    if(is_in_set(newNode -> val)) //The node is already in the set
    {
        delete(newNode);
        return 0;
    }
    if(head -> next == nullptr) //Adding second node
    {
        if(head -> val > newNode -> val)
        {
            head -> prev = newNode;
            newNode -> next = head;
            head = newNode;
        }
        else
        {
            head -> next = newNode;
            newNode->prev = head;
        }
        return 1;
    }
    return 2;
}

/**
 * This methods adds a number to the set, if it's not already in it
 * @param num The number we'd like to add to our set
 * @return true iff we added it successfully, false otherwise
 */
bool my_set :: add(const big_integer& num)
{
    Node *newNode = new Node(num);
    int newListFlag = handleNewList(newNode);
    if(!newListFlag) // Already in the set
    {
        delete(newNode);
        return false;
    }
    if(newListFlag == 1) // The node was added as the first or second element of the set
    {
        delete(newNode);
        return true;
    }
    Node *numOrSmaller = getNumOrSmaller(num);
    if(numOrSmaller != nullptr && numOrSmaller->val == num)
    {
        delete(newNode);
        return false;
    }
    if(numOrSmaller == nullptr) // Smaller then head
    {
        newNode -> next = head;
        head -> prev = newNode;
        head = newNode;
        return true;
    }
    if(numOrSmaller -> next != nullptr)// Adding a node after "numOrSmaller"
    {
        numOrSmaller -> next -> prev = newNode;
        newNode -> next = numOrSmaller -> next;
        newNode -> prev = numOrSmaller;
        numOrSmaller -> next = newNode;
    }
    if(numOrSmaller -> next == nullptr) //Adding a new tail
    {
        numOrSmaller -> next = newNode;
        newNode -> prev = numOrSmaller;
    }
    return true;
}

/**
 * @brief This method removes a number from the set, if it's actually in it
 * @param num The number we'd like to remove from this set
 * @return true if it was removed successfully, false otherwise
 */
bool my_set::remove(const big_integer &num)
{
    Node *foundNode = getNumOrSmaller(num);
    if (foundNode == nullptr || !(foundNode->val == num)) //The number isn't in the set
    {
        delete(foundNode);
        return false;
    }
    if(foundNode == head)
    {
        head = foundNode->next;
        foundNode->prev = nullptr;
        delete(foundNode);
        return true;
    }
    if(foundNode -> next != nullptr)
    {
        foundNode -> next -> prev = foundNode -> prev;
    }
    foundNode -> prev -> next = foundNode -> next;
    delete(foundNode);
    return true;
}

/**
 * @brief This method sums up all the elements in the set
 * @return The summary of all the elements in the set
 */
big_integer my_set::sum_set()
{
    Node *temp = head;
    big_integer sum;
    while(temp != nullptr)
    {
        sum += temp -> val;
        temp = temp -> next;
    }
    return sum;
}

// -------------------------- operators -------------------------

/**
 * @brief This method puts the data of a given my_set obecjt into "this" my_set object member wise
 * @param other The object we'd like to copy the data of
 * @return A reference to the created object
 */
my_set &my_set::operator=(const my_set &other)
{
    if(&other == this)
    {
        return *this;
    }
    delete(this->head);
    Node *otherPtr = other.head;
    Node *thisHead = new Node(other.head->val);
    Node *thisPtr = thisHead;
    otherPtr = otherPtr -> next;
    while(otherPtr != nullptr)
    {
        thisPtr->next = new Node(otherPtr->val);
        otherPtr = otherPtr -> next;
        thisPtr = thisPtr -> next;
    }
    this->head = thisHead;
    return *this;
}

/**
 * @brief This method defines the operation of subtraction a my_set object from another
 * @param other The my_set object that we subtract from "this" object
 * @return the result of the operation
 */
my_set my_set::operator-(const my_set& other)
{
    if(other.head == nullptr || this -> head == nullptr) // Empty set
    {
        return *this;
    }
    my_set diffSet;
    Node *temp = this -> head;
    while(temp != nullptr)
    {
        if(!other.is_in_set(temp -> val))
        {
            diffSet.add(temp -> val);
        }
        temp = temp -> next;
    }
    return diffSet;
}

/**
 * @brief This method defines the operation of uniting to sets' elements
 * @param other The my_set object that we'd like to unite with "this" object
 * @return the result of the operation
 */
my_set my_set::operator|(const my_set& other)
{
    my_set unionSet(*this);
    Node *tempOther = other.head;
    while(tempOther != nullptr)
    {
        unionSet.add(tempOther -> val);
        tempOther = tempOther -> next;
    }
    return unionSet;
}

/**
 * @brief This method defines the operation of uniting to sets' elements
 * @param other The my_set object that we'd like to find the intersection of with our set
 * @return the result of the operation
 */
my_set my_set::operator&(const my_set& other)
{
    my_set intersectionSet(*this-(*this-other));
    return intersectionSet;
}

/**
 * @brief This method enables the operation of printing a "my_set" to the screen using ostream
 * @param output The my object that we'd like to print
 * @param os The ostream.
 * @return The ostream object
 */
ostream& operator <<(ostream &os, const my_set &output)
{
    auto *temp = output.head;
    if(temp == nullptr)
    {
        os << endl;
    }
    else
    {
        big_integer curVal;
        while (temp != nullptr)
        {
            curVal = temp->val;
            temp = temp->next;
            os << curVal << endl;
        }
    }
    return os;
}



