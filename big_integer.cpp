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
// -------------------------- includes-------------------------
#include <string>
#include <cstring>
#include <iostream>
#include "big_integer.h"

// -------------------------- defines -------------------------
/**
* @def DIGIT_LOWER_BOUND 48
* @brief The lowest value a number can get by ascii value. */
#define DIGIT_LOWER_BOUND 48

/**
* @def DIGIT_UPPER_BOUND 57
* @brief The highest value a number can get by ascii value. */
#define DIGIT_UPPER_BOUND 57

/**
* @def INT_TO_CHAR_CONVERTER 48
* @brief The number we need to subtract from an int in order to convert it to a char that presents the smae number
* in ascii value. */
#define INT_TO_CHAR_CONVERTER 48

using namespace std;

// -------------------------- constructors -------------------------

/**
 * @brief The default constructor
 */
big_integer :: big_integer(): _data("0"), length(1), unNegative(true){}

/**
 * @brief A copy constructor
 * @param other The big_integer object that we'd like to copy
 */
big_integer::big_integer(const big_integer &other) : _data(other._data), length(_data.length()),
                                           unNegative(other.unNegative) {}
/**
 * @brief A constructor by a given int
 * @param num The int
 */
big_integer::big_integer(long int num) : _data(reverseStr(to_string(num))), length(_data.length()), unNegative(num >= 0)
{

    if(!unNegative)
    {
        _data = _data.substr(0, length - 1);
    }
    length = _data.length();
    removeZeros(*this);

}

/**
 * @brief A constructor by a given matching string
 * @param str The string we'd like to put into the object
 */
big_integer::big_integer(string str): _data(reverseStr(str)), length(_data.length()), unNegative(str[0] != '-')
{
    if(_data.compare("0") == 0)
    {
        length = 1;
        unNegative = true;
        return;
    }
    if(((int)_data[0] < DIGIT_LOWER_BOUND || DIGIT_UPPER_BOUND < (int)str[0]) && _data[0] != '-')
    {
        _data = '0';
        return;
    }
    for (long i = 0; i <(long) length - 1; i++)
    {
        if((int)_data[i] < DIGIT_LOWER_BOUND || DIGIT_UPPER_BOUND < (int)str[i])
        {
            _data = '0';
            return;
        }
    }
    if(!unNegative)
    {
        _data = _data.substr(0, length - 1);
    }
    length = _data.length();
    if(*this != 0)
    {
        removeZeros(*this);
    }
}

// -------------------------- Methods -------------------------

/**
 * @return The _data field
 */
string big_integer::getData(){ return _data; }

/**
 * @brief This method writes a given string backwards
 * @param str The string we'd like to write from the end to the beginning
 * @return The required string
 */
std::string big_integer :: reverseStr(std::string str)
{
    if(str == "0")
    {
        return str;
    }
    std::string newStr{};
    for(int i = 0; i < (int)str.length(); ++i)
    {
        newStr += '0';
    }
    long j = 0;
    bool allZeroFlag = true;
    for(long i = (long)str.length() - 1; i >= 0; i --)
    {
        newStr[j] = str[i];
        if(newStr[j] != '0' && newStr[j] != '-')
        {
            allZeroFlag = false;
        }
        j ++;

    }
    if(allZeroFlag)
    {
        newStr = "0";
    }
    return newStr;
}

/**
 * @brief This method sets which number is bigger, between 2 "big_integer" objects
 * @param other The number we'd like to compare to "this"
 * @return 1 iff "this" is bigger, -1 iff "other" is bigger, 0 otherwise
 */
int big_integer::compare(const big_integer &other)
{

    if((this->unNegative &&  other.unNegative) ||
       (!this->unNegative &&  !other.unNegative))
    {
        return compareSameSign(*this, other);
    }
    if(this->unNegative)
    {
        return 1;
    }
    else
    {
        return -1;
    }
}

/**
 * @brief This method removes the zeroes from a "big_integer"'s _data field that aren't neccessary (like in "005", will
 * give back "5").
 * @param num The number we'd like to remove the zeros from.
 */
void big_integer::removeZeros(big_integer &num)
{
    size_t i = num.length - 1;
    while(num._data[i] == '0' && i != 0)
    {
        i --;
    }
    num._data = num._data.substr(0, i + 1);
}

