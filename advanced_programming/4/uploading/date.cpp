#include "date.hpp"                                                                                
                                                                
Date::Date(int d, int m, int y)
{
    set_date(d, m, y);
}
                                                                                
bool is_leap_year(int year)
{
    int r = year % 33;
    return r==1 || r==5 || r==9 || r==13 || r==17 || r==22 || r==26 || r==30;
}

int days_of_month(int m, int y)
{
    if (m < 7)
        return 31;
    else if (m < 12)
        return 30;
    else if (m == 12)
        return is_leap_year(y) ? 30 : 29;
    else
        throw bad_date();
}

void Date::set_date(int d, int m, int y)
{
    if (y < 0 || m < 1 || m > 12 || d < 1 || d > days_of_month(m, y))
        throw bad_date();

    day = d;
    month = m;
    year = y;
}

void Date::inc_one_day()
{
    day++;
    if (day > days_of_month(month, year)) {
        day = 1;
        month++;
        if (month > 12) {
            month = 1;
            year++;
        }
    }
}

void Date::print_date()
{
    cout << day << '/' << month << '/' << year << endl;
}

bool Date::equals(Date d) {
    return day == d.day && month == d.month && year == d.year;
}

Date str_to_date(string s) {
    int slash_pos = s.find('/');
    int d = atoi(s.substr(0, slash_pos).c_str());
    s = s.substr(slash_pos + 1);
    slash_pos = s.find('/');
    int m = atoi(s.substr(0, slash_pos).c_str());
    int y = atoi(s.substr(slash_pos + 1).c_str());
    return Date(d, m, y);
}

bool earlier_date(Date earlier, Date after)
{
  if(after.get_year() > earlier.get_year())
   return 1;
  if(   after.get_year() == earlier.get_year() &&
        after.get_month() > earlier.get_month())
    return 1;
  if(   after.get_day() > earlier.get_day() &&
        after.get_year() == earlier.get_year() &&
        after.get_month() == earlier.get_month())
    return 1;
  return 0;
}
bool earlier_date(string earlier, string after)
{
  if(after == NOW)
    return 1;
  if(earlier == NOW)
    return 0;
  return earlier_date(str_to_date(earlier), str_to_date(after));
}