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
    template <typename T>
    JCTensor<T> array(T scalar, uint64_t ndim = 0)
    {

    }
}