/**
 * This method compares 2 "big_integer" objects that have the same sign.
 * @param num1 The first number
 * @param num2 The second number
 * @return 1 iff num1 is bigger than num2, -1 iff num2 2 is bigger than num1, zero otherwise
 */
int big_integer::compareSameSign(big_integer num1, big_integer num2)
{
    long thisLen = (long)num1.length, otherLen = (long)num2.length;

    if(thisLen > otherLen)
    {
        return 1;
    }
    if(thisLen < otherLen)
    {
        return -1;
    }
    for(long i = thisLen; i >= 0; i --)
    {
        if(num1._data[i] > num2._data[i])
        {
            return 1;
        }
        if(num1._data[i] < num2._data[i])
        {
            return -1;
        }
    }
    return 0; // Equal
}

/**
 * This method sums up 2 numbers. It counts on those who use it to put the number which is bigger in the first parament,
 * and the smaller one in the second parameter (it uses the numbers' lengths)
 * @param biggerNum The bigger number
 * @param smallerNum The smaller number
 * @return The summary
 */
string big_integer::sumBySize(const string &biggerNum, const string &smallerNum)
{
    string sum{};
    for (long k = 0; k < (long)biggerNum.length() + 1; ++k)
    {
        sum += '0';
    }
    int j = 0;
    for (char i : smallerNum)
    {
        sum[j] +=  ((int)biggerNum[j] - INT_TO_CHAR_CONVERTER) + ((int) i - INT_TO_CHAR_CONVERTER);
        if(sum[j] - INT_TO_CHAR_CONVERTER >= 10)
        {
            sum[j]  -= 10;
            sum[j + 1] += 1;
        }
        j ++;
    }
    while(j < (int)biggerNum.length())// Puts the rest of the numbers in "sum"
    {
        sum[j] += (int)biggerNum[j] - INT_TO_CHAR_CONVERTER;
        if(sum[j] - INT_TO_CHAR_CONVERTER >= 10)
        {
            sum[j]  -= 10;
            sum[j + 1] += 1;
        }
        j ++;
    }
    if(sum[sum.length() - 1] == '0')
    {
        return sum.substr(0, sum.length() - 1);
    }
    return sum;
}

/**
 * @brief This method uses the method "sumBySize" for summing 2 given numbers
 * @param num1 The first number
 * @param num2 The second number
 * @return The 2 numbers' summary
 */
string big_integer::sumNumbers(const big_integer &num1, const big_integer &num2)
{
    if(compareSameSign(num1, num2) == 1)
    {
        return sumBySize(num1._data, num2._data);
    }
    else
    {
        return sumBySize(num2._data, num1._data);
    }
}

/**
 * @brief This method sums up 2 numbers which have opposite signs. It counts on those who use it to put the
 * positive number in the first arg, and the negative one in the second arg
 * @param pos The positive number
 * @param neg The negative number
 * @return The summary of the 2 numbers
 */
string big_integer::sumDifferentSigns(big_integer &pos, big_integer &neg)
{
    if(compareSameSign(pos, neg) == 1) // Checks which number is bigger by absolute value
    {
       return subtractBySize(pos._data, neg._data);
    }
    string result = subtractBySize(neg._data, pos._data);
    if(result == "0")
    {
        return result;
    }
    return result + "-";
}

/**
 * @brief This method subtract 2 numbers which have opposite signs. It counts on those who use it to put the
 * number we subtract from in the first arg, and the number we subtract in the second arg
 * @param pos The umber we subtract from
 * @param neg The number we subtract
 * @return The subtraction of the 2 numbers
 */
string big_integer::subtractSameSigns(const big_integer &num1, const big_integer &num2)
{
    if(compareSameSign(num1, num2) == 1)
    {
        if(!num1.unNegative) // Like: -10-(-9)
        {
            return subtractBySize(num1._data, num2._data) + "-";
        }
        return subtractBySize(num1._data, num2._data);
    }
    if(num1.unNegative) // Like: 1-2
    {
        return subtractBySize(num2._data, num1._data) + "-";
    }
    return subtractBySize(num2._data, num1._data);  // Like: 9-(-10)
}

/**
 * This method subtract a number from another. It counts on those who use it to put the number which is bigger in the
 * first parameter, and the smaller one in the second parameter (it uses the numbers' lengths)
 * @param biggerNum The bigger number
 * @param smallerNum The smaller number
 * @return The subtraction
 */
