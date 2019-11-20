/**
* @file ikea.cpp
* @author  Gal Batzia <gal.batzia@mail.huji.ac.il>
* @version 1.0
* @date 12 September 2018
*
* @brief  This file is represents an Ikea store. It holds the class "Ikea" that has a vector holds all the store's
* products as a field. This program can add products, sort them by name or by serial number and also sell products
* from the stock.
* @section LICENSE
* This program is not a free software; bla bla bla...
* @input A user's choice from the menu.
* @proccess Updating the stock by the user's request
*/


#include <vector>
#include "FileReader.h"
#include "ikea.h"
#include <algorithm>

// ----------- defines ---------------
/**
 * @brief Tells that the user chose option 1 on the menu
 */
#define INPUT_STOCK 1
/**
 * @brief Tells that the user chose option 2 on the menu
 */
#define FIND_BY_ITEM_NUMBER 2
/**
 * @brief Tells that the user chose option 3 on the menu
 */
#define FIND_BY_ITEM_NAME 3
/**
 * @brief Tells that the user chose option 4 on the menu
 */
#define PRINT_BY_CAT_NUM 4
/**
 * @brief Tells that the user chose option 5 on the menu
 */
#define PRINT_BY_NAME 5
/**
 * @brief Tells that the user chose option 6 on the menu
 */
#define SELL_ITEM 6
/**
 * @brief Tells that the user chose option 7 on the menu
 */
#define EXIT 7
/**
 * @brief The string that is thrown as an exception for an invalid input, and that will eventually be printed to
 * the screen
 */
#define INVALID_INPUT_MSG "Invalid input file"
/**
 * @brief The string that is printed to the screen for getting the catalog number of the product that the
 * user wants
 */
#define ENTER_CATALOG_NUM_MESSAGE "please enter catalog number: "
/**
 * @brief The string that is printed to the screen for getting the file's name, for getting the new stock
 */
/**
 * @brief The string that is printed to the screen for getting the catalog number of the product that the
 * user wants
 */
#define ENTER_CATALOG_ID_MESSAGE "please enter catalog id: "
#define ENTER_FILE_NAME_MSG "please enter file path: "
/**
 * @brief The string that is printed to the screen for getting the name of the product that the
 * user wants
 */
#define ENTER_NAME_MSG "please enter product name: "

using std :: vector;
using std ::cin;
using std :: stringstream;
using std :: sort;

/**
 * @brief A struct that has a comperator method for sorting the products by catalog nubmer
 */
struct CompByCatalogNumStruct
{
    /**
     * @brief This method compares 2 Product pointers by their catalog number
     * @param p1 The first Product pointer
     * @param p2 The second Product pointer
     * @return true iff p1 is bigger than p2, false otherwise
     */
    bool operator()(Product *p1, Product *p2)
    {
        return p1->_getSerialNumber() < p2->_getSerialNumber();
    }
}CompByCatalogNumStruct;

/**
 * @brief A struct that has a comperator method for sorting the products by name
 */
struct CompByNameStruct
{
    /**
     * @brief This method compares 2 Product pointers by their names
     * @param p1 The first Product pointer
     * @param p2 The second Product pointer
     * @return true iff p1 is bigger than p2, false otherwise
     */
    bool operator()(Product *p1, Product *p2)
    {
        return p1->getName().compare(p2 -> getName()) < 0;
    }
}CompByNameStruct;

/**
 * @brief This method adds a product to the Products vector. If the Product wasn't already in the stock, we add a new
 * element to the vector, otherwise, we update the existing element's quantity
 * @param p The new Product
 */
void Ikea :: add(Product *p)
{
    int newSpotIndex = 0;
    bool foundSpotFlag = false;
    for(vector<Product *> :: iterator iter = this -> _catalog.begin(); iter != this -> _catalog.end(); ++iter)
    {
        if((*iter)->_getSerialNumber() == p->_getSerialNumber())
        {
            if((*iter) -> getName().compare(p -> getName()) == 0)
            {
                (*iter)->setQuantity(p->getQuantity()); // Updates the found product's _quantity
                return;
            }
            throw IllegalProductInFile();
        }
        if((*iter)->_getSerialNumber() > p->_getSerialNumber())
        {
            foundSpotFlag = true;
        }
        if(!foundSpotFlag)
        {
            newSpotIndex ++;
        }
    }
    if(foundSpotFlag) // Puts a new product in the place it belongs
    {
        this -> _catalog.insert(_catalog.begin() + newSpotIndex, p);
        return;
    }
    else
    {
        this -> _catalog.push_back(p);
    }
}

/**
 * @brief This method gets a file path that has new stock for the Ikea object. If the file is valid, it adds the new
 * Products to the stock
 * @throw In case of invalid file
 */
void Ikea :: handleStockInput()
{
    cout << ENTER_FILE_NAME_MSG << endl;
    string fileName;
    cin >> fileName;
    FileReader inputStock;
    inputStock.read(fileName);
    for(vector<Product *> :: iterator iter = inputStock.givenProducts.begin(); iter != inputStock.givenProducts.end();
        ++ iter)
    {
        add(*iter);
    }
}

/**
 * @brief This method gets the user's input when is asked for a number and checks if the input is valid
 * @tparam T The variable can be double of int, so I used template)
 * @param outputMsg The message that is printed to the screen and asks the user for what the program needs
 * @param userInput The variable that should store the user's input if its valid
 * @param ExpnMsg The Exception that the program would like to throw in the case of invalid input
 * @throw In case of invalid input
 */
