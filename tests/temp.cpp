#include <gtest/gtest.h>
#include <JCTensor/JCTensor.hpp>


TEST(getDevices, PositiveNumbers) {
    for (const auto& a : DeviceTable)
    {
        std::cout << "Device #" << std::get<2>(a) << ": " << std::get<1>(a) << std::endl;
    }
}
