#include <iostream>
#include "header.h"
#include <string>
using namespace std;

string bit_to_string(bool n)
{
    if(n)   return "1";
    else    return "0";
}

bool char_to_bit(char c)
{
    return int(c) - int('0');
}

string decimal_to_binary(unsigned n)
{
    if(n<2)
        return bit_to_string(n);
    else
    {
        string binary_string = decimal_to_binary( n/2) + bit_to_string( n%2);
        return binary_string;
    }
}

string binary_to_gray(string binary)
{
    if(binary.length() < 2)
        return binary;

    bool digit = char_to_bit(binary.at(binary.length()-1))^char_to_bit(binary.at(binary.length()-2));
    binary.erase(binary.end()-1);
    return binary_to_gray(binary) + bit_to_string(digit);
}

string full_left_by_zero(int bits_number, string s)
{
    while(s.length() < bits_number)
    {
        s.insert(s.begin(), '0');
    }
    return s;
}

string formal_decimal_to_gray(int digits, int number)
{
    return full_left_by_zero(digits, binary_to_gray(decimal_to_binary(number)));
}