string big_integer::subtractBySize(const string &biggerNum, const string &smallerNum)
{
    string subtract(biggerNum.length(), '0');
    int j = 0;
    for (char i : smallerNum)
    {
        subtract[j] +=  ((int)biggerNum[j] - INT_TO_CHAR_CONVERTER) - ((int) i - INT_TO_CHAR_CONVERTER);
        if(subtract[j] - INT_TO_CHAR_CONVERTER < 0)
        {
            subtract[j]  += 10;
            subtract[j + 1] -= 1;
        }
        j ++;
    }
    while(j < (int)biggerNum.length()) // Puts the rest of the numbers in "subtract"
    {
        subtract[j] += (int)biggerNum[j] - INT_TO_CHAR_CONVERTER;
        if(subtract[j] - INT_TO_CHAR_CONVERTER < 0)
        {
            subtract[j]  += 10;
            subtract[j + 1] -= 1;
        }
        j ++;
    }
    if(subtract[subtract.length() - 1] == '0' && subtract != "0")
    {
        return subtract.substr(0, subtract.length() - 1);
    }
    return subtract;
}

/**
 * @brief This method subtract a number from another, which has an opposite sign. It counts on those who use it to put
 * the positive number in the first arg, and the negative one in the second arg
 * @param pos The positive number
 * @param neg The negative number
 * @return The summary of the 2 numbers
 */
string big_integer::subtractDifferentSigns(big_integer &pos, big_integer &neg)
{
    string result;
    if(pos.length >= neg.length)// Like: 7 -(-5)
    {
        result = sumBySize(pos.getData(), neg.getData()); // pos is longer
    }
    else
    {
        result = sumBySize(neg.getData(), pos.getData()); // pos is shorter
    }
    if(result == "0")
    {
        return result;
    }
    return  result;
}

/**
 * @brief this method multiplies a number by a digit, by summing it as the size of the digit
 * @param num The number we multiply
 * @param digit The number of summing that we do
 * @return The multiplication
 */
big_integer big_integer::multiplyByDigit(const big_integer &num, long digit)
{
    big_integer sum(0);
    for(long i = 0; i < digit; i ++)
    {
        sum += num;
    }
    return sum;
}

/**
 * @brief This method finds the smallest sub number (a number that is made from digits of a whole number, from it's beginning
 * to it's end. For example, like 153 out of 153,457) that is bigger than the divisor.
 * @param divided The whole number we'd like to divide
 * @param divisor The number we divide by
 * @return The required sub number
 */
big_integer big_integer::getFirst(const big_integer &divided, const big_integer &divisor)
{
    long long index = divided.length - 1;
    big_integer subNum;
    subNum._data = divided._data[index];
    while(subNum < divisor && *this != subNum)
    {
        if(divided.length == 2)
        {
            subNum._data = divided._data.substr(index, divided.length);
        }
        else
        {
            if(index == -1)
            {
                subNum._data = this -> _data;
                subNum.length = this -> length;
                break;
            }
            subNum._data = divided._data.substr(index, divided.length - 1);
        }
        index--;
    }
    return subNum;
}

/**
 * @brief This method finds the number of times we need to multiply a number, until it's bigger than the other given num
 * @param num The number we'd like to surpass
 * @param divisor The number we multiply until it's big enough
 * @return The multiplication factor
 */
big_integer big_integer::getMultiplicationFactor(const big_integer &num, const big_integer &divisor)
{
    big_integer sum;
    int factor = 0;
    while((sum + divisor) <= num)
    {
        sum += divisor;
        factor ++;
    }
    return big_integer(factor);
}

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
big_integer big_integer::differenciate(const big_integer &remainder, const big_integer &multipliedDivisor,
                                       int *nextDigit, big_integer *curResult, big_integer divisor)
{
    big_integer diff = (big_integer)remainder - (big_integer)multipliedDivisor;
    if(remainder._data == this -> _data)
    {
        return diff;
    }
    while(diff < divisor && *nextDigit >= 0) //change 1: divisor instead of multi..
    {
        char droppedDigit = this -> _data[*nextDigit]; // The digit that we should add to diff
        diff._data = droppedDigit + diff._data;
        diff.length ++;
        (*nextDigit) --;
        (*curResult) *= 10;
        removeZeros(diff);
    }
    return diff;
}

/**
 * @brief returns the next digit that should be "dropped" from divider
 * @param remainder
 * @return
 */
