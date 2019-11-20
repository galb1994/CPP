/**
* @file SubContinuous.cpp
* @author  Gal Batzia <gal.batzia@mail.huji.ac.il>
* @version 1.0
* @date 12 September 2018
*
* @brief  This file holds classes that inherit from "Continuous", which means those objects' counting is countinuous
*
* @section LICENSE
* This program is not a free software; bla bla bla...
*
*/

// ----------- includes ---------------
#include "SubContinuous.h"

// ----------- constructors ---------------

/**
* @brief A constructor
* @param serialNumber The Product's catalog number
* @param productName The Product's name
* @param productPrice The Product's price
* @param productQuantity The product's quantity
* @param productWeight The product's weight
*/
Fabric :: Fabric(int productSerialNumber, string productName, double productPrice, double productQuantity,
                 double productWeight) : Continuous(productSerialNumber, productName, productPrice, productQuantity),
                                         _weight(productWeight){}

/**
* @brief A constructor
* @param serialNumber The Product's catalog number
* @param productName The Product's name
* @param productPrice The Product's price
* @param productQuantity The product's quantity
* @param productWeight The product's weight
*/
Candy :: Candy(int productSerialNumber, string productName, double productPrice, double productQuantity,
               double productWeight) : Continuous(productSerialNumber, productName, productPrice, productQuantity),
                                       _calories(productWeight){}


// ----------- methods---------------
/**
 * @return The Product's weight
 */
double Fabric :: getWeight()
{
    return _weight;
}

/**
 * @brief This method prints the Product
 */
void Fabric :: printObject()
{
    Continuous :: printObject();
    cout << "Weight: " << _weight << endl;
    cout << "-----" << endl;
};

/**
 * @return The Product's calories
 */
double Candy :: getCalories()
{
    return _calories;
}

/**
 * @brief This method prints the Product
 */
void Candy :: printObject()
{
    Continuous :: printObject();
    cout << "Calories: " << _calories << endl;
    cout << "-----" << endl;
};
