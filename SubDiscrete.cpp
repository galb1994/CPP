/**
* @file SubDiscrete.cpp
* @author  Gal Batzia <gal.batzia@mail.huji.ac.il>
* @version 1.0
* @date 12 September 2018
*
* @brief  This file holds classes that inherit from "Discrete", which means those objects' counting is discrete
*
* @section LICENSE
* This program is not a free software; bla bla bla...
*
*/

// ----------- includes ---------------
#include <iomanip>
#include "SubDiscrete.h"

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
*/
Tool :: Tool(int serialNumber, string productName, double productPrice, int productQuantity, double width,
             double length, double height): Discrete(serialNumber, productName, productPrice, productQuantity)
{
    _dimensions[0] = width;
    _dimensions[1] = length;
    _dimensions[2] = height;
}

/**
* @brief A constructor
* @param serialNumber The Product's catalog number
* @param productName The Product's name
* @param productPrice The Product's price
* @param productQuantity The product's quantity
* @param width The product's width
* @param productAuthor The product's autohr's name
* @param productYearOfPublication The product's year of publication
* @param productLength The product's length
*/
Entertainment :: Entertainment(int serialNumber, string productName, double productPrice, int productQuantity,
                               string productAuthor, int productYearOfPublication, int productLength):
        Discrete(serialNumber, productName, productPrice, productQuantity) , _author(productAuthor),
        _yearOfPublication(productYearOfPublication), _length(productLength){}


// ----------- methods ---------------

/**
 * @return The product's dimensions
 */
double *Tool :: getDimensions()
{
    return _dimensions;
}

/**
 * @brief Prints the product to the screen
 */
void Tool :: printObject()
{
    Discrete :: printObject();
    cout << "Dimensions: ";
    cout << std :: setprecision(2) << std :: fixed << _dimensions[0] << " " << std :: setprecision(2) << std :: fixed
         << _dimensions[1] << " " << std :: setprecision(2) << std :: fixed << _dimensions[2] << endl;
}

/**
 * @brief Prints the product to the screen
 */
void Entertainment :: printObject()
{
    Discrete :: printObject();
    cout << "Author: " << _author << endl;
    cout << "Year of publication: " << _yearOfPublication << endl;
    cout << "Length: " << _length << endl;
    cout << "-----" << endl;
}