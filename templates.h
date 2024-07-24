#pragma once

#include <algorithm>
#include <iostream>

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

template <class Ch, class Tr, class Container>
std::basic_ostream<Ch, Tr>& operator<<(std::basic_ostream<Ch, Tr>& os, Container const& x)
{
    for (auto& y : x)
        os << y << " ";
    return os;
}
