#include <gtest/gtest.h>
#include <JCTensor/JCTensor.hpp>


TEST(getDevices, PositiveNumbers) {
	for (auto a : jctensor::getOpenCLDeviceNames()) {
		std::cout << a << std::endl;
	}
	//std::cout << jctensor::getDevices() << std::endl;
	//EXPECT_STREQ("getDevices", jctensor::getDevices().c_str());
    //JCTensor<int> a = JCTensor<int>(1);
}