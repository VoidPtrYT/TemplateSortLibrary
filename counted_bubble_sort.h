#pragma once
#include "counted_sort.h"
namespace vptsl
{
	template <typename T>
	class counted_bubble_sort :
		public counted_sort<T>
	{
	public:
		counted_bubble_sort() :
			counted_sort()
		{}
		counted_bubble_sort(T* pStart, size_t size) :
			counted_sort(pStart, size)
		{}
		counted_bubble_sort(T* pStart, T* pEnd) :
			counted_sort(pStart, pEnd)
		{}
		~counted_bubble_sort() = default;

		void start_sort(bool(*predicate)(T& firstVal, T& secondVal)) override
		{
			for (size_t i = 0; i < this->_size; ++i)
			{
				for (size_t j = 0; j < this->_size - i - 1; ++j)
				{
					++this->countIterations;
					if (predicate(this->_pStart[j], this->_pStart[j + 1]))
					{
						++this->countSwap;
						T tmp = this->_pStart[j];
						this->_pStart[j] = this->_pStart[j + 1];
						this->_pStart[j + 1] = tmp;
					}
				}
			}
		}

		void start_sort(void) override
		{
			this->start_sort([](T& l, T& r)
			{
				return l < r;
			});
		}
	};
}