/**
* @file SubTool.cpp
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

// ----------- includes ---------------
#include <iomanip>
#include "SubTool.h"

// ----------- constructors ---------------
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
KitchenWare::KitchenWare(int serialNumber, string productName, double productPrice, int productQuantity, double width,
                         double length, double height, double productCapacity): Tool(serialNumber, productName,
                         productPrice, productQuantity, width, length, height), _capacity(productCapacity){}

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
Furniture :: Furniture(int serialNumber, string productName, double productPrice, int productQuantity, double width,
                       double length, double height, string productColor, string productMaterial): Tool(serialNumber,
                        productName, productPrice, productQuantity, width, length, height), _color(productColor),
                        _material(productMaterial){}


// ----------- methods ---------------
/**
 * @brief Prints the product to the screen
 */
void KitchenWare::printObject()
{
    Tool :: printObject();
    cout << "Capacity: " << std::setprecision(2) << std :: fixed << _capacity << endl;
    cout << "-----" << endl;
}

/**
 * @brief Prints the product to the screen
 */
void Furniture :: printObject()
{
    Tool :: printObject();
    cout << "Material: " << _material << endl;
    cout << "Color: " << _color << endl;
    cout << "-----" << endl;
}