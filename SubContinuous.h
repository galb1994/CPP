/**
* @file SubContinuous.h
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
#ifndef EX2_SUBCONTINUOUS_H
#define EX2_SUBCONTINUOUS_H

// ----------- includes ---------------
#include "SubProduct.h"

/**
 * @brief This class represents fabric Products
 */
class Fabric : public Continuous
{
public:

// ----------- includes ---------------

/**
* @brief A constructor
* @param serialNumber The Product's catalog number
* @param productName The Product's name
* @param productPrice The Product's price
* @param productQuantity The product's quantity
* @param productWeight The product's weight
*/
Fabric(int productSerialNumber, string productName, double productPrice, double productQuantity, double productWeight);

// ----------- methods ---------------
/**
 * @return The Product's weight
 */
double getWeight();

/**
 * @brief This method prints the Product
 */
void printObject() override;

// ----------- destructor ---------------

/**
 * @brief A destructor
 */
~Fabric() = default;

private:
    double _weight;
};

/**
 * @brief This class represents candy Products
 */
class Candy : public Continuous
{
public:

// ----------- includes ---------------

/**
* @brief A constructor
* @param serialNumber The Product's catalog number
* @param productName The Product's name
* @param productPrice The Product's price
* @param productQuantity The product's quantity
* @param productWeight The product's weight
*/
Candy(int productSerialNumber, string productName, double productPrice, double productQuantity, double productWeight);

// ----------- methods ---------------

/**
 * @return The Product's calories
 */
double getCalories();
void printObject() override;

// ----------- destructor---------------
/**
 * @brief The destructor
 */
~Candy() = default;

private:
    double _calories;
};


#endif //EX2_SUBCONTINUOUS_H
