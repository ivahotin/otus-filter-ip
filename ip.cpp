#include <iterator>
#include <algorithm>
#include <tuple>
#include <cstdio>
#include <stdexcept>

#include "ip.h"

namespace ip
{
    std::ostream& operator<<(std::ostream& os, const ip::Ip& ipAddress) {
        os << ipAddress.first << '.'
            << ipAddress.second << '.'
            << ipAddress.third << '.'
            << ipAddress.forth;

        return os;
    }

    template<>
    void filter<FilterType::First_1>(const ip::IpPool& ipPool, std::ostream& os) {
        std::copy_if(begin(ipPool), end(ipPool), std::ostream_iterator<ip::Ip>(os, "\n"), [](const ip::Ip& ipAddress) {
            return ipAddress.first == 1;
        });
    }

    template<>
    void filter<FilterType::First_46_Second_70>(const ip::IpPool& ipPool, std::ostream& os) {
        std::copy_if(begin(ipPool), end(ipPool), std::ostream_iterator<ip::Ip>(os, "\n"), [](const ip::Ip& ipAddress) {
            return ipAddress.first == 46 && ipAddress.second == 70;
        });
    }

    template<>
    void filter<FilterType::Any_46>(const ip::IpPool& ipPool, std::ostream& os) {
        std::copy_if(begin(ipPool), end(ipPool), std::ostream_iterator<ip::Ip>(os, "\n"), [](const ip::Ip& ipAddress) {
            return ipAddress.first == 46 || ipAddress.second == 46 || ipAddress.third == 46 || ipAddress.forth == 46;
        }); 
    }

    bool ip::IpReverseComparator::operator()(const ip::Ip& lhs, const ip::Ip& rhs) const {
        return std::tie(lhs.first, lhs.second, lhs.third, lhs.forth) >
            std::tie(rhs.first, rhs.second, rhs.third, rhs.forth); 
    }

    ip::Ip parse(const std::string& str) {
        ip::Ip ipAddress {0, 0, 0, 0};

        int temp, temp2;
        if (std::sscanf(str.c_str(), "%hd.%hd.%hd.%hd\t%d\t%d", &ipAddress.first, &ipAddress.second, &ipAddress.third, &ipAddress.forth, &temp, &temp2) == 6) {
            return ipAddress;
        }

        return ip::Ip{-1, -1, -1, -1};
    }
}