template <class T> void Ikea :: handleUsersChoice(const string& outputMsg, T &userInput)
{
    cout << outputMsg;
    string input;
    cin.ignore();
    getline(cin, input);
    stringstream inputParser(input);
    if(!(inputParser >> userInput))
    {
        throw 0;
    }
}

/**
 * @brief This method asks the user to enter a catalog number of a product and prints it to the screen if it exists
 */
void Ikea :: findByNumber()
{
    int givenSerialNumber;
    try
    {
        handleUsersChoice(ENTER_CATALOG_ID_MESSAGE, givenSerialNumber);
    }
    catch(int a)
    {
        throw NotValidException();
    }
    for(vector<Product *> :: iterator iter = this -> _catalog.begin(); iter != this -> _catalog.end(); ++iter)
    {
        if((*iter)->_getSerialNumber() == givenSerialNumber)
        {
            (*iter) -> printObject();
            cout << endl;
            return;
        }
    }
    throw ItemNotFoundException();
}

/**
 * @brief This method asks the user to enter a name of a product and prints it to the screen if it exists
 */
void Ikea :: findByName()
{
    cout << ENTER_NAME_MSG;
    string givenName;
    cin.ignore();
    getline(cin, givenName);
    for(vector<Product *> :: iterator iter = this -> _catalog.begin(); iter != this -> _catalog.end(); ++iter)
    {
        if((*iter) -> getName().compare(givenName) == 0)
        {
            (*iter) -> printObject();
            cout << endl;
            return;
        }
    }
    throw ItemNotFoundException();
}

/**
 * @brief This method prints the catalog's Products by catalog number, from smallest to largest
 */
void Ikea :: printByCatalogNumber()
{
    sort(this -> _catalog.begin(), this -> _catalog.end(), CompByCatalogNumStruct);
    for(vector<Product *> :: iterator iter = this -> _catalog.begin(); iter != this -> _catalog.end(); ++ iter)
    {
        (*iter) -> printObject();
    }
    cout << endl;
}

/**
 * @brief This method prints the catalog's Products by their names, by the ABC, from first to last
 */
void Ikea :: printByName()
{
    sort(this -> _catalog.begin(), this -> _catalog.end(), CompByNameStruct);
    for(vector<Product *> :: iterator iter = this -> _catalog.begin(); iter != this -> _catalog.end(); ++ iter)
    {
        (*iter) -> printObject();
    }
    cout << endl;
}

/**
 * @brief This method sells an item
 */
void Ikea::sellItem()
{
    int itemCatalogNum;
    string input;
    try
    {
        handleUsersChoice(ENTER_CATALOG_NUM_MESSAGE, itemCatalogNum);
    }
    catch(int a)
    {
        throw NotValidException();
    }
    for(vector<Product *> :: iterator iter = this -> _catalog.begin(); iter != this -> _catalog.end(); ++ iter)
    {
        if((*iter)->_getSerialNumber() == itemCatalogNum)
        {
            cout << (*iter) -> getSellingMsg();
            getline(cin, input);
            stringstream inputParser(input);
            double amount;
            if(!(inputParser >> amount))
            {
                throw NotValidException();
            }
            if(amount > (*iter) -> getQuantity())
            {
                throw NotEnoughException();
            }
            if(amount < 0)
            {
                throw NegativeQuantityException();
            }
            (*iter) -> setQuantity(-amount);
            (*iter) -> printObject();
            return;
        }
    }
    throw ItemNotFoundException();
}

void Ikea :: printMenu()
{
    cout << "1. Input stock from file" << endl;
    cout << "2. Find item by catalog number" << endl;
    cout << "3. Find item by name" << endl;
    cout << "4. Print stock by catalog number" << endl;
    cout << "5. Print stock by name" << endl;
    cout << "6. Sell item" << endl;
    cout << "7. Exit" << endl;
}

/**
 * @brief A destructor
 */
Ikea::~Ikea()
{
    for(vector<Product *> :: iterator iter = this -> _catalog.begin(); iter != _catalog.end(); ++ iter)
    {
        delete(*iter);
    }
    _catalog.clear();
}

void manageMenu()
{
    bool runningFlag = true;
    string userInput;
    int userChoice;
    Ikea ik;
    while (runningFlag)
    {
        ik.printMenu();
        do
        {
            cin >> userInput;
        }
        while (std :: all_of(userInput.begin(), userInput.end(), isspace));
        stringstream inputParser(userInput);
        if (!(inputParser >> userChoice))
        {
            continue;
        }
        try
        {
            switch (userChoice)
            {
                case INPUT_STOCK:
                    ik.handleStockInput();
                    break;
                case FIND_BY_ITEM_NUMBER:
                    ik.findByNumber();
                    break;
                case FIND_BY_ITEM_NAME:
                    ik.findByName();
                    break;
                case PRINT_BY_CAT_NUM:
                    ik.printByCatalogNumber();
                    break;
                case PRINT_BY_NAME:
                    ik.printByName();
                    break;
                case SELL_ITEM:
                    ik.sellItem();
                    break;
                case EXIT:
                    runningFlag = false;
                    cout << endl;
                    break;
                default:
                    return;
            }
        }
        catch(FileException& exception)
        {
            exception.printMsg();
        }
    }
}

int main()
{
    manageMenu();
}


