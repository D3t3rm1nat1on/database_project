#include <algorithm>
#include <sstream>
#include <stdexcept>

#include "database.h"

template <class Ch, class Tr, class Container>
std::basic_ostream<Ch, Tr>& operator<<(std::basic_ostream<Ch, Tr>& os, Container const& x)
{
    for (auto& y : x)
        os << y << " ";
    return os;
}

void Database::Add(const Date& date, const std::string& event)
{
    const auto [it, is_new_event] = database[date].events.insert(event);
    if (is_new_event)
        database[date].events_input_order.push_back(event);
}

void Database::Print(std::ostream& os)
{
    for (const auto& [date, meta] : database) {
        for (const auto event : meta.events) {
            os << date << " " << event << std::endl;
        }
    }
}

int Database::RemoveIf(predicate_func predicate)
{
    int result = 0;
    auto it_db = database.begin();
    while (it_db != database.end()) {
        auto& [date, meta] = *it_db;
        auto it_events = meta.events.begin();

        while (it_events != meta.events.end()) {
            const std::string& event = *it_events;

            // remove event if find one
            if (predicate(date, event)) {
                it_events = meta.events.erase(it_events);
                // prepare for delete before next "Last" call
                meta.prepare_for_delete.insert(event);
                result++;
                continue;
            }

            it_events++;
        }

        // remove database entry if no events left
        if (meta.events.empty()) {
            it_db = database.erase(it_db);
            continue;
        }

        it_db++;
    }
    return result;
}

std::vector<std::pair<Date, std::string>> Database::FindIf(predicate_func predicate)
{
    std::vector<std::pair<Date, std::string>> result;
    for (const auto& [date, meta] : database) {
        for (const auto& event : meta.events) {
            if (predicate(date, event))
                result.push_back(std::pair<Date, std::string>(date, event));
        }
    }
    return result;
}

// TODO: last added, not last in lexiography
std::string Database::Last(const Date& date)
{
    auto reverse_it = rlower_bound(database, date);

    if (reverse_it == rend(database))
        throw std::invalid_argument("No entries");

    const Date& found_date = reverse_it->first;
    Meta& meta = reverse_it->second;

    auto it = std::stable_partition(
        meta.events_input_order.begin(),
        meta.events_input_order.end(),
        [&meta](std::string& event_to_delete) {
            auto it_to_delete = meta.prepare_for_delete.find(event_to_delete);
            if (it_to_delete == meta.prepare_for_delete.end())
                return true;
            meta.prepare_for_delete.erase(it_to_delete);
            return false;
        });

    meta.events_input_order.resize(std::distance(meta.events_input_order.begin(), it));

    std::ostringstream oss;

    if (meta.events_input_order.empty()) {
        throw std::runtime_error("no events");
    }

    oss << found_date << ' ' << meta.events_input_order.back();

    return oss.str();
}