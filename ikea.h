/**
* @file ikea.cpp
* @author  Gal Batzia <gal.batzia@mail.huji.ac.il>
* @version 1.0
* @date 12 September 2018
*
* @brief  This file is represents an Ikea store. It holds the class "Ikea" that has a vector holds all the store's
* products as a field. This program can add products, sort them by name or by serial number and also sell products
* from the stock.
* @section LICENSE
* This program is not a free software; bla bla bla...
* @input A user's choice from the menu.
* @proccess Updating the stock by the user's request
*/

#include <vector>
#include <string>
#include "FileReader.h"
#include "ikeaExceptions.h"

#ifndef EX2_IKEA_H
#define EX2_IKEA_H

using std :: vector;
using std :: cin;
using std :: string;

/**
 * @brief This class represents an "IKEA" store
 */
class Ikea
{
public:
    /**
     * A constructor
     */
    Ikea(): _catalog(){}

    /**
     * @brief This method adds a product to the Products vector. If the Product wasn't already in the stock, we add a new
     * element to the vector, otherwise, we update the existing element's quantity
     * @param p The new Product
     */
    void add(Product *p);

    /**
     * @brief This method gets a file path that has new stock for the Ikea object. If the file is valid, it adds the new
     * Products to the stock
     * @throw In case of invalid file
     */
    void handleStockInput();

    /**
     * @brief This method gets the user's input when is asked for a number and checks if the input is valid
     * @tparam T The variable can be double of int, so I used template)
     * @param outputMsg The message that is printed to the screen and asks the user for what the program needs
     * @param userInput The variable that should store the user's input if its valid
     * @param ExpnMsg The Exception that the program would like to throw in the case of invalid input
     * @throw In case of invalid input
     */
    template <class T> void handleUsersChoice(const string& outputMsg, T &userInput);

    /**
     * @brief This method asks the user to enter a catalog number of a product and prints it to the screen if it exists
     */
    void findByNumber();

    /**
     * @brief This method asks the user to enter a name of a product and prints it to the screen if it exists
     */
    void findByName();

    /**
     * @brief This method prints the catalog's Products by catalog number, from smallest to largest
     */
    void printByCatalogNumber();

    /**
     * @brief This method prints the catalog's Products by their names, by the ABC, from first to last
     */
    void printByName();

    /**
     * @brief This method sells an item
     */
    void sellItem();

    /**
     * @brief This method prints the catalog menu
     */
    void printMenu();

    /**
     * A destructor
     */
    ~Ikea();

private:
    vector<Product *> _catalog;
};

#endif //EX2_IKEA_H
