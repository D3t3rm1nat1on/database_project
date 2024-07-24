#pragma once

#include <iostream>
#include <stdexcept>

class Date {
public:
    Date();
    Date(int year, int month, int day);

    int GetYear() const;
    int GetMonth() const;
    int GetDay() const;

    Date& operator=(const Date& other);

private:
    int _year; // can be less than zero
    int _month;
    int _day;
};

std::ostream& operator<<(std::ostream& os, const Date& date);

bool operator==(const Date& d1, const Date& d2);
bool operator!=(const Date& d1, const Date& d2);
bool operator>=(const Date& d1, const Date& d2);
bool operator<=(const Date& d1, const Date& d2);
bool operator>(const Date& d1, const Date& d2);
bool operator<(const Date& d1, const Date& d2);

Date ParseDate(std::istream& is);
