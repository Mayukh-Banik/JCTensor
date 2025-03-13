#pragma once

#define CL_TARGET_OPENCL_VERSION 300

#include <stdlib.h>
#include <vector>
#include <cstdint>
#include <iostream>
#include <CL/opencl.hpp>


namespace jctensor
{

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

};
