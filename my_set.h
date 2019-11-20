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

#include <iostream>
#include "big_integer.h"

using namespace std;

/**
 * @brief This class is an implementation of the data structure "set". It has a nested class "Node", by which it holds
 * the elements of the set, and keep the sorted
 */
class my_set
{
private:
    /**
     * @brief This is my_set's nested class for keeping the elements
     */
    class Node
    {
    public:
        /**
 * @brief A constructor for the nested class "Node", by a given "big_integer" object
 * @param num The "big_integer" object
 */
        Node(const big_integer& newVal);

        // ------- nested class' fields ----------

        Node *next;
        Node *prev;
        big_integer val;

        /**
 * @brief The destructor for the nested class "Node"
 */
        ~Node();
    };

    // ------- fields ----------

    Node *head;

public:

    // -------------------------- constructors-------------------------

    /**
 * @brief The default constructor
 */
    my_set();
    /**
     * @brief A copy constructor
     * @param other The "my_set" object that we'd like to copy
     */
    my_set(const my_set& other);

    // -------------------------- Methods -------------------------

    /**
 * @brief This method looks for a number in the set. if it's not foundm it returns the element that would have been
 * before the given number in the set, if the given number had been in the set (which means the biggest element of the
 * set, that is smaller than the given number)
 * @param num The given number
 * @return The node that holds the same value of the given number iff it's in the set, a smaller node otherwise
 */
    Node* getNumOrSmaller(const big_integer &num) const;
    /**
 * @brief This method looks for a number in the set.
 * @param num The given number
 * @return true iff the number is in the set, false otherwise
 */
    bool is_in_set(const big_integer& num) const ;
    /**
 * @brief This method handles the case in which we try to add the first/ second element of the list. This method also
 * makes sure that the node isn't already in the set
 * @param newNode THe node we'd like to add
 * @return 1 iff the node was added successfully, 0 if the node was already on the set, 2 if it should be added to the
 * set, but it's not the first/ second element we try to add to this set
 */
    int handleNewList(Node *newNode);
    /**
 * This methods adds a number to the set, if it's not already in it
 * @param num The number we'd like to add to our set
 * @return true iff we added it successfully, false otherwise
 */
    bool add(const big_integer& num);
    /**
 * @brief This method removes a number from the set, if it's actually in it
 * @param num The number we'd like to remove from this set
 * @return true if it was removed successfully, false otherwise
 */
    bool remove(const big_integer& num);
    /**
 * @brief This method sums up all the elements in the set
 * @return The summary of all the elements in the set
 */
    big_integer sum_set();

    // -------------------------- operators -------------------------

    /**
 * @brief This method puts the data of a given my_set obecjt into "this" my_set object member wise
 * @param other The object we'd like to copy the data of
 * @return A reference to the created object
 */
    my_set &operator=(const my_set& other);
    /**
 * @brief This method defines the operation of subtraction a my_set object from another
 * @param other The my_set object that we subtract from "this" object
 * @return the result of the operation
 */
    my_set operator-(const my_set& other);
    /**
 * @brief This method defines the operation of uniting to sets' elements
 * @param other The my_set object that we'd like to unite with "this" object
 * @return the result of the operation
 */
    my_set operator|(const my_set& other);
    /**
 * @brief This method defines the operation of uniting to sets' elements
 * @param other The my_set object that we'd like to find the intersection of with our set
 * @return the result of the operation
 */
    my_set operator&(const my_set& other);
    /**
 * @brief This method enables the operation of printing a "my_set" to the screen using ostream
 * @param output The my object that we'd like to print
 * @param os The ostream.
 * @return The ostream object
 */
    friend ostream &operator<<(ostream &os, const my_set &output);
    /**
     * @brief The destructor
     */
    ~my_set();
};
