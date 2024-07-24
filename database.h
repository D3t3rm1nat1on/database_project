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
    void Print(std::ostream& os) const;
    int RemoveIf(predicate_func);
    std::vector<std::pair<Date, std::string>> FindIf(predicate_func predicate) const;
    std::string Last(const Date& date) const;

private:
    std::map<Date, Meta> database;
};