long big_integer::findNextDigit(big_integer remainder)
{
    long j = (long)remainder.length - 1;
    for(long i = (long)this -> length - 1; i >= 0 ; i--)
    {
        if(remainder._data[j] != this -> _data[i])
        {
            return i;
        }
        j --;
    }
    return -1;
}

// -------------------------- operators -------------------------

/**
 * @brief This method says if this object is bigger than the input
 * @param other The object we compare to
 * @return 1 iff this is bigger than other , 0 otherwise
 */
bool big_integer::operator>(const big_integer &other)
{
    int result = compare(other);
    return !(result == 0 || result == -1);
}

/**
 * @brief This method says if this object is smaller than the input
 * @param other The object we compare to
 * @return 1 iff this is smaller than other , 0 otherwise
 */
bool big_integer::operator<(const big_integer &other)
{
    int result = compare(other);
    return !(result == 0 || result == 1);
}

/**
 * @brief This method says if this object is bigger or equal than the input
 * @param other The object we compare to
 * @return 1 iff this is bigger or equal than other , 0 otherwise
 */
bool big_integer::operator>=(const big_integer &other)
{
    int result = compare(other);
    return result == 0 || result == 1;
}

/**
 * @brief This method says if this object is smaller or equal than the input
 * @param other The object we compare to
 * @return 1 iff this is smaller or equal than other , 0 otherwise
 */
bool big_integer::operator<=(const big_integer &other)
{
    int result = compare(other);
    return result == 0 || result == -1;
}

/**
 * @brief This method says if this object is equal to the input
 * @param other The object we compare to
 * @return 1 iff this equal than other , 0 otherwise
 */
bool big_integer::operator==(const big_integer &other)
{
    return (operator>=(other) && operator<=(other));
}

/**
 * @brief This method says if this object is not equal to the input
 * @param other The object we compare to
 * @return 1 iff this equal than other , 0 otherwise
 */
bool big_integer::operator!=(const big_integer &other)
{
    return !operator==(other);
}

/**
 * @brief This method defines the operation of addition 2 "big_integers"
 * @param other The big_integer object that we add to this object
 * @return the result of the operation
 */
big_integer big_integer :: operator+(const big_integer& other)
{
    string result;
    if(this -> unNegative)
    {
        if(other.unNegative)
        {
            result = sumNumbers(*this, other);
        }
        else
        {
            result = sumDifferentSigns(*this, (big_integer &) other);
        }
    }
    else if(other.unNegative)
    {
        result = sumDifferentSigns((big_integer &) other, *this);
    }
    else
    {
        result = sumNumbers(*this, other) + "-";
    }
    result = reverseStr(result);
    big_integer newData(result);
    return newData;
}

/**
 * @brief This method defines the operation of +=, which isn't only just add, but also update "this" to be the result.
 * @param other The big_integer object that we add to this object
 * @return A reference to the result
 */
big_integer &big_integer::operator+=(const big_integer &other)
{
    big_integer new_data = *this + other;
    this -> _data = new_data._data;
    this -> unNegative = new_data.unNegative;
    this -> length = new_data.length;
    return *this;
}

/**
 * @brief This method defines the operation of subtraction 2 "big_integers"
 * @param other The big_integer object that we subtract from "this" object
 * @return the result of the operation
 */
big_integer big_integer::operator-(const big_integer& other)
{
    if(*this == other)
    {
        return 0;
    }
    if(this->_data == "0")
    {
        big_integer otherCopy(other);
        otherCopy.unNegative = !other.unNegative;
        return otherCopy;
    }
    if(other._data == "0")
    {
        return *this;
    }
    string result;
    if (this->unNegative)
    {
        if (other.unNegative)
        {
            result = subtractSameSigns(*this, other);
        }
        else
        {
            result = subtractDifferentSigns(*this, (big_integer&)other);
        }
    }
    else if(other.unNegative)
    {
        result = subtractDifferentSigns(*this, (big_integer&)other);
        if(result != "0")
        {
            result = result + "-";
        }
    }
    else
    {
        result = subtractSameSigns(*this, other);
    }
    big_integer new_data(reverseStr(result));
    removeZeros(new_data);
    return new_data;
}
/**
 * @brief This method defines the operation of -=, which isn't only just subtract, but also update "this" to be the
 * result.
 * @param other The big_integer object that we subtract from "this" object
 * @return A reference to the result
 */
