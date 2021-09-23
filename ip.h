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

    void filter(const IpPool&, std::ostream&, short, short);
    void filter(const IpPool&, std::ostream&, short);
    void filter_any(const IpPool&, std::ostream&, short);

    Ip parse(const std::string &str);
}