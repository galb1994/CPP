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
#ifndef EX2_PRODUCT_H
#define EX2_PRODUCT_H

#include <iostream>

using std :: string;
using std :: cout;
using std :: endl;
using std :: ostream;

/**
 * @brief The abstract class "Product"
 */
class Product
{
public:

    // -------------------------- constructors --------------------

/**
* @brief A constructor
* @param serialNumber The Product's catalog number
* @param productName The Product's name
* @param productPrice The Product's price
* @param productQuantity The product's quantity
*/
Product(int serialNumber, string productName, double productPrice, double d);

    // -------------------------- methods -------------------------
/**
 * @return The Product's price
 */
double getPrice()
{
    return _price;
}

/**
 * @return The Product's catalog number
 */
int &_getSerialNumber();

/**
 * @return The Product's quantity
 */
virtual double getQuantity() = 0;

/**
 * @brief This method sets the Product's quantity in the stock
 * @param amount How much we add to this product's quantity
 */
virtual void setQuantity(double amount) = 0;

/**
 * @brief This method prints this Product
 */
virtual void printObject() = 0;

/**
 * @return The Product's name
 */
string getName();

/**
 * @return The message that is printed to the screen whenver the program sells some Discrete product, and ask for
 * the product's quantity
 */
virtual string getSellingMsg() = 0;

    // ---------- destructor ------------

/**
 * @brief The destructor
 */
virtual ~Product() = default;

protected:
    int _serialNumber;
    string _name;
    double _price;
    double _quantity;
};



#endif //EX2_PRODUCT_H
