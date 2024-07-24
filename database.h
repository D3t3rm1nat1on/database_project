#pragma once

#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <vector>

#include <functional>

#include "date.h"

// typedef bool (*predicate_func)(const Date&, const std::string&);
using predicate_func = std::function<bool(const Date&, const std::string&)>;

struct Meta {
    std::set<std::string> events;
    std::vector<std::string> events_input_order;
    std::set<std::string> prepare_for_delete;
};

class Database {
public:
    void Add(const Date& date, const std::string& event);
    void Print(std::ostream& os);
    int RemoveIf(predicate_func);
    std::vector<std::pair<Date, std::string>> FindIf(predicate_func predicate);
    std::string Last(const Date& date);

private:
    std::map<Date, Meta> database;
};

template <typename T1, typename T2>
typename std::map<T1, T2>::reverse_iterator rlower_bound(std::map<T1, T2>& m, const T1 x)
{
    if (m.empty())
        return m.rend();
    auto it = m.upper_bound(x);
    return make_reverse_iterator(it);
}

template <typename T1, typename T2>
typename std::map<T1, T2>::reverse_iterator rupper_bound(std::map<T1, T2>& m, const T1 x)
{
    if (m.empty())
        return m.rend();
    auto it = m.lower_bound(x);
    return make_reverse_iterator(it);
}

template <typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, const std::pair<T1, T2> p)
{
    return os << p.first << " " << p.second;
}
