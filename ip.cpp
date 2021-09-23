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

    void filter(const ip::IpPool& ipPool, std::ostream& os, short num) {
        std::copy_if(begin(ipPool), end(ipPool), std::ostream_iterator<ip::Ip>(os, "\n"), [num](const ip::Ip& ipAddress) {
            return ipAddress.first == num;
        });
    }

    void filter(const ip::IpPool& ipPool, std::ostream& os, short num1, short num2) {
        std::copy_if(begin(ipPool), end(ipPool), std::ostream_iterator<ip::Ip>(os, "\n"), [num1, num2](const ip::Ip& ipAddress) {
            return ipAddress.first == num1 && ipAddress.second == num2;
        });
    }

    void filter_any(const ip::IpPool& ipPool, std::ostream& os, short num) {
        std::copy_if(begin(ipPool), end(ipPool), std::ostream_iterator<ip::Ip>(os, "\n"), [num](const ip::Ip& ipAddress) {
            return ipAddress.first == num || ipAddress.second == num || ipAddress.third == num || ipAddress.forth == num;
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