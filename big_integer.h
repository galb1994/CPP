
/**
* @file big_integer.cpp
* @author  Gal Batzia <gal.batzia@mail.huji.ac.il>
* @version 1.0
* @date 30 Aug 2018
*
* @brief  This class holds the implementation of the object "big_integer". A kind of type that can hold numbers that
* are as a long a string can get, which is longer then int.
*
* @section LICENSE
* This program is not a free software; bla bla bla...
*
* @section DESCRIPTION
* This class is responsible of the "big_integer"'s arithmetics (addition, multiplication, division...) and also it's
* printings to the screen.
* Input  : A number (by an int, a string or nothing)
* Process: The program analyzes the input's type and by that makes the number's "big_integer"'s presentation.
* Output : Any simple arithmetic action that the user wants to preform on the nubmer
*/

//
// Created by gal.batzia on 8/28/18.
//


#ifndef EX1_BIG_INTEGER_H
#define EX1_BIG_INTEGER_H




class big_integer
{
public:

    // -------------------------- constructors -------------------------
    /**
 * @brief The default constructor
 */
    big_integer();
    /**
 * @brief A copy constructor
 * @param other The big_integer object that we'd like to copy
 */
    big_integer(const big_integer &other);
    /**
 * @brief A constructor by a given int
 * @param num The int
 */
    big_integer(long int num);
    /**
 * @brief A constructor by a given matching string
 * @param str The string we'd like to put into the object
 */
    big_integer(std::string str);

    // -------------------------- operators -------------------------
    /**
     * @brief This method provides the option of assigning a "big_integer" object into another
     * @param other The object we'd like to assign into "this"
     * @return a reference to the copy
     */
    big_integer &operator=(const big_integer& other) = default;
    /**
 * @brief This method says if this object is bigger than the input
 * @param other The object we compare to
 * @return 1 iff this is bigger than other , 0 otherwise
 */
    bool operator>(const big_integer& other);
    /**
 * @brief This method says if this object is smaller than the input
 * @param other The object we compare to
 * @return 1 iff this is smaller than other , 0 otherwise
 */
    bool operator<(const big_integer& other);
    /**
 * @brief This method says if this object is bigger or equal than the input
 * @param other The object we compare to
 * @return 1 iff this is bigger or equal than other , 0 otherwise
 */
    bool operator>=(const big_integer& other);
    /**
 * @brief This method says if this object is smaller or equal than the input
 * @param other The object we compare to
 * @return 1 iff this is smaller or equal than other , 0 otherwise
 */
    bool operator<=(const big_integer& other);
    /**
 * @brief This method says if this object is equal to the input
 * @param other The object we compare to
 * @return 1 iff this equal than other , 0 otherwise
 */
    bool operator==(const big_integer& other);
    /**
 * @brief This method says if this object is not equal to the input
 * @param other The object we compare to
 * @return 1 iff this equal than other , 0 otherwise
 */
    bool operator!=(const big_integer &other);
    /**
 * @brief This method defines the operation of addition 2 "big_integers"
 * @param other The big_integer object that we add to this object
 * @return the result of the operation
 */
    big_integer operator+(const big_integer& other);
    /**
 * @brief This method defines the operation of +=, which isn't only just add, but also update "this" to be the result.
 * @param other The big_integer object that we add to this object
 * @return A reference to the result
 */
    big_integer& operator+=(const big_integer& other);
    /**
 * @brief This method defines the operation of subtraction 2 "big_integers"
 * @param other The big_integer object that we subtract from "this" object
 * @return the result of the operation
 */
    big_integer& operator-=(const big_integer &other);
    /**
 * @brief This method defines the operation of -=, which isn't only just subtract, but also update "this" to be the
 * result.
 * @param other The big_integer object that we subtract from "this" object
 * @return A reference to the result
 */
    big_integer operator-(const big_integer& other);
    /**
 * @brief This method defines the operation of multiplying a "big_integers" in another
 * @param other The big_integer object that we multiply "this" object by
 * @return the result of the operation
 */
    big_integer operator*(const big_integer& other);
    /**
 * @brief This method defines the operation of *=, which isn't only just multiplication, but also update "this" to be
 * the result.
 * @param other The big_integer object that we multiply "this" object by
 * @return A reference to the result
 */
    big_integer& operator*=(const big_integer& other);
    /**
 * @brief This method defines the operation of dividing a "big_integers" in another
 * @param other The big_integer object that we divide "this" object by
 * @return the result of the operation
 */
    big_integer operator/(const big_integer& other);
    /**
 * @brief This method defines the operation of /=, which isn't only just division, but also update "this" to be
 * the result.
 * @param other The big_integer object that we divide "this" object by
 * @return A reference to the result
 */
    big_integer& operator/=(const big_integer& other);
    /**
 * @brief This method defines the operation of module for "big_integers"
 * @param other The big_integer object that we take module of "this" object by
 * @return the result of the operation
 */
    big_integer operator%(const big_integer& other);
    /**
 * @brief This method enables the operation of printing a "big_integers" to the screen using ostream
 * @param output The big_integer object that we'd like to print
 * @param os The ostream.
 * @return The ostream object
 */
    friend std::ostream& operator<<(std::ostream& os, const big_integer& output);

private:

    // ------- fields ----------

