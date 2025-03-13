#include <gtest/gtest.h>
#include <JCTensor/JCTensor.hpp>


TEST(getDevices, PositiveNumbers) {
    for (const auto& [a, b] : jctensor::OpenCLCapabaleDevices)
    {
        std::cout << "Platform: " << a.getInfo<CL_PLATFORM_NAME>() 
                  << ", Device: " << b.getInfo<CL_DEVICE_NAME>() << "\n";
    }
}
