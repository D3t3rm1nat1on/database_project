#include <algorithm>
#include <sstream>
#include <stdexcept>

#include "database.h"
#include "templates.h"

void Database::Add(const Date& date, const std::string& event)
{
    const auto [it, is_new_event] = database[date].events.insert(event);
    if (is_new_event)
        database[date].events_input_order.push_back(event);
}

void Database::Print(std::ostream& os) const
{
    for (const auto& [date, meta] : database) {
        for (const auto& event : meta.events) {
            os << date << " " << event << std::endl;
        }
    }
}

int Database::RemoveIf(predicate_func predicate)
{
    int result = 0;
    auto it_db = database.begin();
    while (it_db != database.end()) {
        const Date& date = it_db->first;
        Meta& meta = it_db->second;

        auto it_events = meta.events.begin();

        while (it_events != meta.events.end()) {
            const std::string& event = *it_events;

            // remove event if find one
            if (predicate(date, event)) {
                it_events = meta.events.erase(it_events);
                // prepare for delete
                meta.prepare_for_delete.insert(event);
                result++;
                continue;
            }

            it_events++;
        }

        auto it = std::stable_partition(
            meta.events_input_order.begin(),
            meta.events_input_order.end(),
            [&meta](const std::string& event_to_delete) {
                auto it_to_delete = meta.prepare_for_delete.find(event_to_delete);
                if (it_to_delete == meta.prepare_for_delete.end())
                    return true;
                meta.prepare_for_delete.erase(it_to_delete);
                return false;
            });
        meta.events_input_order.resize(std::distance(meta.events_input_order.begin(), it));

        // remove database entry if no events left
        if (meta.events.empty()) {
            it_db = database.erase(it_db);
            continue;
        }

        it_db++;
    }

    return result;
}

std::vector<std::pair<Date, std::string>> Database::FindIf(predicate_func predicate) const
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

std::string Database::Last(const Date& date) const
{
    auto reverse_it = rlower_bound(database, date);

    if (reverse_it == rend(database))
        throw std::invalid_argument("No entries");

    const Date& found_date = reverse_it->first;
    const Meta& meta = reverse_it->second;

    std::ostringstream oss;

    if (meta.events_input_order.empty()) {
        throw std::runtime_error("no events");
    }

    oss << found_date << ' ' << meta.events_input_order.back();

    return oss.str();
}