    /**
     * @brief The number itself, unsigned
     */
    std::string _data;
    /**
     * @brief The string's length
     */
    size_t length;
    /**
     * @brief The number's sign
     */
    bool unNegative;


    // -------------------------- Methods -------------------------
    /**
 * @return The _data field
 */
    std::string getData();
    /**
 * @brief This method writes a given string backwards
 * @param str The string we'd like to write from the end to the beginning
 * @return The required string
 */
    std :: string reverseStr(std::string str);
    /**
 * @brief This method removes the zeroes from a "big_integer"'s _data field that aren't neccessary (like in "005", will
 * give back "5").
 * @param num The number we'd like to remove the zeros from.
 */
    void removeZeros(big_integer& num);
    /**
 * @brief This method sets which number is bigger, between 2 "big_integer" objects
 * @param other The number we'd like to compare to "this"
 * @return 1 iff "this" is bigger, -1 iff "other" is bigger, 0 otherwise
 */
    int compare(const big_integer& other);
    /**
 * This method compares 2 "big_integer" objects that have the same sign.
 * @param num1 The first number
 * @param num2 The second number
 * @return 1 iff num1 is bigger than num2, -1 iff num2 2 is bigger than num1, zero otherwise
 */
    int compareSameSign(big_integer num1, big_integer num2);
    /**
 * This method sums up 2 numbers. It counts on those who use it to put the number which is bigger in the first parament,
 * and the smaller one in the second parameter (it uses the numbers' lengths)
 * @param biggerNum The bigger number
 * @param smallerNum The smaller number
 * @return The summary
 */
    std::string sumBySize(const std::string &biggerNum, const std::string &smallerNum);
    /**
 * @brief This method uses the method "sumBySize" for summing 2 given numbers
 * @param num1 The first number
 * @param num2 The second number
 * @return The 2 numbers' summary
 */
    std::string sumNumbers(const big_integer& num1, const big_integer& num2);
    /**
 * @brief This method sums up 2 numbers which have opposite signs. It counts on those who use it to put the
 * positive number in the first arg, and the negative one in the second arg
 * @param pos The positive number
 * @param neg The negative number
 * @return The summary of the 2 numbers
 */
    std::string sumDifferentSigns(big_integer &pos, big_integer &neg);
    /**
 * @brief This method subtract 2 numbers which have opposite signs. It counts on those who use it to put the
 * number we subtract from in the first arg, and the number we subtract in the second arg
 * @param pos The umber we subtract from
 * @param neg The number we subtract
 * @return The subtraction of the 2 numbers
 */
    std::string subtractSameSigns(const big_integer &num1, const big_integer &num2);
    /**
 * This method subtract a number from another. It counts on those who use it to put the number which is bigger in the
 * first parameter, and the smaller one in the second parameter (it uses the numbers' lengths)
 * @param biggerNum The bigger number
 * @param smallerNum The smaller number
 * @return The subtraction
 */
    std::string subtractBySize(const std::string &biggerNum, const std::string &smallerNum);
    /**
 * @brief This method subtract a number from another, which has an opposite sign. It counts on those who use it to put
 * the positive number in the first arg, and the negative one in the second arg
 * @param pos The positive number
 * @param neg The negative number
 * @return The summary of the 2 numbers
 */
    std::string subtractDifferentSigns(big_integer& pos, big_integer& neg);
    /**
 * @brief this method multiplies a number by a digit, by summing it as the size of the digit
 * @param num The number we multiply
 * @param digit The number of summing that we do
 * @return The multiplication
 */
    big_integer multiplyByDigit(const big_integer& num, long digit);
    /**
 * @brief This method finds the smallest sub number (a number that is made from digits of a whole number, from it's beginning
 * to it's end. For example, like 153 out of 153,457) that is bigger than the divisor.
 * @param divided The whole number we'd like to divide
 * @param divisor The number we divide by
 * @return The required sub number
 */
    big_integer getFirst(const big_integer& divided, const big_integer &divisor);
    /**
 * @brief This method finds the number of times we need to multiply a number, until it's bigger than the other given num
 * @param num The number we'd like to surpass
 * @param divisor The number we multiply until it's big enough
 * @return The multiplication factor
 */
    big_integer getMultiplicationFactor(const big_integer &num, const big_integer &divisor);
    /**
 * @brief This method finds the next number we need to divide by the divisor in the algorithm of "long division"
 * @param remainder The number we got after the last subtracting during the "log division" algorithm
 * @param multipliedDivisor The divisor, multiplied by the last multiplication factor we found
 * @param nextDigit A pointer to the index of the next digit we should take from the whole divider and add it to
 * the remainder, as required in the algorithm. I needed to use a pointer because I wanted to keep track of the index
 * of the last digit that I "dropped".
 * @param curResult A pointer to the current state of the result. All the digits that we have collected so far in the
 * proccess. I needed to use a pointer because in the edge case of a few digits being added to curResult, its not
 * something I could have updated from outside of this method.
 * @return The next required remainder
 */
    big_integer differenciate(const big_integer& remainder, const big_integer &multipliedDivisor, int *nextDigit,
                              big_integer *curResult, big_integer divisor);
    /**
 * @brief returns the next digit that should be "dropped" from divider
 * @param remainder
 * @return
 */
    long findNextDigit(big_integer remainder);
};

#endif //EX1_BIG_INTEGER_H




