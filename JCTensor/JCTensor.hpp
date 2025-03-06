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
#include "../extern/CLBlast/include/clblast.h"

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
    T* data = NULL;
    std::vector<uint64_t>* shape = nullptr;
    std::vector<uint64_t>* strides = nullptr;
    uint64_t elementCount;
    uint64_t ndim;
    uint64_t len;
    const int elementSize = sizeof(T);
    bool independent = true;

    JCTensor(T elem)
    {
        this->independent = true;
        this->shape = nullptr;
        this->strides = nullptr;
        setENL();
#if defined(__CUDACC__)
#else
        this->data = (T*) malloc(this->len);
		if (this->data == NULL)
		{
			throw std::runtime_error("Failed to allocate memory for JCTensor");
		}
        this->data[0] = elem;
#endif
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
#if defined(__CUDACC__)
#else
        if (this->data != NULL)
        {
            free(this->data);
        }
#endif
    }

    
};

namespace jctensor {
    std::vector<std::string> getOpenCLDeviceNames() {
        std::vector<std::string> deviceNames;
        std::vector<cl::Platform> platforms;
        cl::Platform::get(&platforms);

        for (const auto& platform : platforms) {
            std::vector<cl::Device> devices;
            platform.getDevices(CL_DEVICE_TYPE_ALL, &devices);

            for (const auto& device : devices) {
                std::string name = device.getInfo<CL_DEVICE_NAME>();
                deviceNames.push_back(name);
            }
        }

        return deviceNames;
    }

    template <typename T>
    JCTensor<T> array(T scalar, uint64_t ndim = 0)
    {

    }

    template <typename T>
	JCTensor<T> array(std::vector<T> values, uint64_t ndim = 0)
	{
	}
}