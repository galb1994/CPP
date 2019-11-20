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
#include "FileReader.h"
#include "ikeaExceptions.h"

// ----------- defines ---------------
/**
 * @brief Tells us that the given categories list matches the required format of a "Fabric" object
 */
#define MATCHES_FABRIC_FORMAT 1
/**
 * @brief Tells us that the given categories list matches the required format of a "Candy" object
 */
#define MATCHES_CANDY_FORMAT 2
/**
 * @brief Tells us that the given categories list matches the required format of a "Kitchenware" object
 */
#define MATCHES_KITCHENWARE_FORMAT 3
/**
 * @brief Tells us that the given categories list matches the required format of a "Furniture" object
 */
#define MATCHES_FURNITURE_FORMAT 4
/**
 * @brief Tells us that the given categories list matches the required format of a "Entertainment" object
 */
#define MATCHES_ENTERTAINMENT_FORMAT 5
/**
 * @brief Tells us that the given categories list doesn't match any format
 */
#define MATCHES_NOTHING 0
/**
 * @brief The string that is thrown as an exception for an invalid input, and that will eventually be printed to
 * the screen
 */

using std :: ifstream;
using std :: string;
using std :: cout;
using std :: cin;
using std :: endl;
using std :: stringstream;
using std :: vector;

// ----------- static instances ---------------
/**
 * @brief The required format of a "Fabric" object
 */
static vector<string> validFabricFormat = {"Item:", "Name:", "Quantity:", "Price:", "Weight:"};
/**
 * @brief The required format of a "Candy" object
 */
static vector<string> validCandyFormat = {"Item:", "Name:", "Quantity:", "Price:", "Calories:"};
/**
 * @brief The required format of a "Kitchenware" object
 */
static vector<string> validKitchenwareFormat = {"Item:", "Name:", "Quantity:", "Price:", "Dimensions:", "Capacity:"};
/**
 * @brief The required format of a "Furniture" object
 */
static vector<string> validFurnitureFormat = {"Item:", "Name:", "Quantity:", "Price:", "Dimensions:", "Material:",
                                              "Color:"};
/**
 * @brief The required format of a "Entertainment" object
 */
static vector<string> validEntertainmentFormat = {"Item:", "Name:", "Quantity:", "Price:", "Author:",
                                                  "Year of publication:", "Length:"};

// ----------- methods ---------------

/**
 * @brief This method cheks if the format of the file is as required (it does not check the file's values' validity)
 * @param givenCategories The fields' categories (like: "Item", "Calories" and so on)
 * @return A number that indicates to which format the given file matches, zero for no such format
 */
int FileReader :: _checkMatchingToFormats(const vector<string> &givenCategories)
{
    if (givenCategories == validFabricFormat)
    {
        return MATCHES_FABRIC_FORMAT;
    }
    if (givenCategories == validCandyFormat)
    {
        return MATCHES_CANDY_FORMAT;
    }
    if (givenCategories == validKitchenwareFormat)
    {
        return MATCHES_KITCHENWARE_FORMAT;
    }
    if (givenCategories == validFurnitureFormat)
    {
        return MATCHES_FURNITURE_FORMAT;
    }
    if (givenCategories == validEntertainmentFormat)
    {
        return MATCHES_ENTERTAINMENT_FORMAT;
    }
    return MATCHES_NOTHING;
}

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
FileReader :: _checkProductBasicValues(const vector<string> &givenValues, int &itemRef, string &nameRef,
                                       double &priceRef, T &quantityRef)
{
    stringstream lineParser(givenValues[0]);
    if (!(lineParser >> itemRef) || itemRef < 0)
    {
        throw InvalidValueException();
    }
    nameRef = givenValues[1];
    lineParser = stringstream(givenValues[2]);
    if (!(lineParser >> quantityRef))
    {
        throw InvalidValueException();
    }
    double price = 0;
    lineParser = stringstream(givenValues[3]);
    if (!(lineParser >> priceRef) || price < 0)
    {
        throw InvalidValueException();
    }
}

/**
 * @brief This method checks if the given values match to the required values for a "Fabric" object
 * @param givenValues The given values
 * @return A "Fabric" object in case of success
 * @throw In case of a value's invalidity
 */
Fabric * FileReader :: _checkFabricValues(const vector<string> &givenValues)
{
    int item;
    string name;
    double quantity, price;
    _checkProductBasicValues(givenValues, item, name, price, quantity);
    int weight;
    stringstream lineParser(givenValues[4]);
    if (!(lineParser >> weight) || weight <= 0)
    {
        throw InvalidValueException();
    }
    return new Fabric(item, name, price, quantity, weight);
}

/**
 * @brief This method checks if the given values match to the required values for a "Candy" object
 * @param givenValues The given values
 * @return A "Candy" object in case of success
 * @throw In case of a value's invalidity
 */
Candy * FileReader :: _checkCandyValues(const vector<string> &givenValues)
{
    int item;
    string name;
    double quantity, price;
    _checkProductBasicValues(givenValues, item, name, price, quantity);
    int calories;
    stringstream lineParser(givenValues[4]);
    if (!(lineParser >> calories) || calories <= 0)
    {
        throw InvalidValueException();
    }
    return new Candy(item, name, price, quantity, calories);
}

