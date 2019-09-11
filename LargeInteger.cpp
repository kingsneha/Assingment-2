/**
 * @author Sneha Santhosh
 * @cwid   50193711
 * @class  COSC 2336, Spring 2019
 * @ide    Visual Studio Community 2017
 * @date   September 09, 2019
 * @assg   Assignment 03
 *
 * @description LargeInteger class.  Represent an arbitrarily large
 *   (signed) integer.  This class keeps the digits of the integer in
 *   an array of integers internally.  The array of integers is
 *   dynamically resized as necessary during LargeInteger operations.
 *   This abstract data type supports addition of large integers.
 */
#include "LargeInteger.hpp"

using namespace std;
static int nextLargeIntegerId = 1;

/** LargeInteger constructor
 * Constructor for LargeInteger class that takes a simple built-in
 * integer to be used as the initial value of the large integer.
 *
 * @param value A regular (32-bit) integer that we will use as the
 *    initial value of this LargeInteger data type.
 */
LargeInteger::LargeInteger(int value)
{
 
  id = nextLargeIntegerId++;
  numDigits = (int)log10((double)value) + 1;
  digits = new int[numDigits];
  int digit;
  for (int digitIndex = 0; digitIndex < numDigits; digitIndex++)
  {
   
    digit = value % 10;
    digits[digitIndex] = digit;
    value = value / 10;
  }
}

/** LargeInteger constructor
 * Constructor for LargeInteger class that takes an array of digits
 * and initializes this large integers digits to the given values.
 *
 * @param numDigits The number of digits being passed in to be
 *   initialized.
 * @param digits An array of integers representing digits of a
 *   large integer.
 */
LargeInteger::LargeInteger(int numDigits, int digits[])
{
  
  id = nextLargeIntegerId++;
  this->numDigits = numDigits;
  this->digits = new int[numDigits];
  for (int digitIndex = 0; digitIndex < numDigits; digitIndex++)
  {
    this->digits[digitIndex] = digits[digitIndex];
  }
}

/** LargeInteger destructor
 * Destructor for the LargeInteger class.  Make sure we are good
 * managers of memory by freeing up our digits when this object
 * goes out of scope.
 */
LargeInteger::~LargeInteger()
{
  cout << "<LargeInteger::~LargeInteger> destructor entered, freeing my digits" << endl
    << "     id = " << id << endl
    << "     value=" << tostring() << endl;
  delete[] this->digits;
}

/** LargeInteger max digits
 * Return the larger of the number of digits (numDigits) between
 * this object and the other LargeInteger object.  This might
 * not be so useful to users of this data type, but the first
 * step in addition and subtraction is to determine the size
 * we need for the new result array, which will either be the
 * larger numDigits of the two objects being added, or that value
 * plus 1 if there is cary from the addition.
 *
 * @param other Another LargeInteger object that we are to compare
 *   this object numDigits to
 *
 * @returns int The larger (max) of the numDigits of the two
 *   referenced objects.
 */
int LargeInteger::maxDigits(LargeInteger& other)
{
  return max(this->numDigits, other.numDigits);
}

/** LargeInteger digit at index
 * Given an index, return the digit at the given index of
 * this LargeInteger.  The digitIndex passed in refers to
 * the place or power of the digit needed.  For example
 * 0 means we want the 10^0 or the 1's place, 1 means we
 * need the 10^1 or the 10s place digit, etc.  If the
 * requested digit index is bigger than the number of places
 * in the LargeInteger then 0 is returned.  For example, if this
 * LargeInteger represents the number 123, and we ask for the
 * 4th place (10^4 or the 1000s place), this function will
 * return 0.
 *
 * @param digitIndex The index, interpreted as the place or power,
 *   of the specific digit to be accessed and returned.
 *
 * @returns int The digit in the 10^digitIndex of this
 *   LargeInteger object.
 */
int LargeInteger::digitAtPlace(int digitPlace)
{
  
  if ((digitPlace >= numDigits) || (digitPlace < 0))
  {
    return 0;
  }
  else 
  {
    return digits[digitPlace];
  }
}

/** LargeInteger append digit
 * Append the indicated digit to the most significant place of this
 * digit.  This function is not so useful to users of LargeInteger.
 * However, for arithemetic operations, if there is carry over from
 * the last operations (like carry from adding the most significant
 * place of two integers), then the LargeInteger has to grow in size.
 *
 * @param digit The digit to append to the most significant place
 *   of this object.
 */
void LargeInteger::appendDigit(int digit)
{
  
  int numNewDigits = numDigits + 1;
  int* newDigits = new int[numNewDigits];

  
  if (digit == 0)
  {
    return;
  }

  for (int digitPlace = 0; digitPlace < numDigits; digitPlace++)
  {
    newDigits[digitPlace] = digits[digitPlace];
  }

  
  newDigits[numDigits] = digit;

  
  delete[] digits;
  digits = newDigits; 
  numDigits = numNewDigits;
}

/** LargeInteger add
 * Add this LargeInteger to the other LargeInteger passed in as
 * a parameter.
 *
 * @param other Another LargeInteger data type.
 *
 * @returns LargeInteger& Returns a reference to a newly created
 *   LargeInteger which contains the value of the this added
 *   with other.
 */
LargeInteger& LargeInteger::add(LargeInteger& other)
{
  
  int numNewDigits = maxDigits(other);

  int* newDigits = new int[numNewDigits];

 
  int newDigit;
  int carry = 0;
  for (int digitPlace = 0; digitPlace < numNewDigits; digitPlace++)
  {
    newDigit = this->digitAtPlace(digitPlace) + other.digitAtPlace(digitPlace) + carry;
    carry = newDigit / 10;     
    newDigit = newDigit % 10;  
    newDigits[digitPlace] = newDigit;
  }

  
  LargeInteger* res = new LargeInteger(numNewDigits, newDigits);
  delete[] newDigits;  


  res->appendDigit(carry);

  return *res;
}

/** LargeInteger tostring
 * Represent this large integer as a string value
 *
 * @returns string The large integer as a string
 */
string LargeInteger::tostring()
{
  ostringstream out;

  for (int digitPlace = numDigits - 1; digitPlace >= 0; digitPlace--)
  {
    out << digits[digitPlace];
  }

  return out.str();
}
