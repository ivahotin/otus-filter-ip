#include <cassert>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <tuple>
#include <algorithm>
#include <stdexcept>
#include <cstdio>

struct Ip {
    short first;
    short second;
    short third;
    short forth;
};

using IpPool = std::vector<Ip>;

std::ostream& operator<<(std::ostream& os, const Ip& ip) {
    os << ip.first << '.'
        << ip.second << '.'
        << ip.third << '.'
        << ip.forth;

    return os;
}

struct IpReverseComparator {
    bool operator() (const Ip& lhs, const Ip& rhs) const {
        return std::tie(lhs.first, lhs.second, lhs.third, lhs.forth) >
            std::tie(rhs.first, rhs.second, rhs.third, rhs.forth);
    } 
};

void filter(const IpPool& ipPool, std::ostream& os, short num) {
    std::copy_if(begin(ipPool), end(ipPool), std::ostream_iterator<Ip>(os, "\n"), [num](const Ip& ip) {
            return ip.first == num;
        });
}

void filter(const IpPool& ipPool, std::ostream& os, short num1, short num2) {
    std::copy_if(begin(ipPool), end(ipPool), std::ostream_iterator<Ip>(os, "\n"), [num1, num2](const Ip& ip) {
            return ip.first == num1 && ip.second == num2;
        });
}

void filter_any(const IpPool& ipPool, std::ostream& os, short num) {
    std::copy_if(begin(ipPool), end(ipPool), std::ostream_iterator<Ip>(os, "\n"), [num](const Ip& ip) {
            return ip.first == num || ip.second == num || ip.third == num || ip.forth == num;
        });
}

Ip parse(const std::string &str) {
    Ip ip {0, 0, 0, 0};

    int temp, temp2;
    if (std::sscanf(str.c_str(), "%hd.%hd.%hd.%hd\t%d\t%d", &ip.first, &ip.second, &ip.third, &ip.forth, &temp, &temp2) == 6) {
        return ip;
    }

    throw std::invalid_argument("Invalid ip address line: " + str);
}

int main()
{
    IpPool ipPool;
    try
    {
        for (std::string line; std::getline(std::cin, line);) {
            ipPool.push_back(parse(line));
        }

        std::sort(begin(ipPool), end(ipPool), IpReverseComparator{});
        std::copy(begin(ipPool), end(ipPool), std::ostream_iterator<Ip>(std::cout, "\n"));

        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        filter(ipPool, std::cout, 1);

        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        filter(ipPool, std::cout, 46, 70);

        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        filter_any(ipPool, std::cout, 46);

        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231
        // 185.46.86.132
        // 185.46.86.131
        // 185.46.86.131
        // 185.46.86.22
        // 185.46.85.204
        // 185.46.85.78
        // 68.46.218.208
        // 46.251.197.23
        // 46.223.254.56
        // 46.223.254.56
        // 46.182.19.219
        // 46.161.63.66
        // 46.161.61.51
        // 46.161.60.92
        // 46.161.60.35
        // 46.161.58.202
        // 46.161.56.241
        // 46.161.56.203
        // 46.161.56.174
        // 46.161.56.106
        // 46.161.56.106
        // 46.101.163.119
        // 46.101.127.145
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // 46.55.46.98
        // 46.49.43.85
        // 39.46.86.85
        // 5.189.203.46
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