/**
 * @brief  This methods checks wether the given "basic tool values" a Tool Product (from the file) has are valid.
 * @param givenValues The given values
 * @param width The tool's eidth
 * @param length The tool's length
 * @param height The tool'd height
 * @throw In case of a value's invalidity
 */
void FileReader :: _checkToolBasicValues(const vector<string> &givenValues, double &widthRef, double &lengthRef,
                                         double &heightRef)
{
    stringstream lineParser(givenValues[4]);
    if (!(lineParser >> widthRef) || widthRef <= 0)
    {
        throw InvalidValueException();
    }
    if (!(lineParser >> lengthRef) || lengthRef <= 0)
    {
        throw InvalidValueException();
    }
    if (!(lineParser >> heightRef) || heightRef <= 0)
    {
        throw InvalidValueException();
    }
    string leftOver;
    lineParser >> leftOver;
    if(leftOver.compare("") != 0)
    {
        throw InvalidValueException();
    }
}

/**
 * @brief This method checks if the given values match to the required values for a "Kitchenware" object
 * @param givenValues The given values
 * @return A "Kitchenware" object in case of success
 * @throw In case of a value's invalidity
 */
KitchenWare * FileReader :: _checkKitchenwareValues(const vector<string> &givenValues)
{
    int item, quantity;
    string name;
    double price;
    _checkProductBasicValues(givenValues, item, name, price, quantity);
    double width, length, height;
    _checkToolBasicValues(givenValues, width, length, height);
    double capacity;
    stringstream lineParser(givenValues[7]);
    if (lineParser >> capacity || capacity <= 0)
    {
        throw InvalidValueException();
    }
    return new KitchenWare(item, name, price, quantity, width, length, height, capacity);
}

/**
 * @brief This method checks if the given values match to the required values for a "Furniture" object
 * @param givenValues The given values
 * @return A "Furniture" object in case of success
 * @throw In case of a value's invalidity
 */
Furniture * FileReader :: _checkFurnitureValues(const vector<string> &givenValues)
{
    int item, quantity;
    string name;
    double price;
    _checkProductBasicValues(givenValues, item, name, price, quantity);
    double width, length, height;
    _checkToolBasicValues(givenValues, width, length, height);
    stringstream lineParser(givenValues[5]);
    string material, color;
    lineParser >> material;
    lineParser = stringstream(givenValues[6]);
    lineParser >> color;
    return new Furniture(item, name, price, quantity, width, length, height, color, material);
}

/**
 * @brief This method checks if the given values match to the required values for a "Entertainment" object
 * @param givenValues The given values
 * @return A "Entertainment" object in case of success
 * @throw In case of a value's invalidity
 */
Entertainment * FileReader :: _checkEntertainmentValues(const vector<string> &givenValues)
{
    int item, quantity;
    string name;
    double price;
    _checkProductBasicValues(givenValues, item, name, price, quantity);
    string author = givenValues[4];
    int yearOfPublication;
    stringstream lineParser(givenValues[5]);
    if(!(lineParser >> yearOfPublication))
    {
        throw InvalidValueException();
    }
    int length;
    lineParser = stringstream(givenValues[6]);
    if(!(lineParser >> length) || length <= 0)
    {
        throw InvalidValueException();
    }
    return new Entertainment(item, name, price, quantity, author, yearOfPublication, length);
}

/**
 * @brief This method read the given file and parses the data from it
 * @param fileName The file's path.
 * @throw In case of a value's invalidity
 */
void FileReader :: read(const string &fileName)
{
    ifstream readFile(fileName);
    if(!readFile.is_open())
    {
        throw BadPathException();
    }
    bool eofFlag = false;
    string curLine;
    while (getline(readFile, curLine) && !eofFlag && curLine.compare("") != 0)
    {
        vector<string> categories;
        vector<string> values;
        string curCategory, curValue;
        while (curLine.compare("-----") != 0) // reading each product
        {
            size_t categoryEndingIndex = curLine.find(':');
            curCategory = curLine.substr(0, categoryEndingIndex + 1);
            curValue = curLine.substr(categoryEndingIndex + 2, curLine.length() - 1);
            categories.push_back(curCategory);
            values.push_back(curValue);
            if (!getline(readFile, curLine))
            {
                eofFlag = true;
                break;
            }
        }
        Product *curProd;
        switch (_checkMatchingToFormats(categories)) // If matches some format, tried to create a Product object out of
                                                    // the values
        {
            case MATCHES_FABRIC_FORMAT:
                curProd = _checkFabricValues(values);
                break;
            case MATCHES_CANDY_FORMAT:
                curProd = _checkCandyValues(values);
                break;
            case MATCHES_KITCHENWARE_FORMAT:
                curProd = _checkKitchenwareValues(values);
                break;
            case MATCHES_FURNITURE_FORMAT:
                curProd = _checkFurnitureValues(values);
                break;
            case MATCHES_ENTERTAINMENT_FORMAT:
                curProd = _checkEntertainmentValues(values);
                break;
            default:
                cout << INVALID_INPUT_MSG << endl;
                return;
        }
        givenProducts.push_back(curProd);
    }
    readFile.close();
}



