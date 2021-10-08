#ifndef __DATE_H__
#define __DATE_H__
#include <iostream>
#include <cstdlib>
#include <string>
#include "error_handling.hpp"
#define NOW "NOW"
using namespace std;
                                                                                

class Date {
public:
    Date(int d, int m, int y);
    Date() {Date (0, 0, 0);}
    void set_date(int d, int m, int y);
    void print_date();
    void inc_one_day();
    bool equals(Date d);
    
    int get_day() { return day; }
    int get_month() { return month; }
    int get_year() { return year; }

private:
    int day;
    int month;
    int year;
};

Date str_to_date(string s);
bool is_leap_year(int year);
int days_of_month(int m, int y);
bool earlier_date(Date earlier, Date after);
bool earlier_date(string earlier, string after);

#endif