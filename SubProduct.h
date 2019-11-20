/**
* @file SubProduct.cpp
* @author  Gal Batzia <gal.batzia@mail.huji.ac.il>
* @version 1.0
* @date 12 September 2018
*
* @brief  This has two abstract classes that represent the to type of legal "Product" objects: Discrete and Continuous
*
* @section LICENSE
* This program is not a free software; bla bla bla...
*
*/

#ifndef EX2_SUBPRODUCT_H
#define EX2_SUBPRODUCT_H

// ----------- constructors ---------------
#include <iomanip>
#include "Product.h"
/**
 * @brief This class represents Products that they're counting is "Discrete", like a book or a chair
 */
class Discrete: public Product
{
public:

// ----------- constructor ---------------

/**
 * @brief A constructor
 * @param serialNumber The Product's catalog number
 * @param productName The Product's name
 * @param productPrice The Product's price
 * @param productQuantity The product's quantity
 */
Discrete(int serialNumber, string productName, double productPrice, int productQuantity);

// ----------- methods ---------------

/**
 * @return The Product's quantity
 */
double getQuantity() override;

/**
 * @brief This method updates the product's quantity in the stock
 * @param amount How much we add to the current quantity
 */
void setQuantity(double amount) override;

/**
 * @return The message that is printed to the screen whenver the program sells some Discrete product, and ask for
 * the product's quantity
 */
string getSellingMsg() override;

/**
* @brief This method prints this Product
*/
void printObject() override
{
    cout << "Item: " << _serialNumber << endl;
    cout << "Name: " << _name << endl;
    cout << "Quantity: " << (int)_quantity << endl;
    cout << "Price: " << std :: setprecision(2) << std :: fixed << _price << endl;
}

// ----------- destructor ---------------

/**
 * @brief The destructor
 */
~Discrete() = default;
};

/**
 * @brief This class represents Products that they're counting is "Continuous", like fabric or candy (buying by weight)
 */
class Continuous: public Product
{
public:

// ----------- constructors ---------------

/**
 * @brief A constructor
 * @param serialNumber The Product's catalog number
 * @param productName The Product's name
 * @param productPrice The Product's price
 * @param productQuantity The product's quantity
 */
Continuous(int serialNumber, string productName, double productPrice, double productQuantity);

// ----------- methods ---------------

/**
 * @return The Product's quantity
 */
double getQuantity() override;

/**
 * @brief This method updates the product's quantity in the stock
 * @param amount How much we add to the current quantity
 */
void setQuantity(double amount) override;

/**
 * @return The message that is printed to the screen whenver the program sells some Discrete product, and ask for
 * the product's quantity
 */
string getSellingMsg() override;

/**
 * @brief This method prints this Product
 */
void printObject() override
{
    cout << "Item: " << _serialNumber << endl;
    cout << "Name: " << _name << endl;
    cout << "Quantity: " << std :: setprecision(2) << std :: fixed << _quantity << endl;
    cout << "Price: " << std :: setprecision(2) << std :: fixed << _price << endl;
}

// ----------- constructors ---------------

/**
 * @brief The destructor
 */
~Continuous() = default;
};


#endif //EX2_SUBPRODUCT_H
