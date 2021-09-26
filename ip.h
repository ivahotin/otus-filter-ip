#pragma once

#include <vector>
#include <iostream> 

namespace ip
{
    struct Ip {
        short first;
        short second;
        short third;
        short forth;
    };

    using IpPool = std::vector<Ip>;

    std::ostream& operator<<(std::ostream&, const Ip&);

    struct IpReverseComparator {
        bool operator() (const Ip& lhs, const Ip& rhs) const;
    };

    enum class FilterType {
        First_1,
        First_46_Second_70,
        Any_46
    };
    
    template <FilterType filterType>
    void filter(const IpPool&, std::ostream&);

    Ip parse(const std::string &str);
}