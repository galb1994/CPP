/**
* @file FileReader.cpp
* @author  Gal Batzia <gal.batzia@mail.huji.ac.il>
* @version 1.0
* @date 12 September 2018
*
* @brief  This file is responsible of parsing a given file, checking it's validity and return the data it read from the
* file
* @section LICENSE
* This program is not a free software; bla bla bla...
* @input A file's path
* @proccess Going over the file, looking for mistakes in it and collects all the info until that point (if exists)
* @output The data from the file in a case of success
*/

// ----------- includes ---------------
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "SubContinuous.h"
#include "SubTool.h"

using std :: vector;

#ifndef EX2_FILEPARSER_H
#define EX2_FILEPARSER_H

/**
 * @brief This class parses a given stock file's data, checks it's validity and produces a vector with all the new
 * products from the given file
 */
class FileReader
{
public:
    /**
     * @brief A constructor
     */
    FileReader() = default;

    // ----------- fields ---------------

    vector<Product *> givenProducts;

    // ----------- methods---------------

    /**
* @brief This method read the given file and parses the data from it
* @param fileName The file's path.
* @throw In case of a value's invalidity
*/
    void read(const string &fileName);

private:
    /**
    * @brief This method cheks if the format of the file is as required (it does not check the file's values' validity)
    * @param givenCategories The fields' categories (like: "Item", "Calories" and so on)
    * @return A number that indicates to which format the given file matches, zero for no such format
    */
    int _checkMatchingToFormats(const vector<string> &givenCategories);
    /**
    * @brief This methods checks wether the given "basic values" a Product has (catalog number, name, quantity and price)
    * are valid.
    * @tparam T The type of the field "quantity", which can be either "int" or "double"
    * @param givenValues A vector of strings that holds the collected values from the file for this specific product
    * @param itemRef A reference to the item variable. Being updated
    * @param nameRef A reference to the name variable. Being updated
    * @param priceRef A reference to the price variable. Being updated
    * @param quantityRef A reference to the quantity variable. Being updated
    * @throw In case of a field's invalidity
    */
    template<typename T>
    void
     _checkProductBasicValues(const vector<string> &givenValues, int &itemRef, string &nameRef, double &priceRef,
                              T &quantityRef);
    /**
    * @brief This method checks if the given values match to the required values for a "Fabric" object
    * @param givenValues The given values
    * @return A "Fabric" object in case of success
    * @throw In case of a value's invalidity
    */
    Fabric *_checkFabricValues(const vector<string> &givenValues);
    /**
    * @brief This method checks if the given values match to the required values for a "Candy" object
    * @param givenValues The given values
    * @return A "Candy" object in case of success
    * @throw In case of a value's invalidity
    */
    Candy * _checkCandyValues(const vector<string> &givenValues);
    /**
    * @brief  This methods checks wether the given "basic tool values" a Tool Product (from the file) has are valid.
    * @param givenValues The given values
    * @param width The tool's eidth
    * @param length The tool's length
    * @param height The tool'd height
    * @throw In case of a value's invalidity
    */
    void _checkToolBasicValues(const vector<string> &givenValues, double &widthRef, double &lengthRef,
                               double &heightRef);
    /**
    * @brief This method checks if the given values match to the required values for a "Kitchenware" object
    * @param givenValues The given values
    * @return A "Kitchenware" object in case of success
    * @throw In case of a value's invalidity
    */
    KitchenWare *_checkKitchenwareValues(const vector<string> &givenValues);
    /**
    * @brief This method checks if the given values match to the required values for a "Furniture" object
    * @param givenValues The given values
    * @return A "Furniture" object in case of success
    * @throw In case of a value's invalidity
    */
    Furniture *_checkFurnitureValues(const vector<string> &givenValues);
    /**
    * @brief This method checks if the given values match to the required values for a "Entertainment" object
    * @param givenValues The given values
    * @return A "Entertainment" object in case of success
    * @throw In case of a value's invalidity
    */
    Entertainment *_checkEntertainmentValues(const vector<string> &givenValues);
};

#endif //EX2_FILEPARSER_H
