#include <OpenVecTor.h>
#include <gtest/gtest.h>


TEST(OpenVecTor, version_is_1_0_0)

{
    EXPECT_STREQ("1.0.0", openvector_version());
}