big_integer &big_integer::operator-=(const big_integer &other)
{
    big_integer new_data = *this - other;
    this -> _data = new_data._data;
    this -> unNegative = new_data.unNegative;
    this -> length = new_data.length;
    return *this;
}

/**
 * @brief This method defines the operation of multiplying a "big_integers" in another
 * @param other The big_integer object that we multiply "this" object by
 * @return the result of the operation
 */
big_integer big_integer::operator*(const big_integer &other)
{
    big_integer result(*this);
    big_integer otherCopy(other);
    big_integer sum(0);
    result.unNegative = (this -> unNegative && other.unNegative) || (!this -> unNegative && !other.unNegative);
    long curDigit = 0;
    for(long i = 0; i < (long)other.length; i++)
    {
        curDigit = other._data[i] - INT_TO_CHAR_CONVERTER;
        sum += multiplyByDigit(result, curDigit);
        result._data = "0" + result._data;
    }
    return sum;
}

/**
 * @brief This method defines the operation of *=, which isn't only just multiplication, but also update "this" to be
 * the result.
 * @param other The big_integer object that we multiply "this" object by
 * @return A reference to the result
 */
big_integer& big_integer::operator*=(const big_integer &other)
{
    big_integer new_data = *this * other;
    this -> _data = new_data._data;
    this -> unNegative = new_data.unNegative;
    this -> length = new_data.length;
    return *this;
}

/**
 * @brief This method defines the operation of dividing a "big_integers" in another
 * @param other The big_integer object that we divide "this" object by
 * @return the result of the operation
 */
big_integer big_integer::operator/(const big_integer &other)
{
    int comparison = compareSameSign(*this, (big_integer)other);
    if(comparison == -1 || other._data == "0") // Division by zero, or by a bigger number
    {
        return big_integer();
    }
    big_integer result;
    result.unNegative = (this -> unNegative && other.unNegative) || (!this -> unNegative && !other.unNegative);
    if(comparison == 0) // Equal
    {
        result._data = "1";
        return result;
    }
    big_integer divisor(other);
    divisor.unNegative = true;
    big_integer divided(*this);
    divided.unNegative = true;
    big_integer reminder(getFirst(divided, divisor));
    int nextDigit = findNextDigit(reminder);
    big_integer factor = getMultiplicationFactor(reminder, divisor);
    if(reminder < divisor && !(reminder == divided))
    {
        result._data = factor._data;
        return result;
    }
    result._data = factor._data + result._data;
    int latestDigit = nextDigit;
    while((reminder = differenciate(reminder, divisor * factor, &nextDigit, &result, divisor)) > divisor)
    {
        if(latestDigit  != nextDigit + 1) // change 2
        {
            nextDigit --;
        }
        latestDigit = nextDigit;
        factor = getMultiplicationFactor(reminder, divisor);
        reminder.length = reminder._data.length();
        removeZeros(reminder);
        if(reminder != 0)
        {
            result += factor;
        }
    }
    result.length = result._data.length();
    removeZeros(result);
    return result;
}

/**
 * @brief This method defines the operation of /=, which isn't only just division, but also update "this" to be
 * the result.
 * @param other The big_integer object that we divide "this" object by
 * @return A reference to the result
 */
big_integer& big_integer :: operator/=(const big_integer& other)
{
    big_integer new_data = *this / other;
    this -> _data = new_data._data;
    this -> unNegative = new_data.unNegative;
    this -> length = new_data.length;
    return *this;
}

/**
 * @brief This method defines the operation of module for "big_integers"
 * @param other The big_integer object that we take module of "this" object by
 * @return the result of the operation
 */
big_integer big_integer::operator%(const big_integer &other)
{
    big_integer partition = *this / other;
    if(partition == 0)
    {
        if((big_integer)other != 0)
        {
            return *this;
        }
        return 0;
    }
    partition.unNegative = this -> unNegative;
    if(!other.unNegative)
    {
        return *this + (partition * other);
    }
    return *this - (partition * other);
}

/**
 * @brief This method enables the operation of printing a "big_integers" to the screen using ostream
 * @param output The big_integer object that we'd like to print
 * @param os The ostream.
 * @return The ostream object
 */
ostream &operator<<(ostream &os, const big_integer &output)
{
    if(!output.unNegative)
    {
        os << '-';
    }
    for(long i = (long)output._data.length() - 1; i >= 0; i --)
    {
        os << output._data[i];
    }
    return os;
}









