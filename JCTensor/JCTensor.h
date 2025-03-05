#pragma once

#include <stdlib.h>
#include <vector>
#include <cstdint>

#if defined(__CUDACC__)
#include <cuda_runtime_api.h>
#include <cuda_runtime.h>
#else
#endif

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
        if (this->shape = nullptr)
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

public:
    /**
     * Raw Data pointer
     */
    T* data = nullptr;
    std::vector<uint64_t>* shape = nullptr;
    std::vector<uint64_t>* strides = nullptr;
    uint64_t elementCount;
    uint64_t ndim;
    uint64_t len;
    constexpr int elementSize = sizeof(T);

    JCTensor(T elem)
    {
        this->shape = nullptr;
        this->strides = nullptr;
        setENL();
#if defined(__CUDACC__)
#else
        this->data = new T[1];
        this->data[0] = elem;
#endif
    }

    JCTensor(std::vector<uint64_t>& shape)
    {
        this->shape = new std::vector<uint64_t>(shapeInput)
    }

    ~JCTensor()
    {
        delete this->shape;
        delete this->strides;
#if defined(__CUDACC__)
#else
        delete[] this->data;
#endif
    }

    
};