/**
* @file SubTool.h
* @author  Gal Batzia <gal.batzia@mail.huji.ac.il>
* @version 1.0
* @date 12 September 2018
*
* @brief  This file holds classes represents Products which are tools
*
* @section LICENSE
* This program is not a free software; bla bla bla...
*
*/
#ifndef EX2_SUBTOOLS_H
#define EX2_SUBTOOLS_H

// ----------- includes ---------------
#include "SubDiscrete.h"

/**
 * @brief This class represents Products which are kitchen tools
 */
class KitchenWare: public Tool
{
public:
// ----------- constructor ---------------
/**
* @brief A constructor
* @param serialNumber The Product's catalog number
* @param productName The Product's name
* @param productPrice The Product's price
* @param productQuantity The product's quantity
* @param width The product's width
* @param length The product's length
* @param height The product's height
* @param productCapacity The product's capacity
*/
KitchenWare(int serialNumber, string productName, double productPrice, int productQuantity, double width,
            double length, double height, double productCapacity);

// ----------- methods ---------------
/**
 * @brief Prints the product to the screen
 */
void printObject() override;

// ----------- destructor ---------------
/**
 * A destructor
 */
~KitchenWare() = default;

private:
    double _capacity;

};

/**
 * @brief This class represents Products which are furnitures
 */
class Furniture: public Tool
{
public:

// ----------- constructor ---------------

/**
* @brief A constructor
* @param serialNumber The Product's catalog number
* @param productName The Product's name
* @param productPrice The Product's price
* @param productQuantity The product's quantity
* @param width The product's width
* @param length The product's length
* @param height The product's height
* @param productCapacity The product's capacity
*/
Furniture(int serialNumber, string productName, double productPrice, int productQuantity, double width,
          double length, double height, string productColor, string productMaterial);

// ----------- methods ---------------
/**
 * @brief Prints the product to the screen
 */
void printObject() override;

// ----------- destructor ---------------
/**
 * A destructor
 */
~Furniture() = default;

private:
    string _color;
    string _material;
};


#endif //EX2_SUBTOOLS_H
