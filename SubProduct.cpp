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
// ----------- constructors ---------------
#include "SubProduct.h"


// ----------- constructors ---------------
#define DISCRETE_SELLING_MSG "Please enter number of items: "

#define CONTINUOUS_SELLING_MSG "Please enter desired quantity: "

// ----------- constructor ---------------

/**
 * @brief A constructor
 * @param serialNumber The Product's catalog number
 * @param productName The Product's name
 * @param productPrice The Product's price
 * @param productQuantity The product's quantity
 */
Discrete :: Discrete(int serialNumber, string productName, double productPrice, int productQuantity):
        Product(serialNumber, productName, productPrice, productQuantity) {}

/**
* @brief A constructor
* @param serialNumber The Product's catalog number
* @param productName The Product's name
* @param productPrice The Product's price
* @param productQuantity The product's quantity
*/
Continuous :: Continuous(int serialNumber, string productName, double productPrice, double productQuantity):
        Product(serialNumber, productName, productPrice, productQuantity){}

// ----------- methods ---------------

/**
 * @return The Product's quantity
 */
double Discrete :: getQuantity()
{
    return (int)_quantity;
}

/**
 * @brief This method updates the product's quantity in the stock
 * @param amount How much we add to the current quantity
 */
void Discrete :: setQuantity(double amount)
{
    _quantity += (int)amount;
}


string Discrete::getSellingMsg()
{
    return DISCRETE_SELLING_MSG;
};

double Continuous ::  getQuantity()
{
    return _quantity;
}
void Continuous :: setQuantity(double amount)
{
    _quantity += amount;
}

string Continuous::getSellingMsg()
{
    return CONTINUOUS_SELLING_MSG;
};




