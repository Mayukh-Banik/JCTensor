#pragma once

#include <stdlib.h>
#include <vector>
#include <cstdint>
#include <iostream>

#if defined(__CUDACC__)
#include <cuda_runtime_api.h>
#include <cuda_runtime.h>
#else
#endif

#include <CL/cl.hpp>

template <typename T>
class JCTensor
{
private:
    /**
     * Sets element count, ndim, and len based on shape ptr
     */
    void setENL()
    {
        this->elementCount = 1;
        if (this->shape == nullptr)
        {
            this->ndim = 0;
        }
        else
        {
            this->ndim = this->shape->size();
            for (auto dim : *this->shape)
            {
                this->elementCount *= dim;
            }
        }
        this->len = this->elementSize * this->elementCount;
    }

    /**
     * Sets strides based on shape
     */
    void setStrides()
    {
        if (this->shape == nullptr)
        {
            this->strides = nullptr;
        }
        this->strides = new std::vector<uint64_t>();
        if (this->shape->size() == 0)
        {
        }
        else if (this->shape->size() == 1)
        {
            this->strides->push_back(this->elementSize);
        }
        else
        {
            for (uint64_t i = 0; i < this->strides->size(); i++)
            {
                this->strides->push_back(this->elementSize);
                for (uint64_t j = i + 1; j < this->strides->size(); j++)
                {
                    this->strides[i] *= this->shape[j];
                }
            }
        }
    }

public:
    /**
     * Raw Data pointer
     */
    T *data = NULL;
    std::vector<uint64_t> *shape = nullptr;
    std::vector<uint64_t> *strides = nullptr;
    uint64_t elementCount;
    uint64_t ndim;
    uint64_t len;
    const int elementSize = sizeof(T);
    bool independent = true;
    cl::Device currentDevice;

    JCTensor(cl::Device requestedDevice = cl::Device());

    JCTensor(T elem)
    {
        this->independent = true;
        this->shape = nullptr;
        this->strides = nullptr;
        setENL();
    }

    JCTensor(uint64_t ndim)
    {
        this->shape = new std::vector<uint64_t>(shapeInput);
    }

    ~JCTensor()
    {
        if (this->shape != nullptr)
        {
            delete this->shape;
        }
        if (this->strides != nullptr)
        {
            delete this->strides;
        }
    }

};

namespace jctensor
{
    std::vector<std::string> getOpenCLDeviceNames()
    {
        std::vector<std::string> deviceNames;
        std::vector<cl::Platform> platforms;
        cl::Platform::get(&platforms);

        for (const auto &platform : platforms)
        {
            std::vector<cl::Device> devices;
            platform.getDevices(CL_DEVICE_TYPE_ALL, &devices);

            for (const auto &device : devices)
            {
                std::string name = device.getInfo<CL_DEVICE_NAME>();
                deviceNames.push_back(name);
            }
        }

        return deviceNames;
    }

	std::vector<std::tuple<cl::Device, std::string, int>> setDeviceTable()
	{
		std::vector<std::tuple<cl::Device, std::string, int>> deviceTable;
		std::vector<cl::Platform> platforms;
		cl::Platform::get(&platforms);
		int index = 0;
		for (const auto& platform : platforms)
		{
			std::vector<cl::Device> devices;
			platform.getDevices(CL_DEVICE_TYPE_ALL, &devices);
			for (const auto& device : devices)
			{
				std::string deviceName;
				device.getInfo(CL_DEVICE_NAME, &deviceName);
				std::tuple<cl::Device, std::string, int> deviceInfo(device, deviceName, index);
				deviceTable.push_back(deviceInfo);
				index++;
			}
		}
		return deviceTable;
	}
};

std::vector<std::tuple<cl::Device, std::string, int>> DeviceTable = jctensor::setDeviceTable();

// namespace jctensor {
//     std::vector<std::string> getOpenCLDeviceNames() {
//         std::vector<std::string> deviceNames;
//         std::vector<cl::Platform> platforms;
//         cl::Platform::get(&platforms);

//         for (const auto& platform : platforms) {
//             std::vector<cl::Device> devices;
//             platform.getDevices(CL_DEVICE_TYPE_ALL, &devices);

//             for (const auto& device : devices) {
//                 std::string name = device.getInfo<CL_DEVICE_NAME>();
//                 deviceNames.push_back(name);
//             }
//         }

//         return deviceNames;
//     }

//     template <typename T>
//     JCTensor<T> array(T scalar, uint64_t ndim = 0)
//     {

//     }

//     template <typename T>
// 	JCTensor<T> array(std::vector<T> values, uint64_t ndim = 0)
// 	{
// 	}
// }