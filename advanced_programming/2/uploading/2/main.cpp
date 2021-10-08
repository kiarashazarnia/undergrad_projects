#include <iostream>
#include <cmath>
#include <string>
#include "header.h"

using namespace std;

int main()
{
    int digits;
    while(cin>>digits)
    {
        for(int number = 0; number<pow(2.0,digits); number++)
        {
        /*    cout<<number<<" "<<full_left_by_zero(digits, decimal_to_binary(number))<<
            " "<<full_left_by_zero(digits, binary_to_gray(decimal_to_binary(number)))<<endl;*/
            cout<<formal_decimal_to_gray(digits, number)<<endl;
        }
    }
    return 0;
}
