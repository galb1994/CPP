#ifndef EX2_IKEAEXCEPTIONS_H
#define EX2_IKEAEXCEPTIONS_H

#include <exception>
#include <iostream>

// ----------- defines ---------------

/**
 * @brief The string that is thrown as an exception for an invalid input, and that will eventually be printed to
 * the screen
 */
#define INVALID_INPUT_MSG "Invalid input file"
/**
 * @brief The string that is printed to the screen for getting the file's name, for getting the new stock
 */
#define ENTER_FILE_NAME_MSG "please enter file path: "
/**
 * @brief The string that is printed to the screen for getting the name of the product that the
 * user wants
 */
#define ENTER_NAME_MSG "please enter product name: "



// ----------- classes ---------------

class FileException: public std :: exception
{
public:
    virtual void printMsg(){};
};

/**
 * @brief The string that is thrown as an exception for an invalid input, and that will eventually be printed to
 * the screen
 */
class InvalidValueException: public FileException
{
public:
    /**
 * @brief The string that is thrown as an exception for an invalid input, and that will eventually be printed to
 * the screen
 */
    void printMsg() override
    {
        std :: cerr << "\nInvalid input." << std :: endl;
        std :: cout << std :: endl;
    }
};

/**
 * @brief The string that is thrown as an exception for a given catalog number that wasn't found in the stock,
 * and that will eventually be printed to
 * the screen
 */
class IllegalProductInFile: public FileException
{
public:
    /**
 * @brief The string that is thrown as an exception for an invalid input, and that will eventually be printed to
 * the screen
 */
    void printMsg() override
    {
        std :: cerr << "Illegal Product In File. Added only the products before. " << std :: endl;
        std :: cout << std :: endl;
    }
};

/**
 * @brief The string that is thrown as an exception for a given catalog number that wasn't found in the stock,
 * and that will eventually be printed to
 * the screen
 */
class NotValidException: public FileException
{
public:
    /**
 * @brief The string that is thrown as an exception for a given catalog number that wasn't found in the stock,
 * and that will eventually be printed to
 * the screen
 */
    void printMsg() override
    {
        std :: cerr << "\nNot valid input." << std :: endl;
        std :: cout << std :: endl;
    }
};

/**
 * @brief The string that is thrown as an exception for an invalid input (used in the case of the user chose "sell"),
 * and that will eventually be printed to the screen
 */
class BadPathException: public FileException
{
public:
    /**
 * @brief The string that is thrown as an exception for an invalid input (used in the case of the user chose "sell"),
 * and that will eventually be printed to the screen
 */
    void printMsg() override
    {
        std :: cerr << "Could not open file." << std :: endl;
        std :: cout << std :: endl;
    }
};

/**
 * @brief The string that is printed to the screen for getting the catalog number of the product that the
 * user wants
 */
class NotEnoughException: public FileException
{
public:
    /**
 * @brief The string that is printed to the screen for getting the catalog number of the product that the
 * user wants
 */
    void printMsg() override
    {
        std :: cerr << "\nNot enough stock to sell." << std :: endl;
        std :: cout << std :: endl;
    }
};

/**
 * @brief The string that is thrown as an exception for a given catalog number that wasn't found in the stock,
 * and that will eventually be printed to
 * the screen
 */
class ItemNotFoundException: public FileException
{
public:
    /**
 * @brief The string that is thrown as an exception for an invalid input, and that will eventually be printed to
 * the screen
 */
    void printMsg() override
    {
        std :: cerr << "\nItem not found" << std :: endl;
        std :: cout << std :: endl;
    }
};

/**
 * @brief The string that is printed to the screen for getting the file's name, for getting the new stock
 */
class NegativeQuantityException: public FileException
{

public:
    /**
 * @brief The string that is printed to the screen for getting the file's name, for getting the new stock
 */
    void printMsg() override
    {
        std :: cout << "Quantity is less than zero." << std :: endl;
    }
};

#endif //EX2_IKEAEXCEPTIONS_H
