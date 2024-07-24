#include <iomanip>

#include "date.h"

std::ostream& operator<<(std::ostream& os, const Date& date)
{
    os << std::setfill('0') << std::setw(4) << std::to_string(date.GetYear());
    os << "-";
    os << std::setfill('0') << std::setw(2) << std::to_string(date.GetMonth());
    os << "-";
    os << std::setfill('0') << std::setw(2) << std::to_string(date.GetDay());
    return os;
}

Date ParseDate(std::istream& is)
{
    bool flag = true;

    int year;
    flag = flag && (is >> year);
    flag = flag && (is.peek() == '-');
    is.ignore(1);

    int month;
    flag = flag && (is >> month);
    flag = flag && (is.peek() == '-');
    is.ignore(1);

    int day;
    flag = flag && (is >> day);
    is.ignore(1);
    // flag = flag && (is.peek() != ' ');

    // std::cout << year << '-' << month << '-' << day << std::endl;
    if (!flag) {
        throw std::logic_error("Wrong date format");
    }

    return Date(year, month, day);
}

bool operator==(const Date& d1, const Date& d2)
{
    return d1.GetYear() == d2.GetYear() && d1.GetMonth() == d2.GetMonth() && d1.GetDay() == d2.GetDay();
}

bool operator!=(const Date& d1, const Date& d2)
{
    return d1.GetYear() != d2.GetYear() || d1.GetMonth() != d2.GetMonth() || d1.GetDay() != d2.GetDay();
}

bool operator>(const Date& d1, const Date& d2)
{
    if (d1.GetYear() > d2.GetYear())
        return true;

    if (d1.GetYear() == d2.GetYear() && d1.GetMonth() > d2.GetMonth())
        return true;

    if (d1.GetYear() == d2.GetYear() && d1.GetMonth() == d2.GetMonth() && d1.GetDay() > d2.GetDay())
        return true;


    return false;
}

bool operator<(const Date& d1, const Date& d2)
{
    if (d1.GetYear() < d2.GetYear())
        return true;

    if (d1.GetYear() == d2.GetYear() && d1.GetMonth() < d2.GetMonth())
        return true;

    if (d1.GetYear() == d2.GetYear() && d1.GetMonth() == d2.GetMonth() && d1.GetDay() < d2.GetDay())
        return true;


    return false;
}

bool operator>=(const Date& d1, const Date& d2)
{
    return !(d1 < d2);
}

bool operator<=(const Date& d1, const Date& d2)
{
    return !(d1 > d2);
}

Date::Date()
    : _year(0)
    , _month(1)
    , _day(1)
{
}

Date::Date(int year, int month, int day)
{
    if (month < 1 || month > 12) {
        throw std::out_of_range("Month value is invalid: " + std::to_string(month));
    } else if (day < 1 || day > 31) {
        throw std::out_of_range("Day value is invalid: " + std::to_string(day));
    }
    _year = year;
    _month = month;
    _day = day;
}

Date& Date::operator=(const Date& other)
{
    this->_year = other.GetYear();
    this->_month = other.GetMonth();
    this->_day = other.GetDay();

    return *this;
}

int Date::GetYear() const
{
    return _year;
}

int Date::GetMonth() const
{
    return _month;
}

int Date::GetDay() const
{
    return _day;
}
