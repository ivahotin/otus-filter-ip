#include <vector>
#include <algorithm>
#include <gtest/gtest.h>

#include "lib.h"
#include "ip.h"

TEST(TestVersion, VersionIsGreaterThanZero) {
    EXPECT_GT (version(), 0);
}

TEST(TestIpComparator, ShouldSortInDescOrder) {
    std::vector<ip::Ip> ips = {
        {192, 168, 0, 1},
        {222, 13, 4, 6},
        {192, 168, 1, 0}
    };

    std::vector<ip::Ip> expectedIps = {
        {222, 13, 4, 6},
        {192, 168, 1, 0},
        {192, 168, 0, 1} 
    };

    std::sort(begin(ips), end(ips), ip::IpReverseComparator{});

    ASSERT_EQ(expectedIps.size(), ips.size());
    for (size_t i = 0; i < ips.size(); ++i) {
        ASSERT_EQ(expectedIps[i].first, ips[i].first);
        ASSERT_EQ(expectedIps[i].second, ips[i].second);
        ASSERT_EQ(expectedIps[i].third, ips[i].third);
        ASSERT_EQ(expectedIps[i].forth, ips[i].forth);
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}