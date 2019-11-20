/**
* @file SubDiscrete.h
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

#ifndef EX2_SUBDISCRETE_H
#define EX2_SUBDISCRETE_H

// ----------- includes ---------------
#include "SubProduct.h"

/**
 * @brief This class represents Products which are tools
 */
class Tool: public Discrete
{
public:
    // ----------- constructor --------------
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
Tool(int serialNumber, string productName, double productPrice, int productQuantity, double width, double length,
     double height);

// ----------- methods ---------------

/**
 * @return The product's dimensions
 */
double *getDimensions();
/**
 * @brief Prints the product to the screen
 */
void printObject() override;

// ----------- destructor ---------------
/**
 * A destructor
 */
~Tool() = default;
private:
    double _dimensions[3] = {0};
};

/**
 * @brief This class represents Products which are entertainments
 */
class Entertainment: public Discrete
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
* @param productAuthor The product's autohr's name
* @param productYearOfPublication The product's year of publication
* @param productLength The product's length
*/
Entertainment(int serialNumber, string productName, double productPrice, int productQuantity, string productAuthor,
              int productYearOfPublication, int productLength);

// ----------- methods ---------------
/**
 * @brief Prints the product to the screen
 */
void printObject() override;

// ----------- destructor ---------------
/**
 * @brief A destructor
 */
~Entertainment() = default;

private:
    string _author;
    int _yearOfPublication;
    int _length;
};

#endif //EX2_SUBDISCRETE_H
