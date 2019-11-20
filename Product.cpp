/**
* @file Product.cpp
* @author  Gal Batzia <gal.batzia@mail.huji.ac.il>
* @version 1.0
* @date 12 September 2018
*
* @brief  This is an abstract class that represents a general item in a store
*
* @section LICENSE
* This program is not a free software; bla bla bla...
*
* @section DESCRIPTION
* This class defines the base fields of a product from any kind, including it's printing to the screen.
*/

// -------------------------- includes-------------------------
#include <iostream>
#include <iomanip>
#include "Product.h"
using std :: string;
using std :: cout;
using std :: endl;
using std :: ostream;

// ----------- constructors ---------------
/**
 * @brief A constructor
 * @param serialNumber The Product's catalog number
 * @param productName The Product's name
 * @param productPrice The Product's price
 * @param productQuantity The product's quantity
 */
Product :: Product(int serialNumber, string productName, double productPrice, double productQuantity):
        _serialNumber(serialNumber), _name(productName), _price(productPrice), _quantity(productQuantity){}

// -------------------------- methods -------------------------

/**
 * @return The Product's catalog number
 */
int &Product :: _getSerialNumber()
{
    return _serialNumber;
}

/**
 * @return The Product's name
 */
string Product :: getName() { return _name; }

/**
 * @brief This method prints this Product
 */
void Product::printObject()
{
    cout << "Item: " << _serialNumber << endl;
    cout << "Name: " << _name << endl;
    cout << "Quantity: " << _quantity << endl;
    cout << "Price: " << std :: setprecision(2) << std :: fixed << _price << endl;